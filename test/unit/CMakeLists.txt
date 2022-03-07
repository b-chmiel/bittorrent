include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE unit_srcs ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(unit_test ${unit_srcs} main.cpp)
target_link_libraries(unit_test ${Boost_LIBRARIES} torrent utils client)
target_include_directories(unit_test SYSTEM PRIVATE ${FakeIt_SOURCE_DIR}/single_header/boost)