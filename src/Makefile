# Makefile for matrix operations project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -O2 -Wno-unused-function 

# Target executable
TARGET = test_cases

# Source files
SRCS = test_cases.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = matrix.h

# Build target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Rule to compile .c files to .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program with default arguments (you can change 10 to any max value)
run: $(TARGET)
	./$(TARGET) 10

.PHONY: all clean run
