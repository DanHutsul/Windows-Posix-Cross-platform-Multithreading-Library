//
// Created by Dandelonium on 5/15/2021.
//

#ifndef PART1_UNIVERSALTHREAD_H
#define PART1_UNIVERSALTHREAD_H

#include <assert.h>
#include <windows.h>
#include <pthread.h>

class universalThread {
private:
    HANDLE wHandle;


protected:


    static void* threadProc(void* param) {
        universalThread* thread = reinterpret_cast<universalThread*>(param);
        return NULL;
    }

public:
    enum EState {
        EState_None,
        EState_Started,
        EState_Joined
    };
    EState state;
    universalThread();
    virtual ~universalThread() {
        assert(state != EState_Started);
    };
    void begin(void* (*start_address )(void *), unsigned stack_size = 0, void *arglist = NULL);
    void exit(void *retval);
    void join(DWORD dwMilliseconds = INFINITE, int status = NULL);

    pthread_t pThread;
};


#endif //PART1_UNIVERSALTHREAD_H
