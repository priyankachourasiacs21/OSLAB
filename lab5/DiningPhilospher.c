#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t mutex;
sem_t S[N];

int state[N];

int LEFT(int i) { return (i + N - 1) % N; }
int RIGHT(int i) { return (i + 1) % N; }

void test(int i) {
    if (state[i] == 1 &&
        state[LEFT(i)] != 2 &&
        state[RIGHT(i)] != 2) {

        state[i] = 2;
        printf("Philosopher %d is eating\n", i);
        sem_post(&S[i]);
    }
}

void take_forks(int i) {
    sem_wait(&mutex);

    state[i] = 1;
    printf("Philosopher %d is hungry\n", i);

    test(i);

    sem_post(&mutex);
    sem_wait(&S[i]);
}

void put_forks(int i) {
    sem_wait(&mutex);

    state[i] = 0;
    printf("Philosopher %d is thinking\n", i);

    test(LEFT(i));
    test(RIGHT(i));

    sem_post(&mutex);
}

void* philosopher(void* num) {
    int i = *(int*)num;

    while(1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);

        take_forks(i);

        sleep(2);

        put_forks(i);
    }
}

int main() {
    pthread_t thread[N];
    int phil[N];

    sem_init(&mutex, 0, 1);

    for(int i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for(int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&thread[i], NULL, philosopher, &phil[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(thread[i], NULL);

    return 0;
}
