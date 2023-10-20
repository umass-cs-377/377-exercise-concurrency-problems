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
