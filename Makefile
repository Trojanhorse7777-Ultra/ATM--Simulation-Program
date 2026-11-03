CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
TARGET = atm
SOURCE = src/atm.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
