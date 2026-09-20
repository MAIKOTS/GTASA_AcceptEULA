cmake_minimum_required(VERSION 3.22.1)

project(AcceptEULA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(AcceptEULA SHARED
    main.cpp
)

target_include_directories(AcceptEULA PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(AcceptEULA PRIVATE
    NDEBUG
)

target_compile_options(AcceptEULA PRIVATE
    -O2
    $<$<STREQUAL:${ANDROID_ABI},armeabi-v7a>:-mfloat-abi=softfp>
)

target_link_libraries(AcceptEULA PRIVATE
    log
)
