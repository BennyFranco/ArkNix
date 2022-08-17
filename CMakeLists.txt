cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_definitions(-std=c++17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEDITOR_DEBUG")

project(Galaga VERSION 0.0.1)

set(BUILD_SHARED_LIBS ON)
set(SDL_STATIC OFF)
set(SDL2_DISABLE_SDL2MAIN ON)
set(SDL2_DISABLE_INSTALL ON)

set(SDL2IMAGE_SAMPLES OFF)
set(SDL2IMAGE_TESTS OFF)
set(SDL2IMAGE_INSTALL OFF)

add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/SDL_image)

set(INCLUDE_DIRS
    engine/core
    engine/core/asset_manager
    engine/core/events
    engine/game
    engine/graphics
    engine/graphics/sprites
    engine/input
)
include_directories(${INCLUDE_DIRS})

file(GLOB SOURCE_FILES 
        engine/*.cpp
        engine/**/*.cpp
        engine/**/**/*.cpp
    )

add_library(NimEngine ${SOURCE_FILES})

add_executable(Galaga game/main.cpp)
#target_include_directories(Galaga PUBLIC ${INCLUDE_DIRS})

target_link_libraries(NimEngine
                      PUBLIC SDL2
                      PUBLIC SDL2_image
                      )

target_link_libraries(Galaga
                      PUBLIC SDL2
                      PUBLIC SDL2_image
                      NimEngine
                      )