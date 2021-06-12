//
// Created by Dandelonium on 5/15/2021.
//
#include "universalFunctions.h"
#include "universalThread.h"

universalThread::universalThread() {
    state = EState_None;
}

void universalThread::begin(void* (*start_address )(void *), unsigned int stack_size, void *arglist) {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    assert(state == EState_None);
    wHandle = universalBeginThread(start_address, stack_size, arglist);
    state = EState_Started;
#elif __unix__
    assert(state == EState_None);
    universalBeginThread(start_address, stack_size, arglist, &pThread);
    state = EState_Started;
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
    assert(state == EState_Started);
    universalJoin(wHandle, dwMilliseconds);
    state = EState_Joined;
#elif __unix__
    assert(state == EState_Started);
    universalJoin(NULL, NULL, pThread, status);
    state = EState_Joined;
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

