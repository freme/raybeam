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
    dynarray.h
    rng.h
    ray.h
    shape.h
    triangle.h
    sphere.h
    )

PROJECT(RayBeam)

# -ansi needed for uint64_t numbers
ADD_DEFINITIONS("-g -Wall -pedantic")# -arch i386")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -arch i386")

ADD_EXECUTABLE(test_image image.cc test_image.cc)
ADD_EXECUTABLE(test_vector3 vector3.cc test_vector3.cc)
ADD_EXECUTABLE(test_onb vector3.cc onb.cc test_onb.cc)
ADD_EXECUTABLE(test_dynarray test_dynarray.cc)
ADD_EXECUTABLE(test_rng test_rng.cc)
ADD_EXECUTABLE(test_ray vector3.cc test_ray.cc)
ADD_EXECUTABLE(test_surfaces triangle.cc sphere.cc test_surfaces.cc)

ADD_EXECUTABLE(simple_raytrace image.cc triangle.cc sphere.cc simple_raytrace.cc)

SET(CMAKE_C_COMPILER llvm-gcc)
SET(CMAKE_CXX_COMPILER llvm-g++)
# not sure if the next one even exists
SET(CMAKE_LINKER llvm-ld)
SET(CMAKE_C_LINK_EXECUTABLE llvm-ld)

#SET(CMAKE_VERBOSE_MAKEFILE true)

#target_link_libraries(${EXENAME} mpi)
