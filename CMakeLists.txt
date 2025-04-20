cmake_minimum_required(VERSION 3.21.2)
project(mettaton)

set(LIBNEKO "libneko")
set(NEKO_TEST "nekotest")

# bot
add_executable(${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall
    -Wextra
    -Werror
    -pedantic
    -std=c++20
)
target_include_directories(${PROJECT_NAME} PUBLIC
    "include/"
)


# library
add_library(${LIBNEKO} SHARED)
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
set_target_properties(${LIBNEKO} PROPERTIES OUTPUT_NAME neko)


# tests
add_executable(${NEKO_TEST})
target_compile_options(${NEKO_TEST} PRIVATE
    -Wall
    -Wextra
    -Werror
    -pedantic
    -std=c++20
)
target_include_directories(${NEKO_TEST} PUBLIC
    "include/"
)


add_subdirectory("src/libneko/")
add_subdirectory("src/bot/")
add_subdirectory("test/")
