#include "tee.h"

#include <fstream>

Tee::Tee(const std::filesystem::path& file_path, bool is_append_mode) :
    file_path_{file_path}
{
    std::fstream file;

    auto mode {is_append_mode ? (std::fstream::out | std::fstream::app)
                              : std::fstream::out};
    file.open(file_path_, mode);
    if (!file)
        throw std::runtime_error("Error: couldn't open file " +
                                 file_path_.string());

    current_position_ = file.tellp();

    file.close();
}

void Tee::start()
{
    char c;
    while (std::cin.get(c))
    {
        std::cout << c;
        write(c);
    }
}

void Tee::write(char c)
{
    std::fstream file;
    file.open(file_path_);
    if (!file)
        throw std::runtime_error("Error: couldn't open file " +
                                 file_path_.string());

    file.seekp(current_position_);
    file.put(c);
    current_position_++;

    file.close();
}
