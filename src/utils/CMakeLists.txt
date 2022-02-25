file(GLOB_RECURSE utils_srcs ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/bencoding)

add_library(utils STATIC ${utils_srcs})
target_link_libraries(utils spdlog::spdlog)