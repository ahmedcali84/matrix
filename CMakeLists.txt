# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(matrix VERSION 1.0.0)

# Specify the C and C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

# Specify the output directory for the object files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release/obj)

# Specify the output directory for the shared library
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/release/include)

# Add the source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/release/include/matrix.c
)

# Compile the source files into object files
add_library(object_files OBJECT ${SOURCES})

# Create the shared library from the object files
add_library(matrix SHARED $<TARGET_OBJECTS:object_files>)

# Optionally, specify the version of the shared library
set_target_properties(matrix PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1  # Set the shared object version (optional)
)

# Install the shared library and headers (optional)
install(TARGETS matrix
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/release/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
