# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -O2 -Wno-unused-function -Ilib

# Target executable
TARGET = gen

# Source files
SRCS = test/test_cases.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = lib/matrix.h

# Default target
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

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CFLAGS += -g -O0
debug: clean all

# PHONY targets
.PHONY: all clean run debug
