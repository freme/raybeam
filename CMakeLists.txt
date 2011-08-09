cmake_minimum_required(VERSION 2.6)

SET(SRC 
    image.cc
    vector3.cc
    onb.cc
    )

SET(FLS
    rgb.h
    image.h
    vector3.h
    onb.h
    )

PROJECT(RayBeam)

ADD_DEFINITIONS("-g -Wall -pedantic -arch i386")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -arch i386")

ADD_EXECUTABLE(test_image image.cc test_image.cc)
ADD_EXECUTABLE(test_vector3 vector3.cc test_vector3.cc)
ADD_EXECUTABLE(test_onb vector3.cc onb.cc test_onb.cc)

#SET(CMAKE_C_COMPILER gcc)
#SET(CMAKE_CXX_COMPILER g++)

#SET(CMAKE_VERBOSE_MAKEFILE true)

#target_link_libraries(${EXENAME} mpi)
