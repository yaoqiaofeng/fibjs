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

namespace fibjs {

class base32_base;
class base64_base;
class base58_base;
class hex_base;
class multibase_base;
class iconv_base;
class Buffer_base;
class json_base;
class msgpack_base;

class encoding_base : public object_base {
    DECLARE_CLASS(encoding_base);

public:
    // encoding_base
    static result_t isEncoding(exlib::string codec, bool& retVal);
    static result_t encode(Buffer_base* data, exlib::string codec, exlib::string& retVal);
    static result_t decode(exlib::string str, exlib::string codec, obj_ptr<Buffer_base>& retVal);
    static result_t jsstr(exlib::string str, bool json, exlib::string& retVal);
    static result_t encodeURI(exlib::string url, exlib::string& retVal);
    static result_t encodeURIComponent(exlib::string url, exlib::string& retVal);
    static result_t decodeURI(exlib::string url, exlib::string& retVal);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }

public:
    static void s_static_isEncoding(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_static_encode(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_static_decode(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_static_jsstr(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_static_encodeURI(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_static_encodeURIComponent(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_static_decodeURI(const v8::FunctionCallbackInfo<v8::Value>& args);
};
}

#include "ifs/base32.h"
#include "ifs/base64.h"
#include "ifs/base58.h"
#include "ifs/hex.h"
#include "ifs/multibase.h"
#include "ifs/iconv.h"
#include "ifs/Buffer.h"
#include "ifs/json.h"
#include "ifs/msgpack.h"

namespace fibjs {
inline ClassInfo& encoding_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "isEncoding", s_static_isEncoding, true, false },
        { "encode", s_static_encode, true, false },
        { "decode", s_static_decode, true, false },
        { "jsstr", s_static_jsstr, true, false },
        { "encodeURI", s_static_encodeURI, true, false },
        { "encodeURIComponent", s_static_encodeURIComponent, true, false },
        { "decodeURI", s_static_decodeURI, true, false }
    };

    static ClassData::ClassObject s_object[] = {
        { "base32", base32_base::class_info },
        { "base64", base64_base::class_info },
        { "base58", base58_base::class_info },
        { "hex", hex_base::class_info },
        { "multibase", multibase_base::class_info },
        { "iconv", iconv_base::class_info },
        { "json", json_base::class_info },
        { "msgpack", msgpack_base::class_info }
    };

    static ClassData s_cd = {
        "encoding", true, s__new, NULL,
        ARRAYSIZE(s_method), s_method, ARRAYSIZE(s_object), s_object, 0, NULL, 0, NULL, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void encoding_base::s_static_isEncoding(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    bool vr;

    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = isEncoding(v0, vr);

    METHOD_RETURN();
}

inline void encoding_base::s_static_encode(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_ENTER();

    METHOD_OVER(2, 1);

    ARG(obj_ptr<Buffer_base>, 0);
    OPT_ARG(exlib::string, 1, "utf8");

    hr = encode(v0, v1, vr);

    METHOD_RETURN();
}

inline void encoding_base::s_static_decode(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Buffer_base> vr;

    METHOD_ENTER();

    METHOD_OVER(2, 1);

    ARG(exlib::string, 0);
    OPT_ARG(exlib::string, 1, "utf8");

    hr = decode(v0, v1, vr);

    METHOD_RETURN();
}

inline void encoding_base::s_static_jsstr(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_ENTER();

    METHOD_OVER(2, 1);

    ARG(exlib::string, 0);
    OPT_ARG(bool, 1, false);

    hr = jsstr(v0, v1, vr);

    METHOD_RETURN();
}

inline void encoding_base::s_static_encodeURI(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = encodeURI(v0, vr);

    METHOD_RETURN();
}

inline void encoding_base::s_static_encodeURIComponent(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = encodeURIComponent(v0, vr);

    METHOD_RETURN();
}

inline void encoding_base::s_static_decodeURI(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = decodeURI(v0, vr);

    METHOD_RETURN();
}
}
