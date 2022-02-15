include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/bencoding)

file(GLOB_RECURSE torrent_srcs ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(torrent SHARED ${torrent_srcs})