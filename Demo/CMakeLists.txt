cmake_minimum_required(VERSION 3.18)

project(Demo LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE DEMO_SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${DEMO_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE BillyEngine)

file(GLOB ASSETS "assets/*")
file(COPY ${ASSETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

set_compiler_flags(${PROJECT_NAME})