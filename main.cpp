#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

 int SUM = 0;
 void* func(void* arg)
 {
   for(int i = 0 ;i<10000;i++){
     ++SUM;
    }
    return NULL;
 }
 int main(){
   pthread_t thread;
    int pthread_result = pthread_create(&thread, NULL , func ,NULL);
    if(pthread_result!= 0)
    {
    std::cerr<< strerror(pthread_result);
    exit(pthread_result);
    }

    for(int i = 0 ;i<10000;i++){
     ++SUM;
    
    }
    void* thread_return;
    int result = pthread_join(thread, &thread_return);//spasuma qani der chi anjatvel thready
    std::cout<< SUM << std::endl;
    return 0;
 }