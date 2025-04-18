find_package(CURL REQUIRED)
target_link_libraries(${LIBNEKO} ${CURL_LIBRARIES})
include_directories(${LIBNEKO} ${CURL_INCLUDE_DIR})

target_sources(${LIBNEKO} PRIVATE "nekoreq.cpp")
target_include_directories(${LIBNEKO} PRIVATE ".")