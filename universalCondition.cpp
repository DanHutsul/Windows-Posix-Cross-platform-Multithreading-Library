//
// Created by Dandelonium on 6/7/2021.
//

#include "universalCondition.h"
int universalCondition::initCond() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    InitializeConditionVariable(&wCondition);
    InitializeCriticalSection(&cs);
    return 0;
#elif __unix__
    return pthread_cond_init(&pCondition, NULL);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

// For wait there is a single function in windows
// As such, POSIX implemenatation is merged into if/else statement
// The time is measured differently, as such the input is given by a DWORD in milliseconds and converted to seconds and nanoseconds for use in POSIX implementation


int universalCondition::waitCond(universalMutex mutex, DWORD ms) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    return SleepConditionVariableCS(&wCondition, &cs, ms);
#elif __unix__
    pthread_mutex_t tempMutex = mutex.getPMutex();
    if (ms == INFINITE) {
        return pthread_cond_wait(&pCondition, reinterpret_cast<pthread_mutex_t *>(tempMutex));
    } else {
        struct timespec abstime;
        abstime.tv_sec = ms / 1000;
        abstime.tv_nsec = (ms % 1000) * 1000000;
        return pthread_cond_timedwait(&pCondition, &tempMutex, &abstime);
    }
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalCondition::wakeCond() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    WakeConditionVariable(&wCondition);
    return 0;
#elif __unix__
    return pthread_cond_signal(&pCondition);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalCondition::wakeAllCond() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    WakeAllConditionVariable(&wCondition);
    return 0;
#elif __unix__
    return pthread_cond_broadcast(&pCondition);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

// Enter/Leave should be used for windows / Posix doesn't need it

void universalCondition::enterSection() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    EnterCriticalSection(&cs);
#elif __unix__
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

void universalCondition::leaveSection() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    LeaveCriticalSection(&cs);
#elif __unix__
    #else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}