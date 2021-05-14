//
// Created by Dandelonium on 5/15/2021.
//
#include "universalFunctions.h"
#include "universalThread.h"

void universalThread::begin(void* (*start_address )(void *), unsigned int stack_size, void *arglist) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    wHandle = universalBeginThread(start_address, stack_size, arglist);
#elif __unix__
    universalBeginThread(start_address, stack_size, arglist, &pThread);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

void universalThread::exit(void * retval) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    ;
#elif __unix__
    void universalExitThread(void *retval);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

void universalThread::join(DWORD dwMilliseconds, int status) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    universalJoin(wHandle, dwMilliseconds);
#elif __unix__
    universalJoin(NULL, NULL, pThread, status);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}