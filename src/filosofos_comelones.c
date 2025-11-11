// dining_philosophers_limited.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5
#define MAX_MEALS 3  // Cada filósofo comerá como máximo MAX_MEALS veces

sem_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    int meals_eaten = 0;

    while (meals_eaten < MAX_MEALS) {
        // Pensar
        printf("Filósofo %d está pensando.\n", id);
        sleep(rand() % 2 + 1); // 1–2 segundos

        // Entrar a sección crítica para tomar tenedores
        pthread_mutex_lock(&mutex);
        printf("Filósofo %d está hambriento (comida %d/%d).\n", id, meals_eaten + 1, MAX_MEALS);

        // Tomar ambos tenedores
        sem_wait(&forks[left]);
        printf("Filósofo %d tomó el tenedor %d (izquierdo).\n", id, left);
        sem_wait(&forks[right]);
        printf("Filósofo %d tomó el tenedor %d (derecho).\n", id, right);

        pthread_mutex_unlock(&mutex);

        // Comer
        printf("Filósofo %d está comiendo la comida %d.\n", id, meals_eaten + 1);
        sleep(rand() % 2 + 1); // 1–2 segundos
        meals_eaten++;

        // Soltar tenedores
        sem_post(&forks[left]);
        sem_post(&forks[right]);
        printf("Filósofo %d soltó ambos tenedores.\n", id);
    }

    printf("Filósofo %d ha terminado (comió %d veces).\n", id, meals_eaten);
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Inicializar tenedores (semáforos binarios)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (sem_init(&forks[i], 0, 1) != 0) {
            perror("Error al inicializar semáforo");
            exit(EXIT_FAILURE);
        }
    }

    // Crear hilos
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Error al crear hilo");
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que todos terminen
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destruir recursos
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&mutex);

    printf("\n✅ Todos los filósofos han terminado de comer.\n");
    return 0;
}
