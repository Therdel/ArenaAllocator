cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("HeteroArenaAllocator")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/example)

# Add source to this project's executable.
add_executable (HeteroArenaAllocator "main.cpp")

target_include_directories(HeteroArenaAllocator PRIVATE ${HETEROARENAALLOCATOR_INCLUDE_DIRS})
