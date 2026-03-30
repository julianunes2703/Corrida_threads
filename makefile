CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -pthread
TARGET = corrida
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) 

clean:
	rm -f $(TARGET)