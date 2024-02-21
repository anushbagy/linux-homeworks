#include "shared_array.h"


SharedArray::SharedArray(std::string name_of_arr, int size) : name_of_arr(name_of_arr), size(size) {
    int name_int = std::stoi(name_of_arr);
    name_of_arr = std::to_string(name_int + size);

    fd = shm_open(name_of_arr.c_str(), O_CREAT | O_RDWR, 0644);

    if (fd < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    if (ftruncate(fd, size) < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int length = size * sizeof(char);
    ptr = static_cast<char*>(mmap(nullptr, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    if (ptr == MAP_FAILED) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
}

char& SharedArray::operator[](int index) {
    return ptr[index];
}

SharedArray::~SharedArray() {
    munmap(ptr, size * sizeof(char));
    close(fd);
}
