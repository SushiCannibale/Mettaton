cmake_minimum_required(VERSION 3.21.2)
project(mettaton)
set(LIBNEKO "libneko")

add_executable(${PROJECT_NAME})
add_library(${LIBNEKO} SHARED)

target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall
    -Wextra
    -Werror
    -pedantic
    -std=c++20
)
target_compile_options(${LIBNEKO} PRIVATE
    -Wall
    -Wextra
    -Werror
    -pedantic
    -std=c++20
)

target_include_directories(${LIBNEKO} PUBLIC 
    "include/"
)
target_include_directories(${PROJECT_NAME} PUBLIC
    "include/"
)

add_subdirectory("src/libneko/")
add_subdirectory("src/bot/")

set_target_properties(${LIBNEKO} PROPERTIES OUTPUT_NAME neko)