//
// Created by Dandelonium on 6/10/2021.
//

#ifndef PART1_UNIVERSALASYNC_H
#define PART1_UNIVERSALASYNC_H

#include "universalFuture.h"
#include "universalThread.h"
#include <pthread.h>
#include <windows.h>
#include <iostream>
class universalAsync {
public:
    template<typename T>
    static universalFuture<T> begin(void* (*start_address )(void *), unsigned stack_size = 0, void *arglist = NULL) {
        universalThread thread;
        universalFuture<T> future;
        thread.begin(start_address, stack_size, arglist);
        future.set(start_address);
        return future;
    }
};



#endif //PART1_UNIVERSALASYNC_H
