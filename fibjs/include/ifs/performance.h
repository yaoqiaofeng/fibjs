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

class performance_base : public object_base {
    DECLARE_CLASS(performance_base);

public:
    // performance_base
    static result_t now(double& retVal);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }

public:
    static void s_static_now(const v8::FunctionCallbackInfo<v8::Value>& args);
};
}

namespace fibjs {
inline ClassInfo& performance_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "now", s_static_now, true, false }
    };

    static ClassData s_cd = {
        "performance", true, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, 0, NULL, 0, NULL, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void performance_base::s_static_now(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    double vr;

    METHOD_ENTER();

    METHOD_OVER(0, 0);

    hr = now(vr);

    METHOD_RETURN();
}
}
