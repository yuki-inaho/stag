
project(Stag)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -w  ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -w ")

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)
find_package(Boost 1.66.0 REQUIRED COMPONENTS program_options)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
file(GLOB SRC_FILE1 "src/*.c*")
file(GLOB SRC_FILE2 "src/ED/*.c*")

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    src/
    src/ED/
)
add_library(
    LibStag SHARED
    ${SRC_FILE1}
    ${SRC_FILE2}
)
target_link_libraries(
    LibStag
    ${OpenCV_LIBS}
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/app)

add_executable(
    demo_with_an_image
    demo_with_an_image.cpp
)

target_link_libraries(
    demo_with_an_image
    LibStag
)

add_executable(
    demo_with_cam
    demo_with_cam.cpp
)

target_link_libraries(
    demo_with_cam
    LibStag
    Boost::program_options
)

