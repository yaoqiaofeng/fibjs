/*
 * MemoryStream.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: lion
 */

#include "object.h"
#include "ifs/io.h"
#include "MemoryStream.h"
#include "Stat.h"
#include "Buffer.h"

namespace fibjs {

result_t MemoryStream_base::_new(obj_ptr<MemoryStream_base>& retVal, v8::Local<v8::Object> This)
{
    retVal = new MemoryStream();
    return 0;
}

result_t MemoryStream::get_fd(int32_t& retVal)
{
    return CALL_E_INVALID_CALL;
}

result_t MemoryStream::read(int32_t bytes, obj_ptr<Buffer_base>& retVal,
    AsyncEvent* ac)
{
    exlib::string strBuf;

    int64_t sz;
    int64_t p = m_buffer.tellg();

    m_buffer.seekg(0, std::ios::end);
    int64_t p1 = m_buffer.tellg();
    sz = p1 - p;
    m_buffer.seekg(p, std::ios::beg);

    if (bytes < 0 || bytes > sz)
        bytes = (int32_t)sz;

    if (bytes > 0) {
        if (p == 0 && bytes == (int32_t)sz) {
            strBuf = m_buffer.str();
            m_buffer.seekg(sz, std::ios::beg);
        } else {
            strBuf.resize(bytes);
            m_buffer.read(strBuf.c_buffer(), bytes);
        }

        m_buffer.seekp(m_buffer.tellg(), std::ios::beg);
    }

    if (strBuf.length() == 0)
        return CALL_RETURN_NULL;

    retVal = new Buffer(strBuf.c_str(), strBuf.length());

    return 0;
}

result_t MemoryStream::readAll(obj_ptr<Buffer_base>& retVal,
    AsyncEvent* ac)
{
    return read(-1, retVal, ac);
}

result_t MemoryStream::truncate(int64_t bytes, AsyncEvent* ac)
{
    std::string str = m_buffer.str();
    str.resize((size_t)bytes);
    m_buffer.str(str);

    m_time.now();

    return 0;
}

result_t MemoryStream::eof(bool& retVal)
{
    retVal = m_buffer.eof();
    return 0;
}

result_t MemoryStream::flush(AsyncEvent* ac)
{
    return 0;
}

result_t MemoryStream::write(Buffer_base* data, AsyncEvent* ac)
{
    Buffer* buf = Buffer::Cast(data);
    int64_t sz1, sz2;

    size(sz1);
    m_buffer.write((const char*)buf->data(), buf->length());
    m_buffer.seekg(m_buffer.tellp(), std::ios::beg);
    size(sz2);

    if (sz2 > sz1)
        extMemory((int32_t)(sz2 - sz1));

    m_time.now();

    return 0;
}

result_t MemoryStream::close(AsyncEvent* ac)
{
    return 0;
}

result_t MemoryStream::copyTo(Stream_base* stm, int64_t bytes, int64_t& retVal,
    AsyncEvent* ac)
{
    return io_base::copyStream(this, stm, bytes, retVal, ac);
}

result_t MemoryStream::stat(obj_ptr<Stat_base>& retVal, AsyncEvent* ac)
{
    obj_ptr<Stat> st = new Stat();

    st->init();
    st->m_isMemory = true;
    st->mtime = st->ctime = m_time;
    size(st->size);

    retVal = st;

    return 0;
}

result_t MemoryStream::seek(int64_t offset, int32_t whence)
{
    if (whence < fs_base::C_SEEK_SET || whence > fs_base::C_SEEK_END)
        return CHECK_ERROR(CALL_E_INVALIDARG);

    int64_t p = m_buffer.tellg();
    m_buffer.seekg(0, std::ios::end);
    int64_t sz = m_buffer.tellg();

    if (whence == fs_base::C_SEEK_CUR)
        offset += p;
    else if (whence == fs_base::C_SEEK_END)
        offset += sz;

    if (offset < 0)
        offset = 0;
    else if (offset > sz)
        offset = sz;

    m_buffer.seekg((int64_t)offset, std::ios::beg);
    m_buffer.seekp((int64_t)offset, std::ios::beg);

    return 0;
}

result_t MemoryStream::tell(int64_t& retVal)
{
    retVal = m_buffer.tellg();
    return 0;
}

result_t MemoryStream::rewind()
{
    m_buffer.seekg(0, std::ios::beg);
    m_buffer.seekp(0, std::ios::beg);
    return 0;
}

result_t MemoryStream::size(int64_t& retVal)
{
    int64_t p = m_buffer.tellg();

    m_buffer.seekg(0, std::ios::end);
    retVal = m_buffer.tellg();
    if (retVal < 0)
        retVal = 0;
    m_buffer.seekg(p, std::ios::beg);

    return 0;
}

result_t MemoryStream::setTime(date_t d)
{
    m_time = d;
    return 0;
}

result_t MemoryStream::clone(obj_ptr<MemoryStream_base>& retVal)
{
    retVal = new CloneStream(m_buffer.str(), m_time);
    return 0;
}

result_t MemoryStream::clear()
{
    rewind();
    m_buffer.str("");

    m_time.now();

    return 0;
}

} /* namespace fibjs */
