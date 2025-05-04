# find_package(dpp REQUIRED)
CPMAddPackage("gh:brainboxdotcc/DPP@10.1.2")

target_link_libraries(${PROJECT_NAME} PRIVATE dpp)
target_include_directories(${PROJECT_NAME} PRIVATE ".")
target_sources(${PROJECT_NAME} PRIVATE "mettaton.cpp")
