cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Red Black Tree" CXX C)
include(ExternalProject)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11")


### EXTERNAL LIBRARIES ###

##GTEST AND GMOCK
ExternalProject_Add(project_gtest
    GIT_REPOSITORY https://github.com/danielsaad/googletest
    PREFIX "project_gtest"
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(project_gtest install_dir)
add_library(lib_gmock STATIC IMPORTED)
add_library(lib_gtest STATIC IMPORTED)
set_property(TARGET lib_gmock PROPERTY IMPORTED_LOCATION ${install_dir}/src/project_gtest/project_gtest-build/googlemock/libmock.a)
set_property(TARGET lib_gtest PROPERTY IMPORTED_LOCATION ${install_dir}/src/project_gtest/project_gtest-build/googlemock/gtest/libgtest.a)
add_dependencies(lib_gtest project_gtest)
add_dependencies(lib_gmock project_gtest)
include_directories(${install_dir}/src/project_gtest/googletest/include)
include_directories(${install_dir}/src/project_gtest/googlemock/include)

add_subdirectory(test)
