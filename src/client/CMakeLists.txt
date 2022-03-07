include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE srcs ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(client STATIC ${srcs})
target_link_libraries(client utils)