cmake_minimum_required(VERSION 3.8)
project(msh)
set(CMAKE_C_STANDARD 99)
cmake_minimum_required(VERSION 2.8.4)

add_custom_target(mytest COMMAND make -C ${mytest_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})