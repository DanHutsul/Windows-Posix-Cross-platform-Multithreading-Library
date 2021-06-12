//
// Created by Dandelonium on 6/5/2021.
//

#ifndef PART1_UNIVERSALBARRIER_H
#define PART1_UNIVERSALBARRIER_H

#include <windows.h>
#include <pthread.h>

class universalBarrier {
private:
    pthread_barrier_t pBarrier;
    LPSYNCHRONIZATION_BARRIER wBarrier;
public:
    int initBarrier(LONG lTotalThreads, LONG lSpinCount = NULL, pthread_barrierattr_t *attr = NULL);
    int destroyBarrier();
    int wait(DWORD dwFlags = 0);
};


#endif //PART1_UNIVERSALBARRIER_H
