//
// Created by Dandelonium on 5/15/2021.
//

#ifndef PART1_UNIVERSALMUTEX_H
#define PART1_UNIVERSALMUTEX_H


#include <windows.h>
#include <pthread.h>

class universalMutex {
private:
    pthread_mutex_t pMutex;
    HANDLE wMutex;
public:
    int initMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL,
                  BOOL bInitialOwner = NULL,
                  LPCSTR lpName = NULL,
                  pthread_mutexattr_t *attr = NULL);
    int lock(DWORD dwMilliseconds = INFINITE);
    int unlock();
    int destroy();
    pthread_mutex_t getPMutex();
};


#endif //PART1_UNIVERSALMUTEX_H
