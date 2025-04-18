find_package(dpp REQUIRED)

# if(DPP-NOTFOUND)
    include_directories(${PROJECT_NAME} ${dpp_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${dpp_LIBRARIES})
# else()
    # message("Library not found. building from source")
# include(FetchContent)

# FetchContent_Declare(
#     dpp
#     GIT_REPOSITORY https://github.com/brainboxdotcc/DPP.git
#     GIT_TAG        v10.1.2 release
# )
# FetchContent_MakeAvailable(dpp)
# endif()

target_link_libraries(${PROJECT_NAME} PRIVATE dpp)
target_include_directories(${PROJECT_NAME} PRIVATE ".")
target_sources(${PROJECT_NAME} PRIVATE "mettaton.cpp")
