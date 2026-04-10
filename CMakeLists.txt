cmake_minimum_required(VERSION 3.10)
project(clox C)

# Set the C standard globally (this is still the correct way to do this part)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 1. explicitly list your files. No GLOB traps.
# Add new ones here as you write them.
set(SOURCES
    main.c
    chunk.c
    debug.c
    value.c
    memory.c
    # add scanner.c, compiler.c, etc. as you make them
)

# 2. Define the executable target
add_executable(clox ${SOURCES})

# 3. Target-specific include directories
target_include_directories(clox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 4. Target-specific warnings (The strict shit)
if(MSVC)
    target_compile_options(clox PRIVATE /W4 /WX)
else()
    target_compile_options(clox PRIVATE
        -Wall 
        -Wextra 
        -Wpedantic 
        #-Werror                # Uncomment if you want pain
        #-Wshadow               # Nystrom's code might trip this
        -Wdouble-promotion
        -Wformat=2
        -Wmissing-prototypes
        -Wstrict-prototypes
        -Wold-style-definition
        -Wcast-align
        -Wunused-parameter
        -Wuninitialized
        #-Wconversion           # Nystrom's code WILL trip this (implicit downcasts)
    )
endif()

# 5. Link the math library (UNIX only)
if(UNIX AND NOT APPLE)
    target_link_libraries(clox PRIVATE m)
endif()

# --- OPTIONAL: CLOX DEBUG FLAGS ---
# Modern way to add definitions specifically to this executable
# target_compile_definitions(clox PRIVATE DEBUG_TRACE_EXECUTION)
# target_compile_definitions(clox PRIVATE DEBUG_LOG_GC)
# target_compile_definitions(clox PRIVATE DEBUG_STRESS_GC)