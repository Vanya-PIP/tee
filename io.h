#ifndef IO_H
#define IO_H

#include <string>

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
         * @param c The character in which to store data
         * @return *this
         */
        IStream& get(char& c);

        /**
         * @brief Extract one line from the stream
         * 
         * @param str The string in which to store data
         * @return *this
         * 
         * @details Saves characters to string excluding the end of line ('\\n') character
         */
        IStream& getline(std::string& str);

        IStream& operator>>(char& c)          {return get(c);}
        IStream& operator>>(std::string& str) {return getline(str);};

        /**
         * @return true if EOF is not reached, false otherwise
         */
        constexpr operator bool() const {return !is_eof_;}

    protected:
        int fd_      {0};
        bool is_eof_ {false};
    };

    extern IStream in; // Custom stream object linked to standard input

} // namespace custom

#endif // IO_H
