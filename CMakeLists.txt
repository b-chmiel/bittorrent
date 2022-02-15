cmake_minimum_required(VERSION 3.0)
project(BitTorrent)

set(CMAKE_CXX_STANDARD 23)
# add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wcast-align -Wold-style-cast -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wlifetime -Weverything)

include(CheckTypeSize)
check_type_size("uint" UINT)
if ("${UINT}" STREQUAL "")
	message(FATAL_ERROR "uint must be available.")
endif()

add_subdirectory(src)
add_subdirectory(test)

include(cmake/CPM.cmake)
CPMAddPackage("gh:boostorg/uuid#boost-1.78.0")
CPMAddPackage("gh:boostorg/variant#boost-1.78.0")