#include<sys/mman.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include<stdio.h>
#include <fcntl.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
// Time
#include<chrono>
#include<ctime>

#include "write_bin_file.hpp"

std::string get_current_time()
{
    auto now = std::chrono::system_clock::now();
    auto current_time = std::chrono::system_clock::to_time_t(now);
    std::string ctime = (std::ctime(&current_time));
    return ctime;
}

int main()
{   
    // Write a binary file to the working directory.
    namespace fs = std::filesystem;
    fs::path base_dir("/home/matt/git/mmfile/");
    fs::path file_path = base_dir / "mm.bin";
    std::string screenfetch_path = "/usr/bin/screenfetch";
    write_bin_file(file_path);

    // Open up the freshly written bin file.
    int fd = open("/home/matt/git/mmfile/mm.bin",O_RDWR);
    struct stat  sb;
    fstat(fd, &sb);
    
    size_t length = sb.st_size;
    // Open up the mmap
    void * mm = (mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED,fd,0));
    if (mm == MAP_FAILED)
    {
        std::cout << "Failed to map file.\n";
        perror("Error ");
        munmap(mm,length);
        close(fd);
        exit(1);
    }
    
    
    // Get the number of 32 bit words in bin file.
    int num_words = (int)(length/ sizeof(uint32_t));
    // Create a 32 bit buffer for mmap access
    uint32_t* buf = (uint32_t*)(mm);

    // Start to fork
    pid_t pi;
    pid_t p;
    int waitstatus;
    p=fork();
    // Fork 0 to print system info while parent process waits
    if(p<0)
    {
        perror("fork fail");
        exit(2);
    }
    else if(p==0)
    {       
        execl(screenfetch_path.c_str(),"screenfetch", "-N",(char *)(NULL));
    }
    else
    {
        // Waiting for screenfetch to complete.
        int w = waitpid(p, &waitstatus, WUNTRACED | WCONTINUED);
        while (!WIFEXITED(waitstatus) && !WIFSIGNALED(waitstatus))
        {
            sleep(1);
        }
        // screenfetch complete.
        // Spawn parallel processes to read and write to memory map.
        pi = fork();   
        if(pi < 0)
        {
            perror("fork fail");
            exit(1);
        }
        else if ( pi == 0)
        {
            // Periodically read memory map.
            for(int i = 5; i > 0; i--)
            {   
                std::cout << "Child PID: " << getpid() << std::endl;
                std::cout<< get_current_time() << std::endl;
                std::cout << "Reading Map Values:\n";
                for(int i=0; i < num_words; i++)
                {
                    printf("0x%X\n",buf[i]);
                }
                std::cout<< std::endl;
                sleep(1);
            }

        } 
        else
        {
            // Wait for some time and then write a value to the memory map.
            std::cout << "Parent PID: " << getpid() << std::endl;
            sleep(3);
            // Write a value
            std::cout << "Parent PID: " << getpid() << " Update buf[1]:"<<std::endl;
            std::cout<< get_current_time() << std::endl;
            buf[1] = 0xBAAAAAAD;
            printf("0x%X\n\n",buf[1]);
        }   
    }

    // Close Resources
    munmap(mm,length);
    close(fd);

    return 0;
}