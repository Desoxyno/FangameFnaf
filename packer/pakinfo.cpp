#include <fstream>
#include <iostream>

int main()
{
    uint32_t size;

    std::string file_needed = "buzzer_error.mp3";

    std::ifstream Data("./packer/data.pak", std::ios::binary | std::ios::in);

    Data.read(reinterpret_cast<char*>(&size), sizeof(size));

    std::cout << size;
}