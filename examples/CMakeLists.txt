cmake_minimum_required (VERSION 3.8)

project("HeteroArenaAllocator_examples")

add_executable(HeteroArenaAllocator_examples "main.cpp")

target_include_directories(HeteroArenaAllocator_examples PRIVATE ${INTERNAL_INCLUDE_DIRS})
		
target_compile_features(HeteroArenaAllocator_examples PRIVATE cxx_std_17)
