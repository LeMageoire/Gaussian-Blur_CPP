# I need a file that can compile my project on multiple OSes (linux/windows/mac)
# I need a file that can compile my project on multiple compilers (gcc/clang/msvc)
# I need a file that can compile my project on multiple architectures (x86/arm)
# I need a file that can compile my project on multiple build systems (make/ninja)
# I need a file that can compile my project on multiple IDEs (vscode/visual studio/xcode)
# I need a file that can compile my project on multiple versions of cmake (3.13.2/3.14.0/3.15.0)
# my project is called "Gaussian_Blur_CLI"
# my project has a single executable called "gaussian_blur"
# my project has a single source file called "gaussian_blur.cpp"
# my project has a single header file called "gaussian_blur.h"
# my project use an external library for file system called "filesystem"

cmake_minimum_required(VERSION 3.13.2)

project(Gaussian_Blur_CLI)

set(SOURCES gaussian_blur.cpp)
set(HEADERS gaussian_blur.h)

add_executable(gaussian_blur ${SOURCES} ${HEADERS})

# Add external library for file system
find_package(filesystem REQUIRED)

target_link_libraries(gaussian_blur PRIVATE filesystem)

# Set compiler flags based on the compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(gaussian_blur PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(gaussian_blur PRIVATE /W4)
endif()

# Set architecture-specific flags
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    # x64 architecture
    # Add specific flags if needed
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    # ARM architecture
    # Add specific flags if needed
endif()

# Set build system-specific flags
if(CMAKE_GENERATOR MATCHES "Make")
    # Make build system
    # Add specific flags if needed
elseif(CMAKE_GENERATOR MATCHES "Ninja")
    # Ninja build system
    # Add specific flags if needed
endif()

# Set IDE-specific flags
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    # Visual Studio IDE
    # Add specific flags if needed
elseif(CMAKE_GENERATOR MATCHES "Xcode")
    # Xcode IDE
    # Add specific flags if needed
elseif(CMAKE_GENERATOR MATCHES "Unix Makefiles")
    # VSCode or other Makefile-based IDE
    # Add specific flags if needed
endif()