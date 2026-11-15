
cmake_minimum_required(VERSION 3.25)

project(360Browser C)

add_executable(360Browser main.c)

set_target_properties(360Browser PROPERTIES
    C_STANDARD 17
    C_EXTENSIONS ON
)

target_compile_options(360Browser PRIVATE
    -Wall
    -Wextra
    -Werror
)

xsdk_add_xex(360Browser)
