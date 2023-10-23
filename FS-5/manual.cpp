#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char** argv){

  //checking file exist or not

    if(argc < 2){
        std::cerr << "Find file" << std::endl;
        exit(1);
    }
    char* filepath = argv[1];

    //open first file

  int first_file = open(filepath , O_WRONLY | O_CREAT | O_TRUNC | S_IRWXU | S_IWUSR | S_IRGRP | S_IROTH);
  if(first_file < 0){
    std:: cerr << strerror(errno) <<std::endl;
    exit(errno);
 }

  //make duplicate

   int duplicate_file = dup(first_file);
   if(duplicate_file < 0){
    std:: cerr << strerror(errno) <<std::endl;
    exit(errno);
 }
  //create second file descriptor

  int fd2 ;

// write lines

  ssize_t file1 = write(first_file ,"First line\n", 12);
  if(file1 < 0){
    std:: cerr << strerror(errno) <<std::endl;
    exit(errno);
  } 
   file1 = write(fd2 ,"Second line\n",13);
   if(file1 < 0){
    std:: cerr << strerror(errno) <<std::endl;
    exit(errno);
  } 

  //close 

  close(first_file);
  close(duplicate_file);
  return 0;
}