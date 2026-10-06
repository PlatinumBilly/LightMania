cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
project(LightMania VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(extern/SDL EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_mixer)
add_subdirectory(extern/SDL_ttf)

#替换了一个更加直观的添加源文件的方式
add_executable(LightMania)

target_sources(LightMania PRIVATE
    src/main.c
    src/GameEngine.c
    src/GameLoop.c
    src/RenderText.c
)

#开启严格警告（省一些麻烦，被某些神秘小Bug恶心到了）
target_compile_options(LightMania PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:
        -Wall
        -Wextra
        -Wformat=2
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wdouble-promotion
        -Wnull-dereference
        -Wstrict-prototypes
        -Wmissing-prototypes
        -Wold-style-definition
        -Wundef
        -Wpointer-arith
        -Wcast-qual
        -Wwrite-strings
        -Wswitch-enum
        -Wunused-macros
        #-Werror
    >
    $<$<C_COMPILER_ID:MSVC>:
        /W4
        /WX
        /permissive-
    >
)

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

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
