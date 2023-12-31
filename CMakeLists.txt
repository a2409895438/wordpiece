cmake_minimum_required(VERSION 3.10)

project(wordpiece)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


add_executable(${PROJECT_NAME} src/main.cpp src/unilib/unicode.cpp src/unilib/uninorms.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC "src/unilib")
target_include_directories(${PROJECT_NAME} PUBLIC "src")


