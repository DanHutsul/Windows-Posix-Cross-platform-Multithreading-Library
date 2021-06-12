//
// Created by Dandelonium on 6/5/2021.
//

#include <iostream>
#include "universalSemaphore.h"
int universalSemaphore::newSemaphore(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName, int pshared) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    wSemaphore = CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
    if (wSemaphore == NULL) {
        return 1;
    };
    return 0;
#elif __unix__
    return sem_init(&pSemaphore, pshared, lInitialCount);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalSemaphore::lock() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    DWORD dwWaitResult = WaitForSingleObject(wSemaphore, 0L);
    BOOL bContinue=TRUE;
    while(bContinue) {
        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                bContinue=FALSE;
                break;
            case WAIT_TIMEOUT:
                break;
        }
    }

    return dwWaitResult;
#elif __unix__
    return sem_wait(&pSemaphore);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalSemaphore::unlock(LONG lReleaseCount, LPLONG lpPreviousCount) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    int a = !ReleaseSemaphore(wSemaphore, lReleaseCount, lpPreviousCount);
    return a;
#elif __unix__
    return sem_post(&pSemaphore);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}