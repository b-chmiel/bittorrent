find_package(Boost 1.78.0 REQUIRED)

file(GLOB torrent_srcs ${CMAKE_CURRENT_SOURCE_DIR}/torrent/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/torrent/bencoding/*.cpp)
file(GLOB cli_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cli/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/torrent)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/bencoding)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cli)

add_library(libclient SHARED ${torrent_srcs})
add_library(cli SHARED ${cli_srcs})

add_executable(main main.cpp)

target_link_libraries(main ${Boost_LIBRARIES} pthread boost_program_options libclient cli)