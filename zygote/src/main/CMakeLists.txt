project(main)

add_executable(zygote main.cpp)
target_link_libraries(zygote bpf conf proc CLI11 spdlog::spdlog)
target_include_directories(zygote PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/include
)


add_executable(main_example_man7org main_example_man7org.c)
add_executable(main_tcp_socket main_tcp_socket.c)

add_executable(main_simple main_simple.c)
target_compile_options(main_simple PUBLIC -fpie -rdynamic -fvisibility=default)
target_link_options(main_simple PUBLIC -pie -export-dynamic -dynamic-list=/home/dcavalei/Projects/zygote/zygote/res/symbols)

#target_link_options(main_simple PUBLIC -fpie "-Wl,--help")
#target_compile_options(main_simple PUBLIC -Wall -Wextra -Werror)
