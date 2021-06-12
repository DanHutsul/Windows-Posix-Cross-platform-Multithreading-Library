//
// Created by Dandelonium on 6/6/2021.
//

#include <iostream>
#include "universalPool.h"

int job::finished_jobs = 0;

pthread_mutex_t job::jobLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t universalPool::jobQueue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t universalPool::jobQueue_cond = PTHREAD_COND_INITIALIZER;

void universalPool::initThreads(universalThread *threads)
{
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    //
#elif __unix__
    for(int i = 0; i < numOfThreads; i++) {
        pthread_create(&threads[i].pThread, NULL, &universalPool::threadExecute, (void *)this);
        std::cout << "Thread:" << i << " is initialized!\n";
    }
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif
}

void universalPool::assignJob(job* _job_)
{
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    //
#elif __unix__
    pthread_mutex_lock(&jobQueue_lock);
    jobQueue.push(_job_);
    pthread_mutex_unlock(&jobQueue_lock);
    pthread_cond_signal(&jobQueue_cond);
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif

}

bool universalPool::loadJob(job*& _job_)
{
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    //
#elif __unix__
    pthread_mutex_lock(&jobQueue_lock);
    while(jobQueue.empty())
        pthread_cond_wait(&jobQueue_cond, &jobQueue_lock);
    _job_ = jobQueue.front();
    jobQueue.pop();
    pthread_mutex_unlock(&jobQueue_lock);
    return true;
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif

}

void *universalPool::threadExecute(void *param)
{
#ifdef _WIN32 //This includes both 32bit and 64bit Windows
    //
#elif __unix__
    universalPool *p = (universalPool *)param;
    job *oneJob = NULL;
    while(p->loadJob(oneJob)) {
        if(oneJob)
            oneJob->working();
        delete oneJob;
        oneJob = NULL;
    }
#else
    throw std::invalid_argument("Unsupported Operating System");
#endif

}