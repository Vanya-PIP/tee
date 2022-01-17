#include <filesystem>
#include <cstring>
#include <stdexcept>

#include "fio.h"

inline void usage()
{
    custom::out << "Usage: tee [-a] filename" << custom::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        custom::err << "Error: No arguments provided." << custom::endl;
        usage();
        return EXIT_FAILURE;
    }
    else if (argc > 3)
    {
        custom::err << "Error: Too many arguments." << custom::endl;
        usage();
        return EXIT_FAILURE;
    }
    else
    {
        std::filesystem::path file_path;
        bool is_append_mode {false};

        if (argc == 2)
        {
            if (std::strcmp(argv[1], "-h") == 0)
            {
                usage();
                return 0;
            }
            else file_path = argv[1];
        }
        else
        {
            if (std::strcmp(argv[1], "-a") != 0)
            {
                custom::err << "Error: Unknown option " << argv[1] << custom::endl;
                usage();
                return EXIT_FAILURE;
            }
            file_path = argv[2];
            is_append_mode = true;
        }

        try
        {
            auto mode {is_append_mode ? custom::openmode::app
                                      : custom::openmode::trunc};
            custom::FOStream file {file_path, mode};
            std::string buf;
            while (custom::in.read_all(buf))
            {
                custom::out << buf;
                file << buf;
            }
        }
        catch (const std::runtime_error& e)
        {
            custom::err << e.what() << custom::endl;
            return EXIT_FAILURE;
        }
    }

    return 0;
}
