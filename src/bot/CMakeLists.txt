# CPMAddPackage("gh:brainboxdotcc/DPP@10.1.2")
include(FetchContent)
FetchContent_Declare(
    dpp
    GIT_REPOSITORY https://github.com/brainboxdotcc/DPP
    GIT_TAG        v10.1.3
)
FetchContent_MakeAvailable(dpp)
target_link_libraries(${PROJECT_NAME} PRIVATE dpp)
target_include_directories(${PROJECT_NAME} PRIVATE ".")
target_sources(${PROJECT_NAME} PRIVATE "mettaton.cpp")
