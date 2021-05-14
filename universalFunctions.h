//
// Created by Dandelonium on 5/15/2021.
//

#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <pthread.h>
#include "universalMutex.h"
#include <unistd.h>


#ifndef PART1_UNIVERSALFUNCTIONS_H
#define PART1_UNIVERSALFUNCTIONS_H

#endif //PART1_UNIVERSALFUNCTIONS_H
HANDLE universalBeginThread(void* (*start_address )(void *), unsigned stack_size, void *arglist, pthread_t* threadId = NULL);
void universalExitThread(void *retval);
void universalJoin(HANDLE hHandle = NULL, DWORD dwMilliseconds = NULL, pthread_t thread = NULL, int status = NULL);