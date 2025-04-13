#!/usr/bin/env python

# Script to build C files
import sys
import os

BUILD_DIR  = "build/" # Build Directory
SOURCE_DIR = "src/"   # Contains Source Files
TEST_DIR   = "test/"  # Contains TEST Source Files

CC       = "gcc" # Compiles 
OUTPUT   = f"{BUILD_DIR}run" # Path to executable
CFLAGS   = f"-Wall -Werror -Wextra -std=c17 -ggdb -o" # C flags
LDFLAGS  = "-lm" # linker flags

# Dictionary Containing Paths to C source files
source_dict_doubles = [
    {"TEST"   : f"{TEST_DIR}test_doubles.c"},
    {"SOURCE" : f"{SOURCE_DIR}matrix.c"}
]

# function that returns list of paths as one string
def c_source_files(source: list[dict]) -> str:
    return " ".join([value for dictionary in source for value in dictionary.values()])


# Usage Function
def usage(subcommand: str , options: list) -> None:
    print(f"Usage: {subcommand} [OPTION]")

    print("[OPTIONS]: ")
    print(f" {options[0]} - Compile the {c_source_files(source_dict)} to {OUTPUT}. (MANDATORY)")
    print(f" {options[1]} - Remove the executable: {OUTPUT}.  (MANDATORY)")
    print(f" {options[2]} - print this usage.")
    print(f" {options[3]} - Run the Built programs '{OUTPUT}'.")


# Function that compiles a given Command
def compile(command: str) -> None:
    try:
        print("Compiling...")
        print(f"{command}\n") # print the compiling command
        exit_code = os.system(command)  # execute the compiled command
        
        if exit_code != 0:
            raise RuntimeError(f"Compilation Failed with exit_code: {exit_code}")

    except RuntimeError as e:
        print(f"{e}") # print error
        sys.exit(1) # exit with failure

    except Exception as e:
        # Catch other unexpected errors (e.g., missing variables, syntax issues)
        print(f"Unexpected error: {e}")
        sys.exit(1)

# source files
sources_doubles = c_source_files(source_dict_doubles)

# Command to be executed
command_doubles = f"{CC} {CFLAGS} {OUTPUT} {sources_doubles} {LDFLAGS}"

# List of options to be included in the cli when running this script
OPTIONS = ["-build", "-clean", "-help", "-run"]

if __name__ == "__main__":
    subcommand , *argv = sys.argv # extract commands and options
    if len(argv) != 1:
        usage(subcommand , OPTIONS) # print usage if no option specified
        sys.exit(1) # exit failure
    
    # if 'build' compile the program
    if argv[0] == OPTIONS[0]:
        try:
            # First time compiling or deletion of build directory (creates build Dir)
            os.mkdir(f"{BUILD_DIR}")

            # comile the program
            compile(command_doubles)

        except FileExistsError:
            # Directory Already Exists
            print(f"Directory '{BUILD_DIR}' exists.\n")

            # Compile the program
            compile(command_doubles)

    # if 'clean' , remove build file
    elif argv[0] == OPTIONS[1]:
        try:
            os.remove(f"{OUTPUT}") # remove the executable if option is 'clean'
            print(f"Successfully Removed '{OUTPUT}' file.") # print removed files
            sys.exit(0) # exit success
        except OSError as e:
            print(f"File: '{OUTPUT}' Removal Failed. ERROR: {e}.") # exit on os error
            sys.exit(1) # Removal Failed , exit failure

    # if 'help' , print Usage
    elif argv[0] == OPTIONS[2]:
        usage(subcommand, OPTIONS)
        sys.exit(0) # exit Success

    elif argv[0] == OPTIONS[3]:
        try:
            os.system(f"{OUTPUT}")
        except Exception as e:
            print(f"ERROR: {e}")
            exit(1)

    # else if command 'UnKnown' , exit with failure
    else:
        print(f"UnKnown Command: '{argv[0]}'.\n")
        usage(subcommand, OPTIONS)
        sys.exit(1) # exit Failure
