#ifndef SHARED_ARRAY
#define SHARED_ARRAY

#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
class SharedArray {
private:
    char* ptr;
    std::string name_of_arr;
    int size;
    int fd; // Add file descriptor as a member variable

public:
    SharedArray(std::string name_of_arr, int size);
    char& operator[](int index);
    ~SharedArray();
};

#endif
