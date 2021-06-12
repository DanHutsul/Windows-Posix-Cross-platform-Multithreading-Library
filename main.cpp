#include <windows.h>
#include <stdio.h>
#include "universalMutex.h"
#include "universalFunctions.h"
#include "universalThread.h"
#include "universalBarrier.h"
#include "universalCondition.h"
#include "universalSemaphore.h"
#include "universalPool.h"
#include "universalAsync.h"
#include <unistd.h>
#include <iostream>
#include <vector>

//unsigned long long int universalBeginThread(void (*pFunction)(void *), int i, int i1);

// Starting with this
// So far the problem is that both function require different inputs
// As such there is a mess of them in here
// This function is required for creating a thread

// win returns handle
// pthread returns

// After consideration _beginthreadex is better then


// Exiting threads
// Windows.h threads are best left unexited
//


//WaitForSingleObject and pthread_join perform the same function
/*
void *worker_thread_w(void *arg)
{
    printf("worker_thread_w function\n");
    return (void *)(arg);
}

void *worker_thread_w2(void *arg)
{
    printf("worker_thread_w2 function\n");
    return (void *)(arg);
}

void *t_function(void *data)
{
    int num = *((int *)data);
    printf("num %d\n", num);
    return (void *)(num*num);
}


int counter;
universalMutex lock;

void* trythis(void* arg)
{
    lock.lock();

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d has started and is counting to 5\n", counter);

    for (int t = 1; t <= 5; t++) {
        printf("Job %d counts %d\n", counter, t);
        sleep(1);
    }

    printf("\n Job %d has finished\n", counter);

    lock.unlock();

    return NULL;
}

void basic_test() {
    universalThread myThread1, myThread2;

    int i = 0;
    int error;
    lock.initMutex();

    myThread1.begin(&trythis);
    myThread2.begin(&trythis);

    myThread1.join();
    myThread2.join();
    lock.destroy();
    printf("DONE!");
    universalExitThread(NULL);
}


universalBarrier b;
int barrierResult = b.initBarrier(2, -1);
void* barrier_test_function(void* p)
{
    int id = *((int*)(&p));
    printf("before  barrier %d\n", id);
    b.wait(0);
    printf("after  barrier %d\n", id);
}

void barrier_test() {

    int num_of_Thread = 2;
    universalThread myThread0, myThread1, myThread2, myThread3;


    myThread0.begin(barrier_test_function, 0, reinterpret_cast<void *>(0));
    myThread1.begin(barrier_test_function, 0, reinterpret_cast<void *>(1));
    myThread2.begin(barrier_test_function, 0, reinterpret_cast<void *>(2));
    myThread3.begin(barrier_test_function, 0, reinterpret_cast<void *>(3));

    myThread0.join();
    myThread1.join();
    myThread2.join();
    myThread3.join();

    b.destroyBarrier();
}
universalCondition cond;
universalMutex mutex;

int footprint = 0;

void *condition_test_function(void *arg) {
    time_t T;

    mutex.lock();
    time(&T);
    printf("starting wait at %s", ctime(&T));
    footprint++;

    cond.waitCond(mutex);
    time(&T);
    printf("wait over at %s", ctime(&T));
}

void condition_test() {
    universalThread thid;
    time_t T;
    struct timespec t;

    mutex.initMutex(NULL);

    cond.initCond();

    thid.begin(condition_test_function, NULL, NULL);

    puts("IPT is about ready to release the thread");
    sleep(2);

    cond.wakeCond();

    thid.join();
}
*/
// Thread Pool

#define THREADS_NUM 5
#define JOBS_NUM 20

void pool_test() {
    universalPool *myPool = new universalPool(THREADS_NUM);
    universalThread threads[THREADS_NUM];
    myPool->initThreads(threads);
    for(int i = 0; i < JOBS_NUM; i++)
    {
        job *newJob = new job(i);
        myPool->assignJob(newJob);
    }
    while(job::finished_jobs < JOBS_NUM);
}

// Future and Async
int square(void* arg){
    std::cout <<  "square" << std::endl;
    int num = 20;
    return num;
}

int main(int argc, char* argv[])
{
    //basic_test();
    //barrier_test();
    //condition_test();
    //semaphore_test();
    //universalAsync j;
    //auto a = universalAsync::begin<void* (*)(void*)>(reinterpret_cast<void *(*)(void *)>(square), 0, NULL);
    //sleep(10);
    //std::cout << "square currently running\n" << a.get(); //do something while square is running
    //std::cout << "result is " << f.get() << '\n'; //getting the result from square
}







/*HANDLE myhandle, myhandle2;
    pthread_t tid[2];
    int ret;
    int ret2;*/

//myhandle = universalBeginThread(worker_thread_w, 0, NULL, &my_thread);//(HANDLE)_beginthread(&mythreadC, 0, 0); // Windows
//myhandle2 = universalBeginThread(worker_thread_w2, 0, NULL, &my_thread2);

/*printf("Creating thread1\n");
//pthread_create(&my_thread, NULL, worker_thread_w, NULL);
myhandle = universalBeginThread(worker_thread_w, 0, NULL, &my_thread);
printf("Creating thread2\n");
//pthread_create(&my_thread2, NULL, worker_thread_w2, NULL);
myhandle2 = universalBeginThread(worker_thread_w2, 0, NULL, &my_thread2);

WaitForSingleObject(myhandle, INFINITE);// Tested, works fine
//universalJoin(myhandle2, INFINITE, my_thread, NULL);
//WaitForSingleObject(myhandle2, INFINITE);// Tested, works fine
universalJoin(myhandle2, INFINITE, my_thread2, NULL);

//pthread_join(my_thread, NULL);
//pthread_join(my_thread2, NULL);
std::cout << "done!\n";
universalExitThread(NULL);//WaitForSingleObject((HANDLE)myhandleC, INFINITE); // Need this*/