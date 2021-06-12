//
// Created by Dandelonium on 6/5/2021.
//

#ifndef PART1_UNIVERSALSEMAPHORE_H
#define PART1_UNIVERSALSEMAPHORE_H

#include <windows.h>
#include <pthread.h>
#include <semaphore.h>
class universalSemaphore {
private:
    HANDLE wSemaphore;
    sem_t pSemaphore;
public:
    int newSemaphore(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes = NULL, LONG lInitialCount = NULL, LONG lMaximumCount = NULL, LPCSTR lpName = NULL, int pshared = 0);
    int lock();
    int unlock(LONG lReleaseCount, LPLONG lpPreviousCount);
};


#endif //PART1_UNIVERSALSEMAPHORE_H
