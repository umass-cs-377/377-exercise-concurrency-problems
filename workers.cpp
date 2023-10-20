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