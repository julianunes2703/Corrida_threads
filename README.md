# Corrida de Threads em C

Este projeto implementa uma corrida de threads em C utilizando a biblioteca POSIX Threads (`pthread`).

## Objetivo

O programa cria múltiplas threads, onde cada thread:

- aguarda em uma **barreira de sincronização** para iniciar junto com as demais;
- realiza uma contagem de **0 a 99**, imprimindo os valores na tela;
- ao finalizar, disputa para ser registrada como a vencedora;
- vence a thread que concluir sua execução primeiro.

## Estrutura do Projeto

O projeto possui duas versões do programa:

- `main.c` → versão **sem mutex**, usada para demonstrar o problema de **condição de corrida**
- `main_mutex.c` → versão **com mutex**, usada para garantir sincronização correta na definição da thread vencedora

## Requisitos

- Compilador GCC
- Biblioteca `pthread`
- Linux, Git Bash, WSL ou outro ambiente com suporte a POSIX Threads

## Exemplo de Saída

```text
Quantidade de threads (aleatória): 6

Thread 1 -> 0
Thread 2 -> 0
Thread 3 -> 0
...
Thread 4 -> 99

RESULTADO
A thread vencedora foi: Thread 4
```



## Compilação e Execução

```bash
# Compilar a versão sem mutex
make sem_mutex

# Executar a versão sem mutex
make run_sem_mutex

# Compilar a versão com mutex
make mutex

# Executar a versão com mutex
make run_mutex

# Remover arquivos gerados
make clean