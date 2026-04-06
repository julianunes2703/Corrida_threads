#include <stdio.h>   
#include <stdlib.h> 
#include <pthread.h> // Biblioteca para trabalhar com threads (POSIX)
#include <unistd.h> 
#include <time.h>   

// Estrutura que será passada como argumento para cada thread
typedef struct {
    int id; // Identificador da thread
    pthread_barrier_t *barreira_inicio; // Ponteiro para a barreira de sincronização
} ArgumentosThread;

// Mutex para garantir exclusão mútua ao definir o vencedor
static pthread_mutex_t mutex_vencedor = PTHREAD_MUTEX_INITIALIZER;

// Variável global que guarda o ID da thread vencedora
static int id_vencedor = -1;

// Função que cada thread irá executar
void *executar_corrida(void *arg) {
    // Converte o argumento genérico para o tipo correto
    ArgumentosThread *args = (ArgumentosThread *)arg;

    // Faz todas as threads esperarem aqui até que todas estejam prontas
    pthread_barrier_wait(args->barreira_inicio);

    // Loop simulando a "corrida"
    for (int i = 0; i < 100; i++) {
        printf("Thread %d -> %d\n", args->id, i);
        fflush(stdout); // Garante que a saída seja exibida imediatamente
    }

    // Região crítica: definição do vencedor
    pthread_mutex_lock(&mutex_vencedor); // trava o mutex

    // Apenas a primeira thread que entrar aqui define o vencedor
    if (id_vencedor == -1) {
        id_vencedor = args->id;
    }

    pthread_mutex_unlock(&mutex_vencedor); // libera o mutex

    return NULL; // encerra a thread
}

int main(int argc, char *argv[]) {
    int quantidade_threads;

    srand(time(NULL)); // inicializa o gerador de números aleatórios

    // Se o usuário passou argumento na linha de comando
    if (argc == 2) {
        quantidade_threads = atoi(argv[1]); // converte string para inteiro
    } else {
        // Caso contrário, gera um número aleatório entre 1 e 10
        quantidade_threads = (rand() % 10) + 1;
        printf("Quantidade de threads (aleatoria): %d\n", quantidade_threads);
    }

    // Validação: número de threads deve ser maior que 0
    if (quantidade_threads <= 0) {
        fprintf(stderr, "Erro: a quantidade de threads deve ser maior que 0.\n");
        return 1;
    }

    // Aloca memória para o vetor de threads
    pthread_t *threads = malloc(sizeof(pthread_t) * quantidade_threads);

    // Aloca memória para os argumentos de cada thread
    ArgumentosThread *args = malloc(sizeof(ArgumentosThread) * quantidade_threads);

    // Verifica se a alocação deu certo
    if (threads == NULL || args == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        free(threads);
        free(args);
        return 1;
    }

    // Cria a barreira que sincroniza o início das threads
    pthread_barrier_t barreira_inicio;

    if (pthread_barrier_init(&barreira_inicio, NULL, quantidade_threads) != 0) {
        fprintf(stderr, "Erro ao criar barreira.\n");
        free(threads);
        free(args);
        return 1;
    }

    // Cria as threads
    for (int i = 0; i < quantidade_threads; i++) {
        args[i].id = i + 1; 
        args[i].barreira_inicio = &barreira_inicio; // passa a barreira

        // Cria a thread
        if (pthread_create(&threads[i], NULL, executar_corrida, &args[i]) != 0) {
            fprintf(stderr, "Erro ao criar thread %d.\n", i + 1);
            pthread_barrier_destroy(&barreira_inicio);
            free(threads);
            free(args);
            return 1;
        }
    }

    // Espera todas as threads terminarem (join)
    for (int i = 0; i < quantidade_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Exibe o resultado final
    printf("\nRESULTADO\n");
    printf("A thread vencedora foi: Thread %d\n", id_vencedor);

    // Libera recursos
    pthread_barrier_destroy(&barreira_inicio);
    pthread_mutex_destroy(&mutex_vencedor);    
    free(threads); 
    free(args);    

    return 0;
}