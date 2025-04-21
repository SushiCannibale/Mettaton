find_package(CURL REQUIRED)
include_directories(${LIBNEKO} ${CURL_INCLUDE_DIR})
target_link_libraries(${LIBNEKO} ${CURL_LIBRARIES})
# Maybe add nholmann/json as a dependency ?

target_sources(${LIBNEKO} PRIVATE "nekoreq.cpp")
target_include_directories(${LIBNEKO} PRIVATE ".")