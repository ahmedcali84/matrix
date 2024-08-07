# Compiler
CC = gcc

# Compiler flags
CFLAGS = -o3 -Wall -Wextra -g -std=c11 -ggdb -pedantic

# Linker flags
LDLIBS = -lm

# Target executable
TARGET = main

# Source files
SRCS = main.c matrix.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
