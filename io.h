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
        IStream(int fd = STDIN_FILENO) : fd_{fd} {}
        virtual ~IStream() = default;

        /**
         * @brief Extract one character from the stream
         * 
         * @param[out] c The character in which to store data
         * @return *this
         */
        IStream& get(char& c);

        /**
         * @brief Extract characters from an input stream to the string until delimiter
         * 
         * @param[out] str The string in which to store data
         * @return *this
         * 
         * Extracts characters to string until delimiter character is reached.
         * The delimiter character is extracted, but is not appended to string.
         * The default delimiter is the endline ('\\n') character.
         */
        IStream& getline(std::string& str, char delim = endl);

        /**
         * @brief Extract characters from an input stream to the string until EOF
         * 
         * @param[out] str The string in which to store data
         * @return *this
         */
        IStream& read_all(std::string& str);

        IStream& operator>>(char& c)          { return get(c); }
        IStream& operator>>(std::string& str) { return getline(str); }

        /**
         * @return true if EOF is not reached, false otherwise
         */
        constexpr operator bool() const { return !is_eof_; }

    protected:
        int fd_; // File descriptor
        bool is_eof_ {false};
    };

    /**
     * @brief Custom output stream which wraps Linux output system calls
     */
    class OStream
    {
    public:
        OStream(int fd = STDOUT_FILENO) : fd_{fd} {}
        virtual ~OStream() = default;

        /**
         * @brief Insert one character to the stream
         * 
         * @param[in] c The character to insert
         * @return *this
         */
        OStream& put(char c);

        /**
         * @brief Insert string into the stream
         * 
         * @param[in] str The string to insert
         * @return *this
         */
        OStream& write(const std::string& str);
        OStream& write(const char* str) { return write(std::string(str)); }

        OStream& operator<<(char c)                 { return put(c); }
        OStream& operator<<(const std::string& str) { return write(str); }
        OStream& operator<<(const char* str)        { return write(str); }

    protected:
        int fd_; // File descriptor
    };

    /**
     * @brief Custom error output stream which wraps Linux output system calls
     */
    class ErrStream : public OStream
    {
    public:
        ErrStream(int fd = STDERR_FILENO) : OStream(fd) {}
    };

    extern IStream in;    // Custom stream object linked to standard input
    extern OStream out;   // Custom stream object linked to standard output
    extern ErrStream err; // Custom stream object linked to standard error output

} // namespace custom

#endif // IO_H
