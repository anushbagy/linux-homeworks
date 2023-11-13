#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <chrono>
#include <string.h>

 void do_command(char** argv){

// start time of the program
auto start = std::chrono::high_resolution_clock::now();
  
//making new process
  pid_t pidForprocess = fork();

//check if it creates correct
  if(pidForprocess < 0){
   std::cerr << strerror(errno) << std::endl;
   exit(errno);
  }
  if(pidForprocess == 0){

    //execute process
 int second_process = execvp(argv[0],argv);

 //checking
 if(second_process == -1){
   std::cerr << strerror(errno) << std::endl;
   exit(errno);
  }
  }

   //waiting for process end
   int pidStatus;
   int waitingPid = waitpid(pidForprocess,&pidStatus,0); 
   if(waitingPid == -1){
   std::cerr << strerror(errno) << std::endl;
   exit(errno);
   }
    
    //give end for time 
    auto end = std::chrono::high_resolution_clock::now();
    
    //make duration
     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout<<duration<<std::endl;
    if(WEXITSTATUS(pidStatus)){
    std::cout<< WEXITSTATUS(pidStatus)<<std::endl;

 }
 }
int main(int argc, char* argv[]){
 
 //check if argument is given correct
if(argc < 2){
   std::cerr << "no path" << std::endl;
   exit(1);
}

//call function
do_command(argv);

return 0;
 
}
