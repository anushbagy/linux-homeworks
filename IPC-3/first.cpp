
#include "shared_array.h"

int main() {
    const char* name_of_sem = "/sem_my";
    SharedArray arrof("fndf", 100); 
    sem_t* semaphore = sem_open(name_of_sem, O_CREAT | O_EXCL, 0666, 1);  
    if (semaphore == SEM_FAILED) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    while (true) {
        sem_wait(semaphore);

        for (int i = 0; i < 100; i++) {
            arrof[i] += 2;
        }

        sem_post(semaphore);

        sleep(3);
    }

 
    sem_close(semaphore);

    return 0;
}
