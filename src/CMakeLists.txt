add_subdirectory(torrent)
add_subdirectory(utils)
add_subdirectory(cli)
add_subdirectory(client)

add_executable(main main.cpp)

target_link_libraries(main ${Boost_LIBRARIES} pthread boost_program_options torrent cli utils client)