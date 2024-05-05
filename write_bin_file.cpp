
#include "write_bin_file.hpp"

void write_bin_file(std::filesystem::path file_path)
{
    uint32_t a[FILE_WORD_LENGTH] = {0xdeadc0de,0xbeeffeed,0xdeadf0df,0xbeefbead};
    std::ofstream wf(file_path.generic_string(), std::ios::out | std::ios::binary);
    for(int i=0; i<4; i++)
    {
        wf.write((char *)(&(a[i])),sizeof(uint32_t));
    }
    wf.close();
}