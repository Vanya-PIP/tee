#ifndef IO_H
#define IO_H

#include <string>

// POSIX
#include <unistd.h>

/**
 * @brief Custom I/O streams
 */
namespace custom
{
    constexpr char endl {'\n'};

    /**
     * @brief Custom input stream which wraps Linux input system calls
     */
    class IStream
    {
    public:
        virtual ~IStream() = default;

        /**
         * @brief Extract one character from the stream
         * 
         * @param[out] c The character in which to store data
         * @return *this
         */
        IStream& get(char& c);

        /**
         * @brief Extract one line from the stream
         * 
         * @param[out] str The string in which to store data
         * @return *this
         * 
         * Saves characters to string excluding the end of line ('\\n') character
         */
        IStream& getline(std::string& str);

        IStream& operator>>(char& c)          {return get(c);}
        IStream& operator>>(std::string& str) {return getline(str);}

        /**
         * @return true if EOF is not reached, false otherwise
         */
        constexpr operator bool() const {return !is_eof_;}

    protected:
        int fd_      {STDIN_FILENO}; // File descriptor
        bool is_eof_ {false};
    };

    /**
     * @brief Custom output stream which wraps Linux output system calls
     */
    class OStream
    {
    public:
        virtual ~OStream() = default;

        /**
         * @brief Insert one character to the stream
         * 
         * @param[in] c The character to insert
         * @return *this
         */
        virtual OStream& put(char c);

        /**
         * @brief Insert string into the stream
         * 
         * @param[in] str The string to insert
         * @return *this
         */
        virtual OStream& write(const std::string& str);
        OStream& write(const char* str) {return write(std::string(str));}

        OStream& operator<<(char c)                 {return put(c);}
        OStream& operator<<(const std::string& str) {return write(str);}
        OStream& operator<<(const char* str)        {return write(str);}

    protected:
        int fd_ {STDOUT_FILENO}; // File descriptor
    };

    extern IStream in;  // Custom stream object linked to standard input
    extern OStream out; // Custom stream object linked to standard output

} // namespace custom

#endif // IO_H
