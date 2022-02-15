file(GLOB_RECURSE cli_srcs ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(cli SHARED ${cli_srcs})
