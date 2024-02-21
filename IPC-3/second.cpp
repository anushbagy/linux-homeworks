
#include "SharedArray.h"

int main() {
    const char* name_of_sem = "/sem_my";

    SharedArray shmArr("my arr", 100); 
   
    sem_t* semaphore = sem_open(name_of_sem, O_CREAT | O_EXCL, 0664, 1);  
    if (semaphore == SEM_FAILED) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    while (true) {
        sem_wait(semaphore);

        for (int i = 0; i < 100; i++) {
            std::cout << shmArr[i];
        }
        sem_post(semaphore);
    }
    sem_close(semaphore);

    return 0;
}