# +----------------------------------------------+
# | project settings                             |
# +--------------------------------------------- +
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(RBFA)

file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/code/*.cpp)

add_executable(RBFA
    ${source_files}
)