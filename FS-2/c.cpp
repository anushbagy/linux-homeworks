#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 91


int main(int argc, char** argv )
{
   // Check the number of command line arguments

   if(argc < 2)
   {
    std::cerr << " Provide path" << std::endl;
    exit(1);
   }

   char* file = argv[1];
   char* second_file = argv[2];

   // open with read only flag

   int fd= open(file, O_RDONLY);
   
   // checking 

   if(fd < 0)
   {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }
   
   char buff[BUFFER_SIZE ];
   
   // open file with flags

   int fd1 = open(second_file, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

   // checking

   if(fd1 < 0)
   {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }
   
   //read file

   while(true)
   {
      
      ssize_t read_bytes = read(fd, buff, BUFFER_SIZE);

      // checking
      if(read_bytes < 0)
      {
         std::cerr << strerror(errno) << std::endl;
         exit(errno);
        
      } 

      
      if(read_bytes == 0)
      {
        break;
      }
      
      // for new file

      ssize_t write_bytes = write(fd1, buff, read_bytes);

      // checking
      if(write_bytes < 0)
      {
         std::cerr << strerror(errno) << std::endl;
         exit(errno);
        
      } 

   }

   // closing file

   int close_file = close(fd);

   int close_second= close(fd1);
  //checking if it is correct

   if(close_file < 0)
   {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }

   if(close_second < 0)
   {
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }

   return 0;

}