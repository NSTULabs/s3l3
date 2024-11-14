#ifndef UTILS_HPP
#define UTILS_HPP

#include <ctime>
#include <cstdlib>

u_int32_t generateRandomNumber(int min, int max) {
    srand(static_cast<u_int32_t>(time(0)));
    return min + rand() % (max - min + 1);
}

#endif