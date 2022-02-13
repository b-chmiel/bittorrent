cmake_minimum_required(VERSION 3.0)
project(BitTorrent)

set(CMAKE_CXX_STANDARD 23)

include(CheckTypeSize)
check_type_size("uint" UINT)
if ("${UINT}" STREQUAL "")
	message(FATAL_ERROR "uint must be available.")
endif()

add_subdirectory(src)
add_subdirectory(test)

include_directories(${CMAKE_SOURCE_DIR}/external/uuid)