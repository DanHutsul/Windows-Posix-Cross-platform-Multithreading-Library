#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

class universalMutex {
public:

    universalMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName) {
#ifdef _WIN32
        innerMutex = CreateMutex(lpMutexAttributes, bInitialOwner, lpName);
#else
        throw std::invalid_argument("Unsupported Operating System");
#endif
    }

private:
    HANDLE innerMutex;
};

unsigned long long int universalBeginThread(void *security,
                                     unsigned stack_size,
                                     unsigned ( *start_address )( void * ),
                                     void *arglist,
                                     unsigned initflag,
                                     unsigned *thrdaddr) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    return _beginthreadex(security, stack_size, start_address, arglist, initflag, thrdaddr);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}
DWORD universalWaitForSingleObject(HANDLE hHandle, DWORD  dwMilliseconds) {
#ifdef _WIN32
    return WaitForSingleObject(hHandle, dwMilliseconds);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}


HANDLE myCreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName) {
#ifdef _WIN32
    return new universalMutex(lpMutexAttributes, bInitialOwner, lpName);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

BOOL universalCloseHandle(HANDLE hObject) {
#ifdef _WIN32
    return CloseHandle(hObject);
#elif _POSIX_VERSION
    //The POSIX does not require explicit closure
    pass;
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

HANDLE universalSemaphore(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName) {
#ifdef _WIN32
    return CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

BOOL universalReleaseSemaphore(HANDLE hSemaphore, LONG lReleaseCount, LPLONG lpPreviousCount) {
#ifdef _WIN32
    return ReleaseSemaphore(hSemaphore, lReleaseCount, lpPreviousCount);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

//For testing
volatile int counter = 0;
HANDLE mutex;

int isPrime(int n)
{
    for(int i = 2; i < (int)(sqrt((float)n) + 1.0) ; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
unsigned int __stdcall mythread(void*)
{
    char* s;
    while (counter < 25) {
        WaitForSingleObject(mutex, INFINITE);
        int number = counter++;
        ReleaseMutex(mutex);
        s = "No";
        if(isPrime(number)) s = "Yes";
        printf("Thread %d value = %d is prime = %s\n",
               GetCurrentThreadId(), number, s);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    HANDLE myhandleA, myhandleB;

    mutex = myCreateMutex(0, 0, 0);

    myhandleA = (HANDLE)universalBeginThread(0, 0, &mythread, (void*)0, 0, 0);
    myhandleB = (HANDLE)universalBeginThread(0, 0, &mythread, (void*)1, 0, 0);

    universalWaitForSingleObject(myhandleA, INFINITE);
    universalWaitForSingleObject(myhandleB, INFINITE);

    universalCloseHandle(myhandleA);
    universalCloseHandle(myhandleB);

    universalCloseHandle(mutex);

    return 0;
}