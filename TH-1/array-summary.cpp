
#include <iostream>
#include <time.h>
#include <pthread.h>
#include <string.h>

//creating a struct to give array begin and end
struct thread_summary{
    int* arr;
    int begin;
    int end;
};

//function to go threw the elements for each thread
void* thread_sum(void* arg) {
     thread_summary* data = (thread_summary*)arg;
     int start = data -> begin;
     int finish = data -> end;
     int total_sum = 0;
    for (int i = start; i < finish; ++i) {
        total_sum += data -> arr[i];
    }

    return NULL;
}

//giving the command line arguments
int main(int argc , char** argv) {
   if(argc < 3){
    std::cerr << "no arguments" << std::endl;
    exit(0);
   }

    //N is our size of array
    int N = std::atoi(argv[1]);

    //M is threads count
    int M = std::atoi(argv[2]);
    int* arr = new int[N];
    for (int i = 0; i < N; ++i) {
        arr[i] = i + 1;
    }

    // Time measurement without threads
    clock_t start_count = clock();
    
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += arr[i];
    }

    clock_t end_count = clock();

    // count the time taken without threads
    double time_taken = ((double)(end_count - start_count)) / CLOCKS_PER_SEC;
    std::cout<<"Time without treads:" << " " << time_taken <<std::endl;

    //dynamically allocates an array of structures with size M
    pthread_t* threads = new pthread_t[M];

    //allocates an array of pointers with size M
    thread_summary** arg_sum = new thread_summary*[M];
    start_count = clock();

    // Time measurement with threads
    for (int i = 0; i < M; ++i) {
        arg_sum[i] = new thread_summary;
        arg_sum[i]-> arr = arr;
        arg_sum[i]->begin = i*(N/M);
        arg_sum[i]->end = std::min (arg_sum[i]->begin + (N/M),N);
        int created_thread = pthread_create(&threads[i], NULL, thread_sum, (void*)&arg_sum[i]);
        if(created_thread < 0){
          std::cerr << strerror(created_thread) << std::endl;
          exit(created_thread);
        }
    }

    //wait for threads finishing
    for (int i = 0; i < M; ++i) {
        pthread_join(threads[i], NULL);
    }

    end_count = clock();

    //count time with threads
    time_taken = ((double)(end_count- start_count)) / CLOCKS_PER_SEC;
    delete[] arg_sum ;
    delete[] arr;
    delete[] threads;
     std::cout<<"Time with threads:"<< " " << time_taken << std::endl;

    return 0;
}
