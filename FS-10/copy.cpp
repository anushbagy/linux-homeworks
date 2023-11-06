#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <cmath>
#include <limits>



 int main(int argc, char** argv){

    //check the number of command line arguments
    if(argc < 3){
        std::cerr << "no path" << std::endl;
        exit(1);
    }

    //give source file path
    char* file = argv[1];
     //give destination file path
    char* copy_file = argv[2];
    
    //open file with read only
    int fd = open(file,O_RDONLY);

    //check if opens correct
    if(fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);  
    }

    //for counting data and hole bytes
    ssize_t value = 0;

    ssize_t data_count = 0;

    ssize_t hole_count = 0;

    //find hole 
    while(true){

        off_t data = lseek(fd,value,SEEK_HOLE);

        if(data > 0){

            hole_count = hole_count + (data - value); 

            std::cout << "hole" <<  hole_count << std::endl;

        value = data;
        }

        //get to the end
        if(data == 0){
            break;
        }

        //no data definition
        if(data < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);  
        }

        //find data
      off_t hole = lseek(fd,value,SEEK_DATA);

      if(hole < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);  
        }
      if(hole > 0){
        data_count = data_count + (data - value); 

            std::cout << "data" <<  data_count << std::endl;
         value = hole;
      }
      }

    
   

    //open coped file
    ssize_t copy_fd = open(copy_file,O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

     //check if opens correct
    if(copy_fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);  
    }

       // closing files

   int close_file = close(fd);

   int close_second= close(copy_fd);
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
 