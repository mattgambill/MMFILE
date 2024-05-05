cmake_minimum_required(VERSION 3.28.3)
project(mmfile VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(mmfile 
                main.cpp
                write_bin_file.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
