CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -pthread

TARGET_SEM_MUTEX = corrida
TARGET_MUTEX = corrida_mutex

SRC_SEM_MUTEX = main.c
SRC_MUTEX = main_mutex.c

all: sem_mutex mutex

sem_mutex: $(TARGET_SEM_MUTEX)

mutex: $(TARGET_MUTEX)

$(TARGET_SEM_MUTEX): $(SRC_SEM_MUTEX)
	$(CC) $(CFLAGS) $(SRC_SEM_MUTEX) -o $(TARGET_SEM_MUTEX)

$(TARGET_MUTEX): $(SRC_MUTEX)
	$(CC) $(CFLAGS) $(SRC_MUTEX) -o $(TARGET_MUTEX)

run_sem_mutex: sem_mutex
	./$(TARGET_SEM_MUTEX)

run_mutex: mutex
	./$(TARGET_MUTEX)

clean:
	rm -f $(TARGET_SEM_MUTEX) $(TARGET_MUTEX)