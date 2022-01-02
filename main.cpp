#include <iostream>
#include <filesystem>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

#include "tee.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: No arguments provided." << std::endl;
        Tee::usage();
        return EXIT_FAILURE;
    }
    else if (argc > 3)
    {
        std::cerr << "Error: Too many arguments." << std::endl;
        Tee::usage();
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
                Tee::usage();
                return 0;
            }
            else file_path = argv[1];
        }
        else
        {
            if (std::strcmp(argv[1], "-a") != 0)
            {
                std::cerr << "Error: Unknown option " << argv[1] << std::endl;
                Tee::usage();
                return EXIT_FAILURE;
            }
            file_path = argv[2];
            is_append_mode = true;
        }

        Tee tee(file_path, is_append_mode);
        try
        {
            tee.start();
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    }

    return 0;
}
