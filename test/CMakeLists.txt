include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE unit_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src *.cpp)

add_executable(unit_test ${unit_srcs} main.cpp)
target_link_libraries(unit_test ${Boost_LIBRARIES} torrent utils tracker)

file(COPY fixtures DESTINATION .)
file(COPY e2e DESTINATION .)

add_test(
	NAME e2e_test
	COMMAND python3 e2e/main.py
)

add_test(unit_test unit_test)

add_custom_target(check 
	COMMAND ${CMAKE_CTEST_COMMAND} --verbose 
	DEPENDS main)