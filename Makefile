# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -O2 -Wno-unused-function -I./release/include/

# Libs
LIB=-Wl,-rpath,./release/lib -L./release/lib

# source files
SRC=test/test_cases.c

# EXECUTABLE
OBJ=gen

# LFLAGS
LFLAGS=-l:libmatrix.so

all:
	$(CC) $(CFLAGS) $(LIB) $(SRC) -o $(OBJ) $(LFLAGS)

clean:
	$(RM) -r *.dSYM *.o $(OBJ) $(OBJ1)
