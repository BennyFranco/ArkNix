cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

project(Galaga)

add_subdirectory(thirdparty/SDL)

add_executable(Galaga main.cpp)

target_link_libraries(Galaga
                      PUBLIC SDL2
                      )