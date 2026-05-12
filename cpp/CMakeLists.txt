cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
  ${SRC_DIR}/common.cpp
  ${SRC_DIR}/main.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
