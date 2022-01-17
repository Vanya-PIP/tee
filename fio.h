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
     * @brief File stream open modes
     */
    namespace openmode
    {
        static constexpr int app      {O_APPEND};
        static constexpr int in_only  {O_RDONLY};
        static constexpr int out_only {O_WRONLY};
        static constexpr int in_out   {O_RDWR  };
        static constexpr int trunc    {O_TRUNC };
    }

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
         * @param[in] pathname Path to file
         * @param[in] openmode Specifies stream open mode
         */
        FOStream(const std::string& pathname, int openmode = 0)
        {
            open(pathname, openmode);
        }
        FOStream(const std::filesystem::path& path, int openmode = 0)
        {
            open(path, openmode);
        }
        FOStream(const char* pathname, int openmode = 0)
        {
            open(pathname, openmode);
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
         * @param[in] pathname Path to file
         * @param[in] openmode    Specifies stream open mode
         */
        void open(const std::string& pathname, int openmode = 0);
        void open(const std::filesystem::path& path, int openmode = 0)
        {
            open(path.string(), openmode);
        }
        void open(const char* pathname, int openmode = 0)
        {
            open(std::string(pathname), openmode);
        }

        void close();

        constexpr bool is_open() const  { return is_open_; }
        constexpr operator bool() const { return is_open(); }

    protected:
        bool is_open_ {false};

    private:
        static constexpr int default_openmode_ {openmode::out_only | O_CREAT | O_SYNC};
    };

} // namespace custom

#endif // FIO_H
