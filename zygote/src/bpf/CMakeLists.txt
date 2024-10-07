project(bpf)

add_library(${PROJECT_NAME} STATIC
        bpf/Builder.cpp
        bpf/Filter.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/include
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        seccomp
        spdlog::spdlog
        conf
)
