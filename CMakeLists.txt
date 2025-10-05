cmake_minimum_required(VERSION 3.16)
project(test VERSION 0.1 LANGUAGES CXX)

set(GAMU_NAME "${PROJECT_NAME}")
set(GAMU_VERSION "${PROJECT_VERSION}")

find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --always --dirty
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(GIT_COMMIT "unknown")
endif()

string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM_NAME)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_STATUS "debug")
else()
    set(BUILD_STATUS "release")
endif()

set(OUTBIN "${GAMU_NAME}-${GAMU_VERSION}_${GIT_COMMIT}-${BUILD_STATUS}-${PLATFORM_NAME}")

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(CORE_DIR "${SRC_DIR}/core")
set(SDL_DIR "${SRC_DIR}/platform/SDL_uni")

set(CORE_SRCS
    ${CORE_DIR}/Player.cpp
    ${CORE_DIR}/Level.cpp
    ${CORE_DIR}/GameScene.cpp
    ${CORE_DIR}/Splash.cpp
)

set(SDL_SRCS
    ${SDL_DIR}/Input.cpp
    ${SDL_DIR}/Renderer.cpp
    ${SDL_DIR}/PlayerRender.cpp
    ${SDL_DIR}/SplashRender.cpp
)

set(COMMON_SRCS
    ${SRC_DIR}/Config.cpp
    ${SRC_DIR}/main.cpp
)

add_executable(${OUTBIN}
    ${CORE_SRCS}
    ${SDL_SRCS}
    ${COMMON_SRCS}
)

target_compile_features(${OUTBIN} PRIVATE cxx_std_17)
target_compile_options(${OUTBIN} PRIVATE -Wall -O2 -DUSE_SDL)

target_include_directories(${OUTBIN} PRIVATE
    ${SRC_DIR}
    ${CORE_DIR}
    ${SDL_DIR}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf)

target_include_directories(${OUTBIN} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(${OUTBIN} ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})

configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/version.h.in
    ${CMAKE_BINARY_DIR}/generated/version.h
    @ONLY
)
target_include_directories(${OUTBIN} PRIVATE ${CMAKE_BINARY_DIR}/generated)
