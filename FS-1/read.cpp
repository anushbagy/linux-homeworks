#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 200

 int main(int argc , char** argv){
    if(argc < 2){

        //check the number of command-line arguments

        std::cerr << "There is no path "<<std::endl;
        exit(1);
    }
    char* file = argv[1];

    // open with flag read only

    int fd = open(file,O_RDONLY);

   //check if it calls correct

    if(fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


    // make buffer with buffer_size

    char buff[BUFFER_SIZE + 1];

    //read file 

    while(true){
     ssize_t read_bytes = read(fd, buff, BUFFER_SIZE);
    
    // checking 

     if(read_bytes < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
     }
     if(read_bytes == 0){
        break;
     }      
    
    // if it reachs the end '\0'

   buff[read_bytes + 1] = '\0';
   std::cout << buff;
    }
   //close file
   int close_file = close(fd);
   if(close_file < 0){
    std::cerr << strerror(errno)<<std::endl;
   }
    return 0;
 }