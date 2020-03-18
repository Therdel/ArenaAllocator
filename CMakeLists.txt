cmake_minimum_required (VERSION 3.8)

project ("HeteroArenaAllocator")

set(LIST_DIR ${CMAKE_CURRENT_LIST_DIR})
set(INTERNAL_INCLUDE_DIRS
    ${LIST_DIR}/src
)

# export config to parent CMakeLists
set(HETEROARENAALLOCATOR_INCLUDE_DIRS
    ${INTERNAL_INCLUDE_DIRS}
    PARENT_SCOPE
)

# examples target (optional)
add_subdirectory(examples EXCLUDE_FROM_ALL)