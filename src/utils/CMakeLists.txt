file(GLOB_RECURSE utils_srcs ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(utils SHARED ${utils_srcs})