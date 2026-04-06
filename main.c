#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    int id;
    pthread_barrier_t *barreira_inicio;
} ArgumentosThread;


static int id_vencedor = -1;

void *executar_corrida(void *arg) {
    ArgumentosThread *args = (ArgumentosThread *)arg;

    // Sincroniza início
    pthread_barrier_wait(args->barreira_inicio);

    for (int i = 0; i < 100; i++) {
        printf("Thread %d -> %d\n", args->id, i);
        fflush(stdout);
    }

    
    if (id_vencedor == -1) {
        id_vencedor = args->id;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    int quantidade_threads;

    srand(time(NULL));

    if (argc == 2) {
        quantidade_threads = atoi(argv[1]);
    } else {
        quantidade_threads = (rand() % 10) + 1;
        printf("Quantidade de threads (aleatoria): %d\n", quantidade_threads);
    }

    if (quantidade_threads <= 0) {
        fprintf(stderr, "Erro: a quantidade de threads deve ser maior que 0.\n");
        return 1;
    }

    pthread_t *threads = malloc(sizeof(pthread_t) * quantidade_threads);
    ArgumentosThread *args = malloc(sizeof(ArgumentosThread) * quantidade_threads);

    if (threads == NULL || args == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        free(threads);
        free(args);
        return 1;
    }

    pthread_barrier_t barreira_inicio;
    if (pthread_barrier_init(&barreira_inicio, NULL, quantidade_threads) != 0) {
        fprintf(stderr, "Erro ao criar barreira.\n");
        free(threads);
        free(args);
        return 1;
    }

    for (int i = 0; i < quantidade_threads; i++) {
        args[i].id = i + 1;
        args[i].barreira_inicio = &barreira_inicio;

        if (pthread_create(&threads[i], NULL, executar_corrida, &args[i]) != 0) {
            fprintf(stderr, "Erro ao criar thread %d.\n", i + 1);
            pthread_barrier_destroy(&barreira_inicio);
            free(threads);
            free(args);
            return 1;
        }
    }

    for (int i = 0; i < quantidade_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nRESULTADO\n");
    printf("A  thread que venceu foi: Thread %d\n", id_vencedor);

    pthread_barrier_destroy(&barreira_inicio);
    free(threads);
    free(args);

    return 0;
}