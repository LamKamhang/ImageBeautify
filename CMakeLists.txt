# # +----------------------------------------------+
# # | project settings                             |
# # +--------------------------------------------- +
# cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# project(ImageBeautify)

# file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/code/*.cpp)

# # Find includes in corresponding build directories
# # set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)
# # set(RESOURCE_DIR resources/resources.qrc)
# set(UI ${PROJECT_SOURCE_DIR}/code/mainwindow.ui)
# find_package(Qt5 REQUIRED Widgets)
# qt5_wrap_cpp( MOC ${PROJECT_SOURCE_DIR}/code/mainwindow.h)
# qt5_wrap_ui( UIC ${PROJECT_SOURCE_DIR}/code/mainwindow.ui)
# #qt5_add_resources(RCC resources.qrc)

# add_executable(ImageBeautify 
#     ${source_files}
#     ${MOC}
#     ${UIC}
# )

#  target_link_libraries(ImageBeautify Qt5::Widgets)

cmake_minimum_required(VERSION 3.1.0)

project(testproject)

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(helloworld_SRCS
${PROJECT_SOURCE_DIR}/code/mainwindow.ui
${PROJECT_SOURCE_DIR}/code/mainwindow.cpp
${PROJECT_SOURCE_DIR}/code/main.cpp
)
# Tell CMake to create the helloworld executable
add_executable(helloworld WIN32 ${helloworld_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(helloworld Qt5::Widgets)