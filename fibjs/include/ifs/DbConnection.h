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

class DbConnection_base : public object_base {
    DECLARE_CLASS(DbConnection_base);

public:
    // DbConnection_base
    virtual result_t get_type(exlib::string& retVal) = 0;
    virtual result_t close(AsyncEvent* ac) = 0;
    virtual result_t use(exlib::string dbName, AsyncEvent* ac) = 0;
    virtual result_t begin(exlib::string point, AsyncEvent* ac) = 0;
    virtual result_t commit(exlib::string point, AsyncEvent* ac) = 0;
    virtual result_t rollback(exlib::string point, AsyncEvent* ac) = 0;
    virtual result_t trans(v8::Local<v8::Function> func, bool& retVal) = 0;
    virtual result_t trans(exlib::string point, v8::Local<v8::Function> func, bool& retVal) = 0;
    virtual result_t execute(exlib::string sql, obj_ptr<NArray>& retVal, AsyncEvent* ac) = 0;
    virtual result_t execute(exlib::string sql, OptArgs args, obj_ptr<NArray>& retVal, AsyncEvent* ac) = 0;
    virtual result_t createTable(v8::Local<v8::Object> opts, AsyncEvent* ac) = 0;
    virtual result_t dropTable(v8::Local<v8::Object> opts, AsyncEvent* ac) = 0;
    virtual result_t createIndex(v8::Local<v8::Object> opts, AsyncEvent* ac) = 0;
    virtual result_t dropIndex(v8::Local<v8::Object> opts, AsyncEvent* ac) = 0;
    virtual result_t insert(v8::Local<v8::Object> opts, double& retVal, AsyncEvent* ac) = 0;
    virtual result_t find(v8::Local<v8::Object> opts, obj_ptr<NArray>& retVal, AsyncEvent* ac) = 0;
    virtual result_t count(v8::Local<v8::Object> opts, int32_t& retVal, AsyncEvent* ac) = 0;
    virtual result_t update(v8::Local<v8::Object> opts, int32_t& retVal, AsyncEvent* ac) = 0;
    virtual result_t remove(v8::Local<v8::Object> opts, int32_t& retVal, AsyncEvent* ac) = 0;
    virtual result_t format(exlib::string method, v8::Local<v8::Object> opts, exlib::string& retVal) = 0;
    virtual result_t format(exlib::string sql, OptArgs args, exlib::string& retVal) = 0;

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }

