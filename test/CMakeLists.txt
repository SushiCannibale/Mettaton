target_link_libraries(${NEKO_TEST} ${LIBNEKO})
target_include_directories(${NEKO_TEST} PRIVATE ".")
target_sources(${NEKO_TEST} PRIVATE "test.cpp")