/*
 * SandBox.cpp
 *
 *  Created on: Oct 22, 2012
 *      Author: lion
 */

#include "object.h"
#include "SandBox.h"
#include "path.h"
#include "ifs/vm.h"
#include "ifs/util.h"
#include "ifs/test.h"
#include "ifs/encoding.h"
#include "ifs/Buffer.h"
#include "ifs/EventEmitter.h"
#include "loaders/loaders.h"
#include "options.h"

namespace fibjs {

DECLARE_MODULE(vm);

result_t SandBox_base::_new(v8::Local<v8::Object> mods, obj_ptr<SandBox_base>& retVal,
    v8::Local<v8::Object> This)
{
    return _new(mods, v8::Local<v8::Function>(), v8::Local<v8::Object>(), retVal, This);
}

result_t SandBox_base::_new(v8::Local<v8::Object> mods, v8::Local<v8::Function> require,
    obj_ptr<SandBox_base>& retVal, v8::Local<v8::Object> This)
{
    return _new(mods, require, v8::Local<v8::Object>(), retVal, This);
}

result_t SandBox_base::_new(v8::Local<v8::Object> mods, v8::Local<v8::Object> global,
    obj_ptr<SandBox_base>& retVal, v8::Local<v8::Object> This)
{
    return _new(mods, v8::Local<v8::Function>(), global, retVal, This);
}

result_t SandBox_base::_new(v8::Local<v8::Object> mods, v8::Local<v8::Function> require,
    v8::Local<v8::Object> global, obj_ptr<SandBox_base>& retVal, v8::Local<v8::Object> This)
{
    obj_ptr<SandBox> sbox = new SandBox();
    sbox->wrap(This);

    if (!global.IsEmpty())
        sbox->initGlobal(global);
    else
        sbox->attachBuffer();

    if (!require.IsEmpty())
        sbox->initRequire(require);

    result_t hr = sbox->add(mods);
    if (hr < 0)
        return hr;

    retVal = sbox;
    return 0;
}

SandBox::SandBox(bool extLoader)
{
    Isolate* isolate = holder();

    m_id = isolate->m_sandboxId++;
    isolate->m_sandboxes.emplace(m_id, this);

    obj_ptr<ExtLoader> loader;

    loader = new js_Loader();
    m_loaders.push_back(loader);

    loader = new mjs_Loader();
    m_loaders.push_back(loader);

    if (extLoader) {
        loader = new jsc_Loader();
        m_loaders.push_back(loader);
    }

    loader = new json_Loader();
    m_loaders.push_back(loader);

    m_global = false;
}

SandBox::~SandBox()
{
    Isolate* isolate = holder();
    isolate->m_sandboxes.erase(m_id);
}

void SandBox::initGlobal(v8::Local<v8::Object> global)
{
    Isolate* isolate = holder();
    v8::Local<v8::Value> _token = isolate->context()->GetSecurityToken();

    v8::Local<v8::Context> _context = v8::Context::New(isolate->m_isolate);
    v8::Context::Scope context_scope(_context);

    _context->SetEmbedderData(kObjectPrototype, v8::Object::New(isolate->m_isolate)->GetPrototype());
    _context->SetSecurityToken(_token);

    v8::Local<v8::Object> _global = _context->Global();

    _global->Delete(_context, isolate->NewString("console")).IsJust();
    _global->Set(_context, isolate->NewString("global"), _global).IsJust();
    _global->Set(_context, isolate->NewString("globalThis"), _global).IsJust();

    JSArray ks = global->GetPropertyNames(_context);
    int32_t len = ks->Length();
    int32_t i;

    for (i = 0; i < len; i++) {
        JSValue k = ks->Get(_context, i);
        JSValue v = global->Get(_context, k);

        _global->Set(_context, k, v).IsJust();
    }

    SetPrivate("_global", _global);
    m_global = true;

    installBuffer();
}

RootModule* RootModule::g_root = NULL;
RootModule* RootModule::g_last = NULL;

void SandBox::attachBuffer()
{
    Isolate* isolate = holder();
    v8::Local<v8::Context> context = isolate->context();
    v8::Local<v8::Value> _buffer = context->GetEmbedderData(kBufferClassIndex);

    InstallModule("buffer", _buffer);
    InstallModule("node:buffer", _buffer);
}

void SandBox::installBuffer()
{
    v8::Local<v8::Value> _buffer = Buffer::load_module();

    InstallModule("buffer", _buffer);
    InstallModule("node:buffer", _buffer);
}

result_t SandBox::addBuiltinModules()
{
    Isolate* isolate = holder();
    v8::Local<v8::Context> context = isolate->context();

    RootModule* pModule = RootModule::g_root;

    while (pModule) {
        exlib::string name = pModule->name();
        v8::Local<v8::Object> mod = pModule->getModule(isolate);
        InstallModule(name, mod);
        InstallModule("node:" + name, mod);

        v8::Local<v8::Value> promises = mod->Get(context, isolate->NewString("promises")).FromMaybe(v8::Local<v8::Value>());
        if (!promises.IsEmpty() && promises->IsObject()) {
            InstallModule(name + PATH_SLASH + "promises", promises.As<v8::Object>());
            InstallModule("node:" + name + PATH_SLASH + "promises", promises.As<v8::Object>());
        }

        pModule = pModule->m_next;
    }

    installBuffer();

    return 0;
}

result_t SandBox::add(exlib::string id, v8::Local<v8::Value> mod)
{
    if (is_relative(id))
        return CHECK_ERROR(Runtime::setError("SandBox: does not accept relative path."));

    path_base::normalize(id, id);
    util_base::clone(mod, mod);

    InstallModule(id, mod);

    return 0;
}

result_t SandBox::add(v8::Local<v8::Object> mods)
{
    v8::Local<v8::Context> context = mods->GetCreationContextChecked();
    JSArray ks = mods->GetPropertyNames(context);
    int32_t len = ks->Length();
    int32_t i;
    result_t hr;

    Isolate* isolate = holder();

    for (i = 0; i < len; i++) {
        JSValue k = ks->Get(context, i);
        hr = add(isolate->toString(k), JSValue(mods->Get(context, k)));
        if (hr < 0)
            return hr;
    }

    return 0;
}

result_t SandBox::remove(exlib::string id)
{
    path_base::normalize(id, id);
    v8::Local<v8::Object> m = mods();
    m->Delete(m->GetCreationContextChecked(), holder()->NewString(id)).IsJust();

    return 0;
}

result_t SandBox::has(exlib::string id, bool& retVal)
{
    path_base::normalize(id, id);
    v8::Local<v8::Object> m = mods();
    retVal = m->Has(m->GetCreationContextChecked(), holder()->NewString(id)).FromMaybe(false);

    return 0;
}

result_t SandBox::clone(obj_ptr<SandBox_base>& retVal)
{
    obj_ptr<SandBox> sbox = new SandBox();
    sbox->SetPrivate("_mods", mods()->Clone());

    retVal = sbox;

    return 0;
}

static result_t deepFreeze(Isolate* isolate, v8::Local<v8::Value> v)
{
    if (v.IsEmpty() || !v->IsObject())
        return 0;

    v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(v);

    if (!isFrozen(isolate->m_isolate, obj)) {
        v8::Local<v8::Context> context = obj->GetCreationContextChecked();
        obj->SetIntegrityLevel(context, v8::IntegrityLevel::kFrozen);
        JSArray names = obj->GetPropertyNames(context, v8::KeyCollectionMode::kIncludePrototypes,
            v8::ALL_PROPERTIES, v8::IndexFilter::kIncludeIndices);

        TryCatch try_catch;
        for (int32_t i = 0; i < (int32_t)names->Length(); i++)
            deepFreeze(isolate, JSValue(obj->Get(context, JSValue(names->Get(context, i)))));
    }

    return 0;
}

result_t SandBox::freeze()
{
    v8::Local<v8::Object> global;
    result_t hr;

    hr = get_global(global);
    if (hr < 0)
        return hr;

    Isolate* isolate = Isolate::current(global);
    deepFreeze(isolate, global);

    return 0;
}

result_t SandBox::get_global(v8::Local<v8::Object>& retVal)
{
    if (!m_global)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    retVal = v8::Local<v8::Object>::Cast(GetPrivate("_global"));
    return 0;
}

result_t SandBox::get_modules(v8::Local<v8::Object>& retVal)
{
    Isolate* isolate = holder();

    retVal = v8::Object::New(isolate->m_isolate);

    v8::Local<v8::Object> ms = mods();
    v8::Local<v8::Context> context = ms->GetCreationContextChecked();
    JSArray ks = ms->GetPropertyNames(context);

    v8::Local<v8::String> mgetter = isolate->NewString("exports");

    for (int32_t i = 0, len = ks->Length(); i < len; i++) {
        JSValue k = ks->Get(context, i);
        retVal->Set(context, k, JSValue((v8::Local<v8::Object>::Cast(JSValue(ms->Get(context, k))))->Get(context, mgetter))).IsJust();
    }

    return 0;
}

} /* namespace fibjs */
