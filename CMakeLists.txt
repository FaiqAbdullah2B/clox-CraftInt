cmake_minimum_required(VERSION 3.10)
project(clox C)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")

# Set the C standard globally (this is still the correct way to do this part)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 1. explicitly list your files. No GLOB traps.
# Add new ones here as you write them.
set(SOURCES
    chunk.c
    compiler.c
    debug.c
    main.c
    memory.c
    scanner.c
    table.c
    object.c
    value.c
    vm.c
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