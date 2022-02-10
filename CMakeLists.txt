cmake_minimum_required(VERSION 3.0)
project(torrent)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost 1.78.0 REQUIRED)
add_executable(torrent server.cpp)
target_link_libraries(torrent ${Boost_LIBRARIES} pthread)