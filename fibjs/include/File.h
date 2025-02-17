#pragma once

#include "ifs/File.h"
#include "Stat.h"
#include "utf8.h"
#include "Buffer.h"

#include <fcntl.h>

#ifndef _WIN32
#include <sys/ioctl.h>
#endif

#define MAX_PATH_LENGTH 4096

#ifndef F_OK
#define F_OK 0
#endif

#ifndef W_OK
#define W_OK 4
#endif

#ifndef R_OK
#define R_OK 2
#endif

#ifndef X_OK
#define X_OK 1
#endif

namespace fibjs {

class File : public File_base {
public:
    File()
        : m_fd(-1)
    {
    }

    File(int32_t fd)
        : m_fd(fd)
    {
    }

    ~File();

public:
    // Stream_base
    virtual result_t read(int32_t bytes, obj_ptr<Buffer_base>& retVal, AsyncEvent* ac);
    virtual result_t write(Buffer_base* data, AsyncEvent* ac);
    virtual result_t flush(AsyncEvent* ac);
    virtual result_t close(AsyncEvent* ac);
    virtual result_t copyTo(Stream_base* stm, int64_t bytes, int64_t& retVal, AsyncEvent* ac);

public:
    // SeekableStream_base
    virtual result_t seek(int64_t offset, int32_t whence);
    virtual result_t tell(int64_t& retVal);
    virtual result_t rewind();
    virtual result_t size(int64_t& retVal);
    virtual result_t readAll(obj_ptr<Buffer_base>& retVal, AsyncEvent* ac);
    virtual result_t truncate(int64_t bytes, AsyncEvent* ac);
    virtual result_t eof(bool& retVal);
    virtual result_t stat(obj_ptr<Stat_base>& retVal, AsyncEvent* ac);

public:
    // File_base
    virtual result_t get_name(exlib::string& retVal);
    virtual result_t get_fd(int32_t& retVal);
    virtual result_t chmod(int32_t mode, AsyncEvent* ac);

public:
    result_t open(exlib::string fname, exlib::string flags);
    result_t close();
    result_t Write(const char* p, int32_t sz);

    result_t Write(exlib::string data)
    {
        return Write(data.c_str(), (int32_t)data.length());
    }

    result_t Write(Buffer_base* data)
    {
        obj_ptr<Buffer> buf = Buffer::Cast(data);
        return Write((const char*)buf->data(), (int32_t)buf->length());
    }

protected:
    exlib::string name;
    int32_t m_fd;
};

inline result_t file_open(exlib::string fname, exlib::string flags, int32_t mode, int32_t& fd)
{
#ifdef _WIN32
    int32_t _flags = _O_BINARY;
#else
    int32_t _flags = 0;
#endif

    if (flags == "r")
        _flags |= O_RDONLY;
    else if (flags == "r+")
        _flags |= O_RDWR;
    else if (flags == "w")
        _flags |= O_TRUNC | O_CREAT | O_WRONLY;
    else if (flags == "w+")
        _flags |= O_TRUNC | O_CREAT | O_RDWR;
    else if (flags == "a")
        _flags |= O_APPEND | O_CREAT | O_WRONLY;
    else if (flags == "a+")
        _flags |= O_APPEND | O_CREAT | O_RDWR;

#ifdef _WIN32
    fd = _wopen(UTF8_W(fname), _flags, _S_IREAD | _S_IWRITE);
#else
    fd = ::open(fname.c_str(), _flags, mode);
#endif
    if (fd < 0)
        return CHECK_ERROR(LastError());

#ifndef _WIN32
    struct stat64 st;
    fstat64(fd, &st);

    if (S_IFDIR & st.st_mode) {
        ::_close(fd);
        fd = -1;
        return CHECK_ERROR(CALL_E_FILE_NOT_FOUND);
    }

    if (::fcntl(fd, F_SETFD, FD_CLOEXEC))
        return CHECK_ERROR(LastError());
#endif
    return 0;
}
}
