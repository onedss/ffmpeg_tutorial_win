cmake_minimum_required(VERSION 3.20)
project(ffmpeg_tutorial_win)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)

message(STATUS "==============WINDOWS APP=================")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CURRENT_PLATFORM "x64")
    message(STATUS "Current Platform is ${CURRENT_PLATFORM}")
else()
    set(CURRENT_PLATFORM "x86")
    message(STATUS "Current Platform is ${CURRENT_PLATFORM}")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    message(STATUS "Debug Mode.")
    add_definitions(-DDebug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o0 -g")
else()
    message(STATUS "Release Mode.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o2")
endif()

set(ffmpeg_include_dir ${PROJECT_SOURCE_DIR}/FFmpeg/include)
include_directories(${ffmpeg_include_dir})

set(ffmpeg_lib_dir ${PROJECT_SOURCE_DIR}/FFmpeg/lib/${CURRENT_PLATFORM})
file(GLOB ffmpeg_dylibs ${ffmpeg_lib_dir}/*.lib)
link_directories(${ffmpeg_lib_dir})

set(sdl2_include_dir ${PROJECT_SOURCE_DIR}/SDL2/include)
include_directories(${sdl2_include_dir})

set(sdl2_lib_dir ${PROJECT_SOURCE_DIR}/SDL2/lib/${CURRENT_PLATFORM})
file(GLOB sdl2_dylibs ${sdl2_lib_dir}/*.lib)
link_directories(${sdl2_lib_dir})

include_directories(${PROJECT_SOURCE_DIR}/include)

set(demo_dir ${PROJECT_SOURCE_DIR}/demo)
file(GLOB demo_codes ${demo_dir}/*.cpp)

set(core_dir ${PROJECT_SOURCE_DIR}/src)
file(GLOB core_codes ${core_dir}/*.cpp)

foreach (demo ${demo_codes})
    get_filename_component(demo_basename ${demo} NAME_WE)
    add_executable(${demo_basename} ${demo} ${core_codes} ${src_codes})
    target_link_libraries(${demo_basename} ${ffmpeg_dylibs} ${sdl2_dylibs})
endforeach()

add_executable(ffmpeg_tutorial main.cpp)
