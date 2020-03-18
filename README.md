# HeteroArenaAllocator
Heap- and stack-local heterogeneous arena allocation in C++

## CMake Integration
If you're including this in another CMake project, you can simply clone this repo into your project directory, 
and add the following to your CMakeLists.txt:

```
add_subdirectory(HeteroArenaAllocator)

target_include_directories(<your program> ${HETEROARENAALLOCATOR_INCLUDE_DIRS})

```


### Credit
Howard Hinnants STL-compatible allocator and stack arena: \
http://howardhinnant.github.io/stack_alloc.html
