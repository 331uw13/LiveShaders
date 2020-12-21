cmake_minimum_required(VERSION 3.18.2)
project(LiveShaders)

# TODO: add debug option

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused-function -lGL -lGLEW -lglfw -O3")

file(GLOB_RECURSE SOURCE_FILES "./src/*.cpp")

add_executable(
	LiveShaders
	${SOURCE_FILES}
)
