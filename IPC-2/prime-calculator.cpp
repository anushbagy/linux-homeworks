#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

 //finding the prime number
int Find_Prime(int n) {
  int temp = 0;  
  int num = 1; 

  while (temp < n) {
    ++num;

    bool isPrime = true;

    for (int i = 2; i <= num/ 2; ++i) {
      if (num % i == 0) {
        isPrime = false; 
        break;
      }
    }

    if (isPrime) {
      ++temp; 
    }
  }
  return num; 
}
int main(){
    //creating two pipes for child and parent
    int first_pipe[2];
    int second_pipe[2];
    int first_result = pipe(first_pipe);
    if(first_result < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
     int second_result = pipe(second_pipe);
    if(second_result < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    //making child process 
    pid_t pid = fork();
    
    if(pid < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
     //we are in parent process
    if(pid > 0){
        close(first_pipe[0]);
        close(second_pipe[1]);
        

        std::string outcome;
        std::cout << "" << std::endl;

       while(true){
       
        std::cout << "Please enter the number :"<< " ";
        std::cin >> outcome;

        if(outcome == "EXIT"){
            break;
        }
        int m = std::stoi(outcome);

        std::cout << " Sending " << " "<< m << "to the child process..." << std::endl;

        //write result in parent pipe
        write(first_pipe[1], &m, sizeof(int));
        
        int write_result = write(first_pipe[1], &m, sizeof(int));
        if(write_result < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
        std::cout << "Waiting for response from the child process..." << std::endl;
        //read from child process 
        int prime_res;
        int read_exp = read(second_pipe[0],&prime_res,sizeof(int));
         if(read_exp < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
        //getting the calculations from child 
        std::cout << "Received calcualtion result of prime " << " " << m <<" = " << prime_res << std::endl; 
    }   
    }

    if(pid == 0){
        close(first_pipe[1]);
        close(second_pipe[0]);
    
        int m;
        // reading m from parent 
        int result1 = read(first_pipe[0], &m, sizeof(int));
        if(result1 < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
        std::cout << "Calculating " <<  m <<"th"<< " "<< "prime number"<<std::endl;

        //calculating prime number
        int m_prime = Find_Prime(m);
        std::cout << "Sending calculation result of prime" << " " <<  m << std::endl;

        //writing result 
        int write_result2 = write(second_pipe[1], &m_prime, sizeof(int));
        if(write_result2 < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

    }

    return 0;

}