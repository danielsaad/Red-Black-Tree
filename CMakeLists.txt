cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Red Black Tree" CXX)
include(ExternalProject)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11")


### EXTERNAL LIBRARIES ###
ExternalProject_Add(project_gtest
    GIT_REPOSITORY https://github.com/danielsaad/googletest
    PREFIX "project_gtest"
)

ExternalProject_Get_Property(project_gtest install_dir)
add_library(lib_gtest STATIC IMPORTED)
set_property(TARGET lib_gtest PROPERTY IMPORTED_LOCATION ${install_dir}/src/project_gtest/lib/libgtest.a)
add_dependencies(lib_gtest project_gtest)


add_subdirectory(test)
