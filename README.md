# Corrida de Threads em C

Este projeto implementa uma corrida de threads em C utilizando a biblioteca POSIX Threads (`pthread`).

## Objetivo

O programa cria múltiplas threads, onde cada thread:

- aguarda em uma **barreira de sincronização** para iniciar junto com as demais;
- realiza uma contagem de **0 a 99**, imprimindo os valores na tela;
- ao finalizar, disputa para ser registrada como a vencedora;
- vence a thread que concluir sua execução primeiro.

## Requisitos

- Compilador GCC
- Biblioteca `pthread`

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

## Funcionamento Geral 
- O programa define a quantidade de threads 
- Todas as threads são criadas
- Elas aguardam na barreira até que todas estejam prontas
- Após a liberação, iniciam a execução simultaneamente
- Cada thread imprime sua contagem
- A primeira a finalizar é registrada como vencedora

## Compilação e Execução

```bash
make
make run



