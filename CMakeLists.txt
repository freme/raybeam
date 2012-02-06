cmake_minimum_required(VERSION 2.6)

SET(SRC 
    image.cc
    vector3.cc
    onb.cc
    mesh.cc
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
    mesh.h
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

ADD_EXECUTABLE(simple_raytrace mesh.cc image.cc triangle.cc sphere.cc simple_raytrace.cc)
ADD_EXECUTABLE(test_mesh mesh.cc image.cc test_mesh.cc)
ADD_EXECUTABLE(test_no_mesh image.cc triangle.cc test_no_mesh.cc)
ADD_EXECUTABLE(test_instance instance.cc matrix.cc mesh.cc image.cc test_instance.cc)
ADD_EXECUTABLE(example_instances instance.cc matrix.cc mesh.cc image.cc example_instances.cc)


SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_LINKER ld)
SET(CMAKE_C_LINK_EXECUTABLE ld)

#SET(CMAKE_VERBOSE_MAKEFILE true)

#target_link_libraries(${EXENAME} mpi)
