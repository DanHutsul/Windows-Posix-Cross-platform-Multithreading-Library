#include <windows.h>
#include <stdio.h>
#include "universalMutex.h"
#include "universalFunctions.h"
#include "universalThread.h"
#include <unistd.h>

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
    printf("\n Job %d has started and is counting to 10\n", counter);

    for (int t = 1; t <= 10; t++) {
        printf("Job %d counts %d\n", counter, t);
        sleep(1);
    }

    printf("\n Job %d has finished\n", counter);

    lock.unlock();

    return NULL;
}

int main(int argc, char* argv[])
{
    universalThread myThread1, myThread2;

    int i = 0;
    int error;
    lock.initMutex();

    myThread1.begin(&trythis);
    myThread2.begin(&trythis);
    /*myhandle = universalBeginThread(&trythis, 0, NULL, &(tid[0]));
    myhandle2 = universalBeginThread(&trythis, 0, NULL, &(tid[1]));*/

    myThread1.join();
    myThread2.join();
    /*universalJoin(myhandle, INFINITE, tid[0], NULL);
    universalJoin(myhandle2, INFINITE, tid[1], NULL);*/
    lock.destroy();
    printf("DONE!");
    universalExitThread(NULL);
    return 0;
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