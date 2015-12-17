# CMakeLists.txt to build project using cmake
# run $cmake CMakeLists.txt

cmake_minimum_required(VERSION 2.6)
set(PROJECT_NAME Simulator)

project(${PROJECT_NAME})

include_directories("/usr/include/irrlicht")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
file(
GLOB_RECURSE
SOURCE_FILES
src/*.[cht]pp
)
SET(CMAKE_BUILD_TYPE Debug)

ADD_DEFINITIONS( -Wall -Wextra -std=c++11 -Wno-comment -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable)

add_executable(
${PROJECT_NAME}
${SOURCE_FILES}
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Irrlicht)

