#include "io.h"

#include <cstring>
#include <stdexcept>
#include <cerrno>

namespace custom
{

IStream in;
OStream out;
ErrStream err;


// ===========IStream===========

IStream& IStream::get(char& c)
{
    is_eof_ = false;

    ssize_t num_of_bytes {::read(fd_, &c, 1)};

    if (num_of_bytes == 0)
        is_eof_ = true;
    else if (num_of_bytes == -1)
        throw std::runtime_error("System input call error: " +
                                 std::string(std::strerror(errno)));

    return *this;
}

IStream& IStream::getline(std::string& str, char delim)
{
    is_eof_ = false;

    str.erase();

    char buf[256]        {0};
    ssize_t num_of_bytes {sizeof(buf)};
    bool is_delim        {false};

    size_t chars_to_append;

    while(!(num_of_bytes < sizeof(buf) || is_delim))
    {
        num_of_bytes = ::read(fd_, buf, sizeof(buf));

        if (num_of_bytes <= 0)
            break;

        is_delim = buf[num_of_bytes - 1] == endl;
        chars_to_append = is_delim ? num_of_bytes - 1
                                   : num_of_bytes;

        str.append(buf, chars_to_append);
    }

    if (num_of_bytes == 0)
        is_eof_ = true;
    else if (num_of_bytes == -1)
        throw std::runtime_error("System input call error: " +
                                 std::string(std::strerror(errno)));

    return *this;
}

IStream& IStream::read_all(std::string& str)
{
    is_eof_ = false;

    str.erase();

    char buf[256]        {0};
    ssize_t num_of_bytes {sizeof(buf)};

    while(num_of_bytes == sizeof(buf))
    {
        num_of_bytes = ::read(fd_, buf, sizeof(buf));

        if (num_of_bytes <= 0)
            break;

        str.append(buf, num_of_bytes);
    }

    if (num_of_bytes == 0)
        is_eof_ = true;
    else if (num_of_bytes == -1)
        throw std::runtime_error("System input call error: " +
                                 std::string(std::strerror(errno)));

    return *this;
}


// ===========OStream===========

OStream& OStream::put(char c)
{
    ssize_t num_of_bytes {::write(fd_, &c, 1)};

    if (num_of_bytes == -1)
        throw std::runtime_error("System output call error: " +
                                 std::string(std::strerror(errno)));
    return *this;
}

OStream& OStream::write(const std::string& str)
{
    ssize_t num_of_bytes {::write(fd_, str.data(), str.size())};

    if (num_of_bytes == -1)
        throw std::runtime_error("System output call error: " +
                                 std::string(std::strerror(errno)));
    return *this;
}

} // namespace custom
