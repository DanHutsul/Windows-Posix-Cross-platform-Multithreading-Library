//
// Created by Dandelonium on 5/15/2021.
//
#include "universalFunctions.h"

HANDLE universalBeginThread(void* (*start_address )(void *), unsigned stack_size, void *arglist, pthread_t* threadId) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    return (HANDLE)_beginthreadex(0, stack_size, (_beginthreadex_proc_type) start_address, arglist, 0, 0);
#elif __unix__
    // The pthread_create has 2 return states: 0 if correct, int error code if error
    //pthread_create(&my_thread, NULL, worker_thread_w, NULL);
    return (HANDLE) pthread_create(threadId, NULL, start_address, arglist);//pthread_create(threadId, NULL, start_address, arglist);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

void universalExitThread(void *retval) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    ;
#elif __unix__
    pthread_exit(retval);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

void universalJoin(HANDLE hHandle, DWORD dwMilliseconds, pthread_t thread, int status) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    WaitForSingleObject(hHandle, dwMilliseconds);
#elif __unix__
    pthread_join(thread, (void **) status);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}
