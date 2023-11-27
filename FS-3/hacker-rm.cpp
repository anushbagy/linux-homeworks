#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#define BUFFER_SIZE 25

  int main(int argc , char** argv){
    if(argc < 2){

        //check the number of command-line arguments

        std::cerr << "There is no path "<<std::endl;
        exit(1);
    }
    char* first = argv[1];

    // open with flags write and read only

    int fd = open(first,O_WRONLY );

   //check if it calls correct

    if(fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // make buffer with buffer_size

    char buff[BUFFER_SIZE];

    //fill buffer with '\0'

    for(int i = 0;i < BUFFER_SIZE ;++i){
        buff[i]='\0';
    }
    
    //give information about file

    struct stat  _buff;
    ssize_t info = stat (first,&_buff);
    ssize_t __size = _buff.st_size;
   
   //fill file with '\0'

    int count = 0;
    while(count < __size){
       ssize_t  write_ = write (fd,buff,BUFFER_SIZE);
         if(write_ < 0){
            std::cerr << strerror(errno) << std::endl;
        exit(errno);
         }
         count += write_;
    }
   
   //removing

   ssize_t deleting = unlink(first);
   if(deleting < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
     }
    
    return 0;
 }
//  #include <iostream>
// #include <sys/types.h>
// #include <unistd.h>
// #include <cerrno>
// #include <sys/wait.h>
// #include <bits/stdc++.h> 
// #include <ctime>

// using namespace std; 

//  void do_command(char** argv){

// // start time of the program
// struct tms start, end; 
// clock_t beginTime,endTime;
// beginTime = times(&start);
//   // std::time_t beginTime = std::time(nullptr);
//   // std::time_t endTime;
  
// //making new process
//   pid_t pidForprocess = fork();

// //check if it creates correct
//   if(pidForprocess == -1){
//    std::cerr << strerror(errno) << std::endl;
//    exit(errno);
//   }
//  int second_process = execv(argv[0],argv);
//  if(second_process == -1){
//    std::cerr << strerror(errno) << std::endl;
//    exit(errno);
//   }
//    int pidStatus = -1;

//    pid_t waitingPid = waitpid(pidForprocess,&pidStatus,0); 
//    if(waitingPid == -1){
//    std::cerr << strerror(errno) << std::endl;
//    exit(errno);
//    }

//    endTime = times(&end);
//      if (WIFEXITED(pidStatus)) {
//      double total_time = difftime(endTime,beginTime)/_SC_;
//     std::cout<< "Done with "<< WEXITSTATUS(pidStatus) <<" "<<"time"<< total_time <<std::endl;
//   }

//  }

//  }
// int main(int argc, char* argv[]){

// if(argc < 2){
//    std::cerr << "no path" << std::endl;
//    exit(1);
// }
// do_command(argv);

// return 0;
 
// }