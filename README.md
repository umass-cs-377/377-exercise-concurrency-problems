# COMPSCI 377 LAB: Common Concurrency Problems

## Purpose

The purpose of this lab is to provide with with a hands-on understanding of common concurrency problems encountered in computer systems. Please make sure that you do all your work in the Edlab environment, otherwise, there may be inconsistent results and you will not receive points. Please read through this exercise and follow the instructions. After you do that, visit Gradescope and complete the questions associated with this exercise by the assigned due date.

The TA present in your lab will do a brief explanation of the various parts of this lab, but you are expected to answer all questions by yourself. Please raise your hand if you have any questions during the lab section. Questions and Parts have a number of points marked next to them to signify their weight in this lab’s final grade.

## Setup

Once you have logged in to Edlab, you can clone this repo using

```bash
git clone https://github.com/umass-cs-377/377-exercise-concurrency-problems
```

Then you can use `cd` to open the directory you just cloned:

```bash
cd 377-exercise-concurrency-problems
```

This repo includes a `Makefile` that allows you to locally compile and run all the sample code listed in this tutorial. You can compile them by running `make`. Feel free to modify the source files yourself, after making changes you can run `make` again to build new binaries from your modified files. You can also use `make clean` to remove all the built files, this command is usually used when something went wrong during the compilation so that you can start fresh.

## Part 1: Race Condition

A race condition is a critical concurrency issue that occurs when multiple threads access shared resources or data simultaneously and the final outcome depends on the timing and order of their execution. In other words, a race condition happens when the program's behavior is unpredictable and depends on the "race" between different threads or processes to access and modify shared data. In this `incrementer.cpp` we intentionally introduced a race condition where Thread 1 and Thread 2 run concurrently and there is no synchronization mechanism in place to control access to the counter variable. The final value of counter may not be what you expect. 

To avoid race conditions, we need to use synchronization mechanisms like locks, semaphores, and mutexes to ensure that only one thread can access the shared resource at a time. 

```c++
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

#define N 1000

int counter = 0;

void *incrementer(void *arg) {
    for (int i = 0; i < N; ++i) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, incrementer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    cout << " [ DONE ] value of counter: " << counter << endl;

    return 0;
}
```


## Part 2: Deadlocks

A deadlock is a specific type of concurrency problem that can occur when multi-threaded are unable to proceed because each is waiting for the other to release a resource, resulting in a standstill. Deadlocks are a common issue in concurrent computing, and they can lead to system or application failures. There are Four conditions for deadlock to occur. 

- Mutual exclusion: Threads claim exclusive control of resources that they require (e.g., a thread grabs a lock).
- Hold-and-wait: Threads hold resources allocated to them (e.g., locks that they have already acquired) while waiting for additional resources (e.g., locks that they wish to acquire).
- No preemption: Resources (e.g., locks) cannot be forcibly removed from threads that are holding them.
- Circular wait: There exists a circular chain of threads such that each thread holds one or more resources (e.g., locks) that are being requested by the next thread in the chain.

Deadlocks can be a complex and challenging issue to deal with. In the following `workers.cpp` we intentionally introduced a deadlock that can be solved by removing one of the above conditions.

```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <unistd.h>

using namespace std;

#define N 1000000

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg) {
    pthread_mutex_lock(&lock1);
    cout << "Thread 1: Holding lock1..." << endl;
    // Simulate some work
    sleep(1);

    pthread_mutex_lock(&lock2);
    cout << "Thread 1: Holding lock2..." << endl;

    // Do work with both locks
    sleep(1);

    pthread_mutex_lock(&lock2);
    pthread_mutex_lock(&lock1);
    return NULL;
}

void *thread2(void *arg) {
    pthread_mutex_lock(&lock2);
    cout << "Thread 2: Holding lock2..." << endl;
    
    // Simulate some work
    sleep(1);

    pthread_mutex_lock(&lock1);
    cout << "Thread 2: Holding lock1..." << endl;

    // Do work with both locks
    sleep(1);

    pthread_mutex_lock(&lock1);
    pthread_mutex_lock(&lock2);
    return NULL;
}


int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    cout << " [ DONE ] " << endl;

    return 0;
}
```


## Part 3: Order Violation
An order violation is a concurrency problem that can occur in multi-threaded programs when the expected order of execution of instructions or operations becomes unpredictable, leading to unexpected or incorrect results within a program. These issues are often associated with race conditions and can be challenging to identify and fix. Some order violations are more problematic than others. For example, if a thread accidentally deletes a resource that another thread is actively using, the program can crash. In the program below, the violation pertains to the expected behavior of the print statements and is unlikly to crash.

```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <unistd.h>

using namespace std;

pthread_mutex_t lock_t = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int current_thread = 0;

void *Thread1(void *arg) {
    sleep(1);

    int i = 0;
    while (i++ < 10) {
        cout << "(";
    }
        

    current_thread = 1;

    return NULL;
}

void *Thread2(void *arg) {
    sleep(1);

    
    int i = 0;
    while (i++ < 10) {
        cout << ")";
    }
    

    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t2, NULL, Thread2, NULL);
    pthread_create(&t1, NULL, Thread1, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    cout << endl; 

    pthread_mutex_destroy(&lock_t);
    pthread_cond_destroy(&condition);

    return 0;
}
```



