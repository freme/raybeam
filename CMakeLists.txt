cmake_minimum_required(VERSION 2.6)

SET(SRC 
    image.cc
    )

SET(FLS
    rgb.h
    image.h
    )

PROJECT(RayBeam)

ADD_DEFINITIONS("-g -Wall -pedantic")

ADD_EXECUTABLE(imagetester ${SRC} test_image.cc)

#SET(CMAKE_C_COMPILER gcc)
#SET(CMAKE_CXX_COMPILER g++)

#SET(CMAKE_VERBOSE_MAKEFILE true)

#target_link_libraries(${EXENAME} mpi)
