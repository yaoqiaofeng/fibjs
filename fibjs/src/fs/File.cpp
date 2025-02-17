/*
 * File.cpp
 *
 *  Created on: Apr 7, 2012
 *      Author: lion
 */

#ifndef _WIN32
#define _FILE_OFFSET_BITS 64
#endif

#include "object.h"

#include "ifs/io.h"
#include "ifs/fs.h"
#include "File.h"
#include "Buffer.h"

#ifdef _WIN32
#define pclose _pclose
#endif

namespace fibjs {

File::~File()
{
    if (m_fd != -1)
        asyncCall(::_close, m_fd);
}

result_t File::read(int32_t bytes, obj_ptr<Buffer_base>& retVal,
    AsyncEvent* ac)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    exlib::string strBuf;

    if (bytes < 0) {
        int64_t p = _lseeki64(m_fd, 0, SEEK_CUR);
        if (p < 0)
            return CHECK_ERROR(LastError());

        int64_t sz = _lseeki64(m_fd, 0, SEEK_END);
        if (sz < 0)
            return CHECK_ERROR(LastError());

        if (_lseeki64(m_fd, p, SEEK_SET) < 0)
            return CHECK_ERROR(LastError());

        sz -= p;

        if (sz > STREAM_BUFF_SIZE)
            sz = STREAM_BUFF_SIZE;

        bytes = (int32_t)sz;
    }

    if (bytes > 0) {
        strBuf.resize(bytes);
        int32_t sz = bytes;
        char* p = strBuf.c_buffer();

        while (sz) {
            int32_t n = (int32_t)::_read(m_fd, p, sz > STREAM_BUFF_SIZE ? STREAM_BUFF_SIZE : sz);
            if (n < 0)
                return CHECK_ERROR(LastError());
            if (n == 0)
                break;

            sz -= n;
            p += n;
        }

        strBuf.resize(bytes - sz);
    }

    if (strBuf.length() == 0)
        return CALL_RETURN_NULL;

    retVal = new Buffer(strBuf.c_str(), strBuf.length());

    return 0;
}

result_t File::readAll(obj_ptr<Buffer_base>& retVal, AsyncEvent* ac)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    exlib::string strBuf;

    int32_t bytes;
    int64_t p = _lseeki64(m_fd, 0, SEEK_CUR);
    if (p < 0)
        return CHECK_ERROR(LastError());

    int64_t sz = _lseeki64(m_fd, 0, SEEK_END);
    if (sz < 0)
        return CHECK_ERROR(LastError());

    if (_lseeki64(m_fd, p, SEEK_SET) < 0)
        return CHECK_ERROR(LastError());

    sz -= p;

    bytes = (int32_t)sz;

    if (bytes > 0) {
        strBuf.resize(bytes);
        int32_t sz = bytes;
        char* p = strBuf.c_buffer();

        while (sz) {
            int32_t n = (int32_t)::_read(m_fd, p, sz > STREAM_BUFF_SIZE ? STREAM_BUFF_SIZE : sz);
            if (n < 0)
                return CHECK_ERROR(LastError());
            if (n == 0)
                break;

            sz -= n;
            p += n;
        }

        strBuf.resize(bytes - sz);
    }

    if (strBuf.length() == 0)
        return CALL_RETURN_NULL;

    retVal = new Buffer(strBuf.c_str(), strBuf.length());

    return 0;
}

result_t File::Write(const char* p, int32_t sz)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    while (sz) {
        int32_t n = (int32_t)::_write(m_fd, p, sz > STREAM_BUFF_SIZE ? STREAM_BUFF_SIZE : sz);
        if (n < 0)
            return CHECK_ERROR(LastError());

        sz -= n;
        p += n;
    }

    return 0;
}

result_t File::write(Buffer_base* data, AsyncEvent* ac)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    return Write(data);
}

result_t File::copyTo(Stream_base* stm, int64_t bytes, int64_t& retVal,
    AsyncEvent* ac)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    return io_base::copyStream(this, stm, bytes, retVal, ac);
}

result_t File::open(exlib::string fname, exlib::string flags)
{
    close();
    name = fname;
    return file_open(fname, flags, 0666, m_fd);
}

result_t File::get_name(exlib::string& retVal)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    retVal = name;
    return 0;
}

result_t File::get_fd(int32_t& retVal)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    retVal = m_fd;
    return 0;
}

result_t File::stat(obj_ptr<Stat_base>& retVal, AsyncEvent* ac)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    return fs_base::stat(name, retVal, ac);
}

result_t File::size(int64_t& retVal)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    int64_t p = _lseeki64(m_fd, 0, SEEK_CUR);
    if (p < 0)
        return CHECK_ERROR(LastError());

    int64_t sz = _lseeki64(m_fd, 0, SEEK_END);
    if (sz < 0)
        return CHECK_ERROR(LastError());

    if (_lseeki64(m_fd, p, SEEK_SET) < 0)
        return CHECK_ERROR(LastError());

    retVal = sz;
    return 0;
}

result_t File::eof(bool& retVal)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    int64_t p = _lseeki64(m_fd, 0, SEEK_CUR);
    if (p < 0)
        return CHECK_ERROR(LastError());

    int64_t sz = _lseeki64(m_fd, 0, SEEK_END);
    if (sz < 0)
        return CHECK_ERROR(LastError());

    if (_lseeki64(m_fd, p, SEEK_SET) < 0)
        return CHECK_ERROR(LastError());

    retVal = sz == p;

    return 0;
}

result_t File::seek(int64_t offset, int32_t whence)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    if (_lseeki64(m_fd, offset, whence) < 0)
        return CHECK_ERROR(LastError());

    return 0;
}

result_t File::tell(int64_t& retVal)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    retVal = _lseeki64(m_fd, 0, SEEK_CUR);
    if (retVal < 0)
        return CHECK_ERROR(LastError());

    return 0;
}

result_t File::rewind()
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    if (_lseeki64(m_fd, 0, SEEK_SET) < 0)
        return CHECK_ERROR(LastError());

    return 0;
}

result_t File::flush(AsyncEvent* ac)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    //    fflush(m_file);

    //    if (ferror(m_file))
    //        return CHECK_ERROR(LastError());

    return 0;
}

result_t File::close()
{
    if (m_fd != -1) {
        ::_close(m_fd);
        m_fd = -1;
    }

    return 0;
}

result_t File::close(AsyncEvent* ac)
{
    if (m_fd != -1) {
        if (ac->isSync())
            return CHECK_ERROR(CALL_E_NOSYNC);

        return close();
    }

    return 0;
}

result_t File::truncate(int64_t bytes, AsyncEvent* ac)
{
    if (m_fd == -1)
        return CHECK_ERROR(CALL_E_INVALID_CALL);

    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    if (ftruncate64(m_fd, bytes) < 0)
        return CHECK_ERROR(LastError());

    return 0;
}

result_t File::chmod(int32_t mode, AsyncEvent* ac)
{
#ifdef _WIN32
    return CHECK_ERROR(CALL_E_INVALID_CALL);
#else
    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    if (::fchmod(m_fd, mode))
        return CHECK_ERROR(LastError());

    return 0;
#endif
}
}
