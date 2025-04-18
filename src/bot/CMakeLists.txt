find_package(DPP REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ".")
target_sources(${PROJECT_NAME} PRIVATE "mettaton.cpp")

include_directories(${PROJECT_NAME} ${DPP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${DPP_LIBRARIES})