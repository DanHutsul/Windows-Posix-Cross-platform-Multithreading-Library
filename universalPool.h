//
// Created by Dandelonium on 6/6/2021.
//

#ifndef PART1_UNIVERSALPOOL_H
#define PART1_UNIVERSALPOOL_H

#include <iostream>
#include <queue>
#include <unistd.h>
#include "universalThread.h"

class job {
private:
    int jobID;
public:
    job(int id) : jobID(id) {}
    virtual ~job(){}

    void virtual working()
    {
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
        //
#elif __unix__
        pthread_mutex_lock(&jobLock);
            finished_jobs++;
            pthread_mutex_unlock(&jobLock);
            std::cout << "job:" << jobID << " starts\n";
            sleep(1);
        #else
            throw std::invalid_argument("Unsupported Operating System");
#endif

    }
    static int finished_jobs;
    static pthread_mutex_t jobLock;
};

class universalPool {
private:
    std::queue<job*> jobQueue;
    int numOfThreads;

public:
    static pthread_mutex_t jobQueue_lock;
    static HANDLE wMutex;
    static CONDITION_VARIABLE wCondition;
    static pthread_cond_t jobQueue_cond;
    universalPool(){ universalPool(2); }
    universalPool(int num) : numOfThreads(num) {}
    virtual ~universalPool() { while(!jobQueue.empty()) jobQueue.pop(); };
    void initThreads(universalThread *);
    void assignJob(job *_job_);
    bool loadJob(job *&_job_);
    static void *threadExecute(void *);
};



#endif //PART1_UNIVERSALPOOL_H
