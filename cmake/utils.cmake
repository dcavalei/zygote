function(print_compiler_info)

    message(STATUS "CMake version: ${CMAKE_VERSION}")

    message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
    message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

    message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
    message(STATUS "C compiler ID: ${CMAKE_C_COMPILER_ID}")
    message(STATUS "C compiler version: ${CMAKE_C_COMPILER_VERSION}")

endfunction()
