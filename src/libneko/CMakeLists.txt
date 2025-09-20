include(FetchContent)

FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG curl-8_16_0
)
FetchContent_MakeAvailable(curl)

target_link_libraries(${LIBNEKO} PRIVATE CURL::libcurl)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
# include_directories(${LIBNEKO} ${CURL_INCLUDE_DIR})

target_include_directories(${LIBNEKO} PRIVATE ".")
target_sources(${LIBNEKO} PRIVATE "nekoreq.cpp")