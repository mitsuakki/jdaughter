cmake_minimum_required(VERSION 3.10)
project(jdaughter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/json)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} SHARED src/jdaughter.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

if(EXISTS ${PROJECT_SOURCE_DIR}/examples/example.cpp)
    add_executable(cpp_example examples/example.cpp)
    target_link_libraries(cpp_example PRIVATE ${PROJECT_NAME})
endif()