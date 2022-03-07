file(COPY fixtures DESTINATION .)
file(COPY e2e DESTINATION .)

add_test(
	NAME e2e_test
	COMMAND python3 e2e/main.py
)

add_subdirectory(unit)
add_test(unit_test unit/unit_test)

add_custom_target(check 
	COMMAND ${CMAKE_CTEST_COMMAND} --verbose 
	DEPENDS main)