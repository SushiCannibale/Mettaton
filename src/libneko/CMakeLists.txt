find_package(CURL REQUIRED)
include_directories(${LIBNEKO} ${CURL_INCLUDE_DIR})
target_link_libraries(${LIBNEKO} ${CURL_LIBRARIES})

target_sources(${LIBNEKO} PRIVATE "nekoreq.cpp")
target_include_directories(${LIBNEKO} PRIVATE ".")