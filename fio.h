#ifndef FIO_H
#define FIO_H

# include "io.h"

#include <filesystem>
#include <stdexcept>

// POSIX
#include <fcntl.h>

namespace custom
{
    /**
     * @brief Custom file output stream which wraps Linux output system calls
     */
    class FOStream : public OStream
    {
    public:
        FOStream(int fd = -1) : OStream(fd) {}

        /**
         * @brief Construct a new FOStream object and open it
         * 
         * @param pathname Path to file
         * @param flags    Specifies stream open mode
         */
        FOStream(const std::string& pathname, int flags = default_flags_)
        {
            open(pathname, flags);
        }
        FOStream(const std::filesystem::path& path, int flags = default_flags_)
        {
            open(path, flags);
        }
        FOStream(const char* pathname, int flags = default_flags_)
        {
            open(pathname, flags);
        }
        ~FOStream()
        {
            try
            {
                if (is_open())
                    close();
            }
            catch (const std::runtime_error& e) {}
        }

        /**
         * @brief Open or create a file for writing
         * 
         * @param pathname Path to file
         * @param flags    Specifies stream open mode
         */
        void open(const std::string& pathname, int flags = default_flags_);
        void open(const std::filesystem::path& path, int flags = default_flags_)
        {
            open(path.string(), flags);
        }
        void open(const char* pathname, int flags = default_flags_)
        {
            open(std::string(pathname), flags);
        }

        void close();

        constexpr bool is_open() const  { return is_open_; }
        constexpr operator bool() const { return is_open(); }

    protected:
        bool is_open_ {false};

    private:
        static constexpr int default_flags_ {O_WRONLY | O_CREAT | O_TRUNC | O_SYNC};
    };

} // namespace custom

#endif // FIO_H
