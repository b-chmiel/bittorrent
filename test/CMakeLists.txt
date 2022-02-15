find_package(Boost REQUIRED COMPONENTS unit_test_framework filesystem)
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

file(GLOB test_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp main.cpp)

add_executable(test ${test_srcs})
target_link_libraries(test ${Boost_LIBRARIES} torrent utils)

file(COPY fixtures DESTINATION .)
