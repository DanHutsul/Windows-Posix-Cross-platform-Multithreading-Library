//
// Created by Dandelonium on 6/5/2021.
//

#include "universalBarrier.h"
int universalBarrier::initBarrier(LONG lTotalThreads, LONG lSpinCount, pthread_barrierattr_t *attr){ //lTotalThreads contains number/max number of threads. Used in both methods
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    return InitializeSynchronizationBarrier(reinterpret_cast<LPSYNCHRONIZATION_BARRIER>(&wBarrier), lTotalThreads, lSpinCount);
#elif __unix__
    return pthread_barrier_init(&pBarrier, attr, lTotalThreads);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalBarrier::destroyBarrier() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    return DeleteSynchronizationBarrier(reinterpret_cast<LPSYNCHRONIZATION_BARRIER>(&wBarrier));
#elif __unix__
    return pthread_barrier_destroy(&pBarrier);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalBarrier::wait(DWORD dwFlags) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    return EnterSynchronizationBarrier(reinterpret_cast<LPSYNCHRONIZATION_BARRIER>(&wBarrier), dwFlags);
#elif __unix__
    return pthread_barrier_wait(&pBarrier);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}