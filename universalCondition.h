//
// Created by Dandelonium on 6/7/2021.
//

#ifndef PART1_UNIVERSALCONDITION_H
#define PART1_UNIVERSALCONDITION_H

#include <windows.h>
#include <pthread.h>
#include "universalMutex.h"

class universalCondition {
private:
    pthread_cond_t pCondition;
    CONDITION_VARIABLE wCondition;
    // This is needed for windows
    CRITICAL_SECTION cs;
public:
    int initCond();
    int waitCond(universalMutex mutex, DWORD ms = INFINITE);
    int wakeCond();
    int wakeAllCond();
    // For windows.h we need a critical section Enter and Leave function
    void enterSection();
    void leaveSection();
};


#endif //PART1_UNIVERSALCONDITION_H
