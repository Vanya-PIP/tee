cmake_minimum_required(VERSION 3.8)
project(tee)

set(SOURCE_FILES
    "main.cpp"
    "io.cpp"
    "tee.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

