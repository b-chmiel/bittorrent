find_package(Boost REQUIRED COMPONENTS unit_test_framework filesystem)
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src/torrent ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB test_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB test_helpers ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(test ${test_srcs} ${test_helpers})
target_link_libraries(test ${Boost_LIBRARIES} libclient)

file(COPY fixtures DESTINATION .)
