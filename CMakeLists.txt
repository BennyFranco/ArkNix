cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_definitions(-std=c++17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

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
    engine/core/events
    engine/graphics
    engine/input
)

include_directories(${INCLUDE_DIRS})

file(GLOB SOURCE_FILES 
        engine/*.cpp
        engine/**/*.cpp
    )

add_executable(Galaga ${SOURCE_FILES})
target_include_directories(Galaga PUBLIC ${INCLUDE_DIRS})

target_link_libraries(Galaga
                      PUBLIC SDL2
                      PUBLIC SDL2_image
                      )

# install(TARGETS SDL2 EXPORT SDL2Targets
#       LIBRARY DESTINATION bin
#       ARCHIVE DESTINATION bin
#       RUNTIME DESTINATION bin)
# install(TARGETS Galaga DESTINATION bin) 

# include(InstallRequiredSystemLibraries)
# set(CPACK_PACKAGE_VERSION_MAJOR "${Galaga_VERSION_MAJOR}")
# set(CPACK_PACKAGE_VERSION_MINOR "${Galaga_VERSION_MINOR}")
# set(CPACK_SOURCE_GENERATOR "ZIP")
# include(CPack)