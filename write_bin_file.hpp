#include<iostream>
#include<stdint.h>
#include<filesystem>
#include<fstream>

constexpr int FILE_WORD_LENGTH = 4;

void write_bin_file(std::filesystem::path file_path);