# +----------------------------------------------+
# | project settings                             |
# +--------------------------------------------- +
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
project(image_beautify)

# +----------------------------------------------+
# | Complilation flags                           |
# +--------------------------------------------- +
list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

# +----------------------------------------------+
# | Load third libraries                         |
# +--------------------------------------------- +
#find_package(OpenCV REQUIRED)
#include_directories(${OPENCV_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/OpenCV/inlcude)
link_directories(${PROJECT_SOURCE_DIR}/OpenCV/lib)
# +----------------------------------------------+
# | Build executable                             |
# +--------------------------------------------- +
file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*.cpp)

link_libraries(opencv_world341.lib)


add_executable(image_beautify
    ${source_files}
)
target_link_libraries(image_beautify opencv_world341.lib)