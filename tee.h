#ifndef TEE_H
#define TEE_H

#include <iostream>
#include <string>
#include <filesystem>

class Tee
{
public:
    Tee(const std::filesystem::path& file_path, bool is_append_mode);

    void start();

    static void usage()
    {
        std::cout << "Usage: tee [-a] <file_name>" << std::endl;
    };

private:
    void write(char c);

    const std::filesystem::path file_path_;
    size_t current_position_;
};

#endif // TEE_H
