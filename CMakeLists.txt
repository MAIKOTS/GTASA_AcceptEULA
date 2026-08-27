cmake_minimum_required(VERSION 3.10.2)
project(AcceptEULA)

# Define o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cria a biblioteca compartilhada (.so) com os arquivos fonte
add_library(AcceptEULA SHARED
    main.cpp
    mod/config.cpp
)

# Diretórios de include (equivalente ao LOCAL_C_INCLUDES)
target_include_directories(AcceptEULA PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Definições de compilação (-DNDEBUG)
target_compile_definitions(AcceptEULA PRIVATE
    NDEBUG
)

# Flags de otimização e compilação (aplicando -mfloat-abi=softfp apenas para armeabi-v7a)
target_compile_options(AcceptEULA PRIVATE
    -O2
    $<$<STREQUAL:${ANDROID_ABI},armeabi-v7a>:-mfloat-abi=softfp>
)

# Bibliotecas do sistema vinculadas (equivalente ao -llog)
target_link_libraries(AcceptEULA PRIVATE
    log
)
