#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define TIMEOUT 5

#define PHILOSOPHERS 5  

#define LEFT position                   
#define RIGHT (position + 1) % PHILOSOPHERS

pthread_t eat_think_repeat[PHILOSOPHERS];

int positioning[PHILOSOPHERS];              
int forks[PHILOSOPHERS];                    

void *philosopher(void *arg) {

    int position = *((int *)arg);

    while (true) {
        
        // thinking
        printf("Philosopher %i is thinking\n", position);
        sleep(1);

        time_t start = time(NULL);
        while (forks[LEFT] == 0 && time(NULL) - start < TIMEOUT){
            sleep(1);
        }
        if (forks[LEFT] == 0) {
            printf("Philosopher %i timed out waiting for left fork\n", position);
            continue;
        }
        forks[LEFT] = 0;
        printf("Philosopher %i picked left fork\n", position);
        start = time(NULL);
        while (forks[RIGHT] == 0 && time(NULL) - start < TIMEOUT){
            sleep(1);
        }
        if (forks[RIGHT] == 0) {
            printf("Philosopher %i timed out waiting for right fork\n", position);
            forks[LEFT] = 1;
            continue;
        }
        forks[RIGHT] = 0;
        printf("Philosopher %i picked right fork\n", position);

        // eating
        printf("Philosopher %i is eating\n", position);
        sleep(1);

        forks[LEFT] = 1;
        printf("Philosopher %i placed left fork back\n", position);
        forks[RIGHT] = 1;
        printf("Philosopher %i placed right fork back\n", position);
    }
}

int main(int argc, char *argv[]) {

    for (int i = 0; i < PHILOSOPHERS; i++) {
        forks[i] = 1;
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        positioning[i] = i;
        pthread_create(&eat_think_repeat[i], NULL, philosopher, &positioning[i]);
    }

    for (int i = 0; i < PHILOSOPHERS; i++) {
        pthread_join(eat_think_repeat[i], NULL);
    }

    return 0;
}
