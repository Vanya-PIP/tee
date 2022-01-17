#include "fio.h"

#include <cstring>
#include <cerrno>

namespace custom
{

void FOStream::open(const std::string& pathname, int openmode)
{
    openmode = default_openmode_ | openmode;
    fd_ = ::open(pathname.c_str(), openmode);

    if (fd_ == -1)
    {
        is_open_ = false;
        throw std::runtime_error("System file open call error: " +
                                 std::string(std::strerror(errno)));
    }
    else
        is_open_ = true;
}

void FOStream::close()
{
    int result {::close(fd_)};

    if (result == -1)
    {
        throw std::runtime_error("System file close call error: " +
                                 std::string(std::strerror(errno)));
    }
    else
    {
        is_open_ = false;
        fd_ = -1;
    }
}

} // namespace custom
