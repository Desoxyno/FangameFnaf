#include "archive.h"

#include <filesystem>
#include <fstream>
#include <iostream>

int main()
{
    std::ofstream Data("./packer/data.pak", std::ios::binary);

    std::string filepath = "./assets/sounds/buzzer_error.mp3";

    std::ifstream file(filepath, std::ios::binary);

    if (!file)
    {
        std::cerr << "Error opening the file\n";
        return 1;
    }

    std::filesystem::path p(filepath);

    uint64_t size = std::filesystem::file_size(p);
    std::string filename = p.filename().string();

    uint64_t filenameSize = filename.size();

    Data.write(reinterpret_cast<char*>(&filenameSize), sizeof(filenameSize));
    Data.write(filename.data(), filenameSize);

    Data.write(reinterpret_cast<char*>(&size), sizeof(size));

    char byte;

    for (uint64_t i = 0; i < size; i++)
    {
        file.read(&byte, 1);
        Data.write(&byte, 1);
    }

    Data.close();
    file.close();

    std::cout << "Packed: " << filename << "\n";
}