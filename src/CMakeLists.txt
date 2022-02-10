find_package(Boost 1.78.0 REQUIRED)

file(GLOB server_srcs ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/server)

add_library(libserver SHARED ${server_srcs})
add_executable(client client.cpp)
add_executable(server server.cpp)

target_link_libraries(client ${Boost_LIBRARIES} pthread)
target_link_libraries(server ${Boost_LIBRARIES} pthread libserver)