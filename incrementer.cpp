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