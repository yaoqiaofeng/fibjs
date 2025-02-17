/*
 * _Message.cpp
 *
 *  Created on: Sep 2, 2012
 *      Author: lion
 */

#include "object.h"
#include "Message.h"
#include "MemoryStream.h"
#include "Buffer.h"
#include "ifs/json.h"
#include "ifs/msgpack.h"

namespace fibjs {

result_t Message::get_value(exlib::string& retVal)
{
    retVal = m_value;
    return 0;
}

result_t Message::set_value(exlib::string newVal)
{
    m_value = newVal;
    return 0;
}

result_t Message::get_params(obj_ptr<NArray>& retVal)
{
    if (m_params == NULL)
        m_params = new NArray();

    retVal = m_params;
    return 0;
}

result_t Message::get_type(int32_t& retVal)
{
    retVal = m_type;
    return 0;
}

result_t Message::set_type(int32_t newVal)
{
    m_type = newVal;
    return 0;
}

result_t Message::get_data(v8::Local<v8::Value>& retVal)
{
    if (m_body == NULL)
        return CALL_RETURN_NULL;

    result_t hr;
    obj_ptr<Buffer_base> data;

    m_body->rewind();
    hr = m_body->ac_readAll(data);
    if (hr < 0)
        return hr;

    if (hr == CALL_RETURN_NULL)
        return CALL_RETURN_NULL;

    if (m_type == C_TEXT) {
        exlib::string txt;

        data->toString(txt);
        retVal = holder()->NewString(txt);
    } else
        return data->valueOf(retVal);

    return 0;
}

result_t Message::get_body(obj_ptr<SeekableStream_base>& retVal)
{
    if (m_body == NULL)
        m_body = new MemoryStream();

    retVal = m_body;
    return 0;
}

result_t Message::set_body(SeekableStream_base* newVal)
{
    m_body = newVal;
    return 0;
}

result_t Message::read(int32_t bytes, obj_ptr<Buffer_base>& retVal,
    AsyncEvent* ac)
{
    if (m_body == NULL)
        return CALL_RETURN_NULL;

    return m_body->read(bytes, retVal, ac);
}

result_t Message::readAll(obj_ptr<Buffer_base>& retVal, AsyncEvent* ac)
{
    if (m_body == NULL)
        return CALL_RETURN_NULL;

    return m_body->readAll(retVal, ac);
}

result_t Message::write(Buffer_base* data, AsyncEvent* ac)
{
    if (m_body == NULL)
        m_body = new MemoryStream();

    return m_body->write(data, ac);
}

result_t Message::json(v8::Local<v8::Value> data, v8::Local<v8::Value>& retVal)
{
    m_body = new MemoryStream();

    exlib::string str;
    result_t hr = json_base::encode(data, str);
    if (hr < 0)
        return hr;

    obj_ptr<Buffer_base> buf = new Buffer(str.c_str(), str.length());
    return m_body->ac_write(buf);
}

result_t Message::json(v8::Local<v8::Value>& retVal)
{
    if (m_body == NULL)
        return CALL_RETURN_NULL;

    result_t hr;
    obj_ptr<Buffer_base> data;

    m_body->rewind();
    hr = m_body->ac_readAll(data);
    if (hr < 0)
        return hr;

    if (hr == CALL_RETURN_NULL)
        return CALL_RETURN_NULL;

    exlib::string str;
    data->toString(str);

    return json_base::decode(str, retVal);
}

result_t Message::pack(v8::Local<v8::Value> data, v8::Local<v8::Value>& retVal)
{
    m_body = new MemoryStream();

    obj_ptr<Buffer_base> buf;
    result_t hr = msgpack_base::encode(data, buf);
    if (hr < 0)
        return hr;

    return m_body->ac_write(buf);
}

result_t Message::pack(v8::Local<v8::Value>& retVal)
{
    if (m_body == NULL)
        return CALL_RETURN_NULL;

    result_t hr;
    obj_ptr<Buffer_base> data;

    m_body->rewind();
    hr = m_body->ac_readAll(data);
    if (hr < 0)
        return hr;

    if (hr == CALL_RETURN_NULL)
        return CALL_RETURN_NULL;

    return msgpack_base::decode(data, retVal);
}

result_t Message::get_length(int64_t& retVal)
{
    if (m_body == NULL) {
        retVal = 0;
        return 0;
    }
    return m_body->size(retVal);
}

result_t Message_base::_new(obj_ptr<Message_base>& retVal, v8::Local<v8::Object> This)
{
    retVal = new Message();
    return 0;
}

result_t Message::end()
{
    m_end = true;
    return 0;
}

result_t Message::isEnded(bool& retVal)
{
    retVal = m_end;
    return 0;
}

result_t Message::clear()
{
    m_end = false;
    m_params.Release();
    m_value.clear();
    m_body.Release();

    return 0;
}

result_t Message::sendTo(Stream_base* stm, AsyncEvent* ac)
{
    return CHECK_ERROR(CALL_E_INVALID_CALL);
}

result_t Message::readFrom(Stream_base* stm, AsyncEvent* ac)
{
    return CHECK_ERROR(CALL_E_INVALID_CALL);
}

result_t Message::get_stream(obj_ptr<Stream_base>& retVal)
{
    return CHECK_ERROR(CALL_E_INVALID_CALL);
}

result_t Message::get_lastError(exlib::string& retVal)
{
    retVal = m_lastError;
    return 0;
}

result_t Message::set_lastError(exlib::string newVal)
{
    m_lastError = newVal;
    return 0;
}

} /* namespace fibjs */
