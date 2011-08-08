cmake_minimum_required(VERSION 2.6)

SET(SRC 
    image.cc
    vector3.cc
    )

SET(FLS
    rgb.h
    image.h
    vector3.h
    )

PROJECT(RayBeam)

ADD_DEFINITIONS("-g -Wall -pedantic")

ADD_EXECUTABLE(test_image image.cc test_image.cc)
ADD_EXECUTABLE(test_vector3 vector3.cc test_vector3.cc)

#SET(CMAKE_C_COMPILER gcc)
#SET(CMAKE_CXX_COMPILER g++)

#SET(CMAKE_VERBOSE_MAKEFILE true)

#target_link_libraries(${EXENAME} mpi)
