cmake_minimum_required(VERSION 3.10)
project(clox C)

# Use C99 because that's what Nystrom sticks to for clox
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Boss wants ALL the warnings and shit on. 
# We're going full "strict mode" here.
if(MSVC)
    # If you're on Windows/MSVC
    add_compile_options(/W4 /WX)
else()
    # GCC/Clang - The good stuff
    add_compile_options(
        -Wall 
        -Wextra 
        -Wpedantic 
        -Werror                # Treat warnings as errors
        -Wshadow               # Don't let variables hide other variables
        -Wdouble-promotion     # Warn if float is implicitly promoted to double
        -Wformat=2             # Extra format string checking
        -Wmissing-prototypes   # Force global functions to be in headers
        -Wstrict-prototypes    # C-style strictness
        -Wold-style-definition # No K&R style bullshit
        -Wcast-align           # Alignment checking
        -Wunused-parameter     # Clean up your signatures
        -Wuninitialized        # No garbage values
        -Wconversion           # Catch implicit type casts that might lose data
    )
endif()

# Gather all the C files. 
# Nystrom's clox usually puts them in a 'c' directory, but adjust if they're root.
file(GLOB SOURCES 
    "*.c"
    "c/*.c"
)

# If you have specific headers elsewhere
include_directories(".")
include_directories("c/")

add_executable(clox ${SOURCES})

# Need to link the math library for the VM operations
if(UNIX AND NOT APPLE)
    target_link_libraries(clox m)
endif()

# --- OPTIONAL: CLOX DEBUG FLAGS ---
# These are the ones Nystrom uses to trace the VM and GC.
# Uncomment these if you want the internal "shit" to output to console.
# add_definitions(-DDEBUG_TRACE_EXECUTION)
# add_definitions(-DDEBUG_LOG_GC)
# add_definitions(-DDEBUG_STRESS_GC)
