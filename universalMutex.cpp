#include "universalMutex.h"

int universalMutex::initMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes,
                              BOOL bInitialOwner,
                              LPCSTR lpName,
                              pthread_mutexattr_t *attr) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    wMutex = CreateMutex(lpMutexAttributes, bInitialOwner, lpName);
#elif __unix__
    return pthread_mutex_init(&pMutex, attr);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalMutex::lock(DWORD dwMilliseconds) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    return WaitForSingleObject(wMutex, dwMilliseconds);
#elif __unix__
    return pthread_mutex_lock(&pMutex);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalMutex::unlock() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    ReleaseMutex(wMutex);
#elif __unix__
    return pthread_mutex_unlock(&pMutex);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

int universalMutex::destroy() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    //
#elif __unix__
    return pthread_mutex_destroy(&pMutex);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

pthread_mutex_t universalMutex::getPMutex() {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    //
#elif __unix__
    return pMutex;
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}