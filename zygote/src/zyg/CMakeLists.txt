project(zyg)

add_library(${PROJECT_NAME} STATIC
        Zygote.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        spdlog
        seccomp
)
