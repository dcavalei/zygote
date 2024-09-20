project(main)

add_executable(zygote main.cpp)
target_link_libraries(zygote zyg)
target_include_directories(zygote PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/include
)

add_executable(main_tcp_socket main_tcp_socket.c)

add_executable(main_example_man7org main_example_man7org.c)