public:
    static void s_get_type(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_close(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_use(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_begin(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_commit(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_rollback(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_trans(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_execute(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_createTable(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_dropTable(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_createIndex(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_dropIndex(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_insert(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_find(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_count(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_update(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_remove(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_format(const v8::FunctionCallbackInfo<v8::Value>& args);

public:
    ASYNC_MEMBER0(DbConnection_base, close);
    ASYNC_MEMBER1(DbConnection_base, use, exlib::string);
    ASYNC_MEMBER1(DbConnection_base, begin, exlib::string);
    ASYNC_MEMBER1(DbConnection_base, commit, exlib::string);
    ASYNC_MEMBER1(DbConnection_base, rollback, exlib::string);
    ASYNC_MEMBERVALUE2(DbConnection_base, execute, exlib::string, obj_ptr<NArray>);
    ASYNC_MEMBERVALUE3(DbConnection_base, execute, exlib::string, OptArgs, obj_ptr<NArray>);
    ASYNC_MEMBER1(DbConnection_base, createTable, v8::Local<v8::Object>);
    ASYNC_MEMBER1(DbConnection_base, dropTable, v8::Local<v8::Object>);
    ASYNC_MEMBER1(DbConnection_base, createIndex, v8::Local<v8::Object>);
    ASYNC_MEMBER1(DbConnection_base, dropIndex, v8::Local<v8::Object>);
    ASYNC_MEMBERVALUE2(DbConnection_base, insert, v8::Local<v8::Object>, double);
    ASYNC_MEMBERVALUE2(DbConnection_base, find, v8::Local<v8::Object>, obj_ptr<NArray>);
    ASYNC_MEMBERVALUE2(DbConnection_base, count, v8::Local<v8::Object>, int32_t);
    ASYNC_MEMBERVALUE2(DbConnection_base, update, v8::Local<v8::Object>, int32_t);
    ASYNC_MEMBERVALUE2(DbConnection_base, remove, v8::Local<v8::Object>, int32_t);
};
}

namespace fibjs {
inline ClassInfo& DbConnection_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "close", s_close, false, true },
        { "closeSync", s_close, false, false },
        { "use", s_use, false, true },
        { "useSync", s_use, false, false },
        { "begin", s_begin, false, true },
        { "beginSync", s_begin, false, false },
        { "commit", s_commit, false, true },
        { "commitSync", s_commit, false, false },
        { "rollback", s_rollback, false, true },
        { "rollbackSync", s_rollback, false, false },
        { "trans", s_trans, false, false },
        { "execute", s_execute, false, true },
        { "executeSync", s_execute, false, false },
        { "createTable", s_createTable, false, true },
        { "createTableSync", s_createTable, false, false },
        { "dropTable", s_dropTable, false, true },
        { "dropTableSync", s_dropTable, false, false },
        { "createIndex", s_createIndex, false, true },
        { "createIndexSync", s_createIndex, false, false },
        { "dropIndex", s_dropIndex, false, true },
        { "dropIndexSync", s_dropIndex, false, false },
        { "insert", s_insert, false, true },
        { "insertSync", s_insert, false, false },
        { "find", s_find, false, true },
        { "findSync", s_find, false, false },
        { "count", s_count, false, true },
        { "countSync", s_count, false, false },
        { "update", s_update, false, true },
        { "updateSync", s_update, false, false },
        { "remove", s_remove, false, true },
        { "removeSync", s_remove, false, false },
        { "format", s_format, false, false }
    };

    static ClassData::ClassProperty s_property[] = {
        { "type", s_get_type, block_set, false }
    };

    static ClassData s_cd = {
        "DbConnection", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void DbConnection_base::s_get_type(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_INSTANCE(DbConnection_base);
    PROPERTY_ENTER();

    hr = pInst->get_type(vr);

    METHOD_RETURN();
}

inline void DbConnection_base::s_close(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(0, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_close(cb, args);
    else
        hr = pInst->ac_close();

    METHOD_VOID();
}

inline void DbConnection_base::s_use(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_use(v0, cb, args);
    else
        hr = pInst->ac_use(v0);

    METHOD_VOID();
}

inline void DbConnection_base::s_begin(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 0);

    OPT_ARG(exlib::string, 0, "");

    if (!cb.IsEmpty())
        hr = pInst->acb_begin(v0, cb, args);
    else
        hr = pInst->ac_begin(v0);

    METHOD_VOID();
}

inline void DbConnection_base::s_commit(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 0);

    OPT_ARG(exlib::string, 0, "");

    if (!cb.IsEmpty())
        hr = pInst->acb_commit(v0, cb, args);
    else
        hr = pInst->ac_commit(v0);

    METHOD_VOID();
}

inline void DbConnection_base::s_rollback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 0);

    OPT_ARG(exlib::string, 0, "");

    if (!cb.IsEmpty())
        hr = pInst->acb_rollback(v0, cb, args);
    else
        hr = pInst->ac_rollback(v0);

    METHOD_VOID();
}

inline void DbConnection_base::s_trans(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    bool vr;

    METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Function>, 0);

    hr = pInst->trans(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(v8::Local<v8::Function>, 1);

    hr = pInst->trans(v0, v1, vr);

    METHOD_RETURN();
}

inline void DbConnection_base::s_execute(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<NArray> vr;

    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_execute(v0, cb, args);
    else
        hr = pInst->ac_execute(v0, vr);

    ASYNC_METHOD_OVER(-1, 1);

    ARG(exlib::string, 0);
    ARG_LIST(1);

    if (!cb.IsEmpty())
        hr = pInst->acb_execute(v0, v1, cb, args);
    else
        hr = pInst->ac_execute(v0, v1, vr);

    METHOD_RETURN();
}

inline void DbConnection_base::s_createTable(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_createTable(v0, cb, args);
    else
        hr = pInst->ac_createTable(v0);

    METHOD_VOID();
}

inline void DbConnection_base::s_dropTable(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_dropTable(v0, cb, args);
    else
        hr = pInst->ac_dropTable(v0);

    METHOD_VOID();
}

inline void DbConnection_base::s_createIndex(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_createIndex(v0, cb, args);
    else
        hr = pInst->ac_createIndex(v0);

    METHOD_VOID();
}

inline void DbConnection_base::s_dropIndex(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_dropIndex(v0, cb, args);
    else
        hr = pInst->ac_dropIndex(v0);

    METHOD_VOID();
}

inline void DbConnection_base::s_insert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    double vr;

    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_insert(v0, cb, args);
    else
        hr = pInst->ac_insert(v0, vr);

    METHOD_RETURN();
}

inline void DbConnection_base::s_find(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<NArray> vr;

    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_find(v0, cb, args);
    else
        hr = pInst->ac_find(v0, vr);

    METHOD_RETURN();
}

inline void DbConnection_base::s_count(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_count(v0, cb, args);
    else
        hr = pInst->ac_count(v0, vr);

    METHOD_RETURN();
}

inline void DbConnection_base::s_update(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_update(v0, cb, args);
    else
        hr = pInst->ac_update(v0, vr);

    METHOD_RETURN();
}

inline void DbConnection_base::s_remove(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    ASYNC_METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_remove(v0, cb, args);
    else
        hr = pInst->ac_remove(v0, vr);

    METHOD_RETURN();
}

inline void DbConnection_base::s_format(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_INSTANCE(DbConnection_base);
    METHOD_ENTER();

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(v8::Local<v8::Object>, 1);

    hr = pInst->format(v0, v1, vr);

    METHOD_OVER(-1, 1);

    ARG(exlib::string, 0);
    ARG_LIST(1);

    hr = pInst->format(v0, v1, vr);

    METHOD_RETURN();
}
}
