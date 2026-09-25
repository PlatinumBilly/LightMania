cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(LightMania VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(extern/SDL EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_mixer)
add_subdirectory(extern/SDL_ttf)

add_executable(LightMania ./src/main.c ./src/GameEngine.c ./src/GameLoop.c)

target_include_directories(LightMania PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/extern/SDL/include
    ${CMAKE_SOURCE_DIR}/extern/SDL_mixer/include
    ${CMAKE_SOURCE_DIR}/extern/SDL_ttf/include
)

target_link_libraries(LightMania 
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
