//
// Created by Dandelonium on 5/15/2021.
//

#ifndef PART1_UNIVERSALTHREAD_H
#define PART1_UNIVERSALTHREAD_H

#include <windows.h>
#include <pthread.h>

class universalThread {
private:
    pthread_t pThread;
    HANDLE wHandle;
public:
    void begin(void* (*start_address )(void *), unsigned stack_size = 0, void *arglist = NULL);
    void exit(void *retval);
    void join(DWORD dwMilliseconds = INFINITE, int status = NULL);
};


#endif //PART1_UNIVERSALTHREAD_H
