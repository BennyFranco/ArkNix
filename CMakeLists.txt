cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

set(SDL2TTF_SAMPLES OFF)
set(SDL2TTF_INSTALL OFF)

set(SDL2MIXER_INSTALL OFF)
set(SDL2MIXER_SAMPLES OFF)
set(SDL2MIXER_OPUS OFF)
set(SDL2MIXER_FLAC OFF)
set(SDL2MIXER_MOD OFF)
set(SDL2MIXER_MOD_MODPLUG OFF)
set(SDL2MIXER_MIDI_FLUIDSYNTH OFF)

set(YAML_BUILD_SHARED_LIBS ON)

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")

add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/SDL_image)
add_subdirectory(thirdparty/SDL_ttf)
add_subdirectory(thirdparty/SDL_mixer)
add_subdirectory(thirdparty/yaml-cpp)

# set(INCLUDE_DIRS
    
#     game/
#     game/components
# )

include_directories(${INCLUDE_DIRS})

file(GLOB ENGINE_SOURCE_FILES 
        engine/*.cpp
        engine/**/*.cpp
        engine/**/**/*.cpp
        engine/**/**/**/*.cpp
    )

file(GLOB GAME_SOURCE_FILES
        game/*.cpp
        game/**/*.cpp
    )

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
if(MSVC)
add_library(NimEngine STATIC ${ENGINE_SOURCE_FILES})
else()
add_library(NimEngine SHARED ${ENGINE_SOURCE_FILES})
endif()

add_executable(Galaga ${GAME_SOURCE_FILES})

target_link_libraries(NimEngine
                      PUBLIC SDL2
                      PUBLIC SDL2_image
                      PUBLIC SDL2_ttf
                      yaml-cpp
                      )

target_include_directories (NimEngine PUBLIC
    engine/components
    engine/core
    engine/core/asset_manager
    engine/core/asset_manager/assets
    engine/core/events
    engine/game
    engine/graphics
    engine/graphics/sprites
    engine/input
    engine/math
    engine/physics2d
)

if(MSVC)
target_compile_options(NimEngine PUBLIC /std:c++17)
target_compile_options(Galaga PUBLIC /std:c++17)
else()
target_compile_options(NimEngine PUBLIC -std=c++17 -pthread)
target_compile_options(Galaga PUBLIC -std=c++17 -pthread)
endif()

target_link_libraries(Galaga
                      PUBLIC SDL2
                      PUBLIC SDL2_image
                      PUBLIC SDL2_ttf
                      yaml-cpp
                      NimEngine
                      )

target_include_directories (Galaga PUBLIC
    engine/components
    engine/core
    engine/core/asset_manager
    engine/core/asset_manager/assets
    engine/core/events
    engine/game
    engine/graphics
    engine/graphics/sprites
    engine/input
    engine/math
    engine/physics2d
    game/
    game/components
    game/player
)