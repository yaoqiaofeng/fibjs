/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#pragma once

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"
#include "ifs/XmlNode.h"

namespace fibjs {

class XmlNode_base;

class XmlDocumentType_base : public XmlNode_base {
    DECLARE_CLASS(XmlDocumentType_base);

public:
    // XmlDocumentType_base
    virtual result_t get_name(exlib::string& retVal) = 0;
    virtual result_t get_publicId(exlib::string& retVal) = 0;
    virtual result_t get_systemId(exlib::string& retVal) = 0;

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }

public:
    static void s_get_name(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_publicId(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_systemId(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
};
}

namespace fibjs {
inline ClassInfo& XmlDocumentType_base::class_info()
{
    static ClassData::ClassProperty s_property[] = {
        { "name", s_get_name, block_set, false },
        { "publicId", s_get_publicId, block_set, false },
        { "systemId", s_get_systemId, block_set, false }
    };

    static ClassData s_cd = {
        "XmlDocumentType", false, s__new, NULL,
        0, NULL, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &XmlNode_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void XmlDocumentType_base::s_get_name(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_INSTANCE(XmlDocumentType_base);
    PROPERTY_ENTER();

    hr = pInst->get_name(vr);

    METHOD_RETURN();
}

inline void XmlDocumentType_base::s_get_publicId(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_INSTANCE(XmlDocumentType_base);
    PROPERTY_ENTER();

    hr = pInst->get_publicId(vr);

    METHOD_RETURN();
}

inline void XmlDocumentType_base::s_get_systemId(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_INSTANCE(XmlDocumentType_base);
    PROPERTY_ENTER();

    hr = pInst->get_systemId(vr);

    METHOD_RETURN();
}
}
