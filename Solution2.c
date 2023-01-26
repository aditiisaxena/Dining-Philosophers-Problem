#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

#define PHILOSOPHERS 5  

#define LEFT position   
#define RIGHT (position + 1) % PHILOSOPHERS 

pthread_t eat_think_repeat[PHILOSOPHERS];
sem_t forks[PHILOSOPHERS];

int positioning[PHILOSOPHERS];              

void *philosopher(void *arg) {

    int position = *((int *)arg);

    while (true) {
        
        // thinking
        printf("Philosopher %i is thinking\n", position);
        sleep(1);

        if (position % 2 == 0){
            sem_wait(&forks[LEFT]);
            printf("Philosopher %i picked left fork\n", position);
            sem_wait(&forks[RIGHT]);
            printf("Philosopher %i picked right fork\n", position);
        } else {
            sem_wait(&forks[RIGHT]);
            printf("Philosopher %i picked right fork\n", position);
            sem_wait(&forks[LEFT]);
            printf("Philosopher %i picked left fork\n", position);
        }

        // eating
        printf("Philosopher %i is eating\n", position);
        sleep(1);

        sem_post(&forks[LEFT]);
        printf("Philosopher %i placed left fork back\n", position);
        sem_post(&forks[RIGHT]);
        printf("Philosopher %i placed right fork back\n", position);
    }
}

int main(int argc, char *argv[]) {

    for (int i = 0; i < PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        positioning[i] = i;
        pthread_create(&eat_think_repeat[i], NULL, philosopher, &positioning[i]);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_join(eat_think_repeat[i], NULL);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}