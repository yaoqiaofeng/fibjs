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

class StringDecoder_base;

class string_decoder_base : public object_base {
    DECLARE_CLASS(string_decoder_base);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }
};
}

#include "ifs/StringDecoder.h"

namespace fibjs {
inline ClassInfo& string_decoder_base::class_info()
{
    static ClassData::ClassObject s_object[] = {
        { "StringDecoder", StringDecoder_base::class_info }
    };

    static ClassData s_cd = {
        "string_decoder", true, s__new, NULL,
        0, NULL, ARRAYSIZE(s_object), s_object, 0, NULL, 0, NULL, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}
}
