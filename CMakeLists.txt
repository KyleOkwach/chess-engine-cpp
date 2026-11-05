cmake_minimum_required(VERSION 3.16)
project(chess_assignment_1 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put the finished program in build/ no matter which IDE or command configured the project.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Recursive file globbing to pick up files from both engine and frontend modules
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_SOURCE_DIR}/src/engine/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/frontend/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Find SDL3 package on the system
find_package(SDL3 REQUIRED)

# Define the executable
add_executable(chess ${SOURCES})

# Include directories for clean modular relative header paths
target_include_directories(chess PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/engine
    ${CMAKE_SOURCE_DIR}/src/frontend
)

# Link SDL3 using its modern namespaced target
target_link_libraries(chess PRIVATE SDL3::SDL3)

# Compiler flags and Sanitizers
if(MSVC)
  target_compile_options(chess PRIVATE /W4)
else()
  target_compile_options(chess PRIVATE -Wall -Wextra -g)
  target_compile_options(chess PRIVATE -fsanitize=address,undefined -fno-sanitize-recover=all)
  target_link_options(chess PRIVATE -fsanitize=address,undefined -fno-sanitize-recover=all)
endif()

