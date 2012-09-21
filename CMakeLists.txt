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
ADD_DEFINITIONS("-g -Wall -pedantic")
#ADD_DEFINITIONS("-O3 -Wall -pedantic")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -arch i386")

ADD_EXECUTABLE(test_image image.cc test/test_image.cc)
ADD_EXECUTABLE(test_vector2 test/test_vector2.cc)
ADD_EXECUTABLE(test_vector3 vector3.cc test/test_vector3.cc)
ADD_EXECUTABLE(test_onb vector3.cc onb.cc test/test_onb.cc)
ADD_EXECUTABLE(test_dynarray test/test_dynarray.cc)
ADD_EXECUTABLE(test_rng test/test_rng.cc)
ADD_EXECUTABLE(test_ray vector3.cc test/test_ray.cc)

#ADD_EXECUTABLE(test_surfaces triangle.cc sphere.cc test/test_surfaces.cc)
#ADD_EXECUTABLE(test_solid_noise solid_noise.cc test/test_solid_noise.cc)

#ADD_EXECUTABLE(test_noise_texture image.cc solid_noise.cc noise_texture.cc test/test_noise_texture.cc)
#ADD_EXECUTABLE(test_wood_texture image.cc solid_noise.cc wood_texture.cc test/test_wood_texture.cc)
#ADD_EXECUTABLE(test_turbulence_texture image.cc solid_noise.cc turbulence_texture.cc test/test_turbulence_texture.cc)
#ADD_EXECUTABLE(test_simple_texture image.cc test/test_simple_texture.cc)
#ADD_EXECUTABLE(test_marble_texture image.cc solid_noise.cc marble_texture.cc test/test_marble_texture.cc)

#ADD_EXECUTABLE(test_uvsphere image.cc solid_noise.cc marble_texture.cc wood_texture.cc uvsphere.cc test/test_uvsphere.cc)
#ADD_EXECUTABLE(test_image_texture image.cc image_texture.cc uvsphere.cc test/test_image_texture.cc)

#ADD_EXECUTABLE(simple_raytrace mesh.cc image.cc triangle.cc sphere.cc simple_raytrace.cc)
ADD_EXECUTABLE(simple_raytrace image.cc triangle.cc sphere.cc simple_raytrace.cc)
#ADD_EXECUTABLE(test_mesh mesh.cc image.cc test/test_mesh.cc)
#ADD_EXECUTABLE(test_no_mesh image.cc triangle.cc test/test_no_mesh.cc)
#ADD_EXECUTABLE(test_instance instance.cc matrix.cc mesh.cc image.cc test/test_instance.cc)

#ADD_EXECUTABLE(example_instances instance.cc matrix.cc mesh.cc image.cc example_instances.cc)

#SET(CMAKE_C_COMPILER gcc)
#SET(CMAKE_CXX_COMPILER g++)
#SET(CMAKE_LINKER ld)
#SET(CMAKE_C_LINK_EXECUTABLE ld)

SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)
SET(CMAKE_INCLUDE_PATH /Users/william/Software/dvl/raybeam)

#SET(CMAKE_VERBOSE_MAKEFILE true)
#target_link_libraries(${EXENAME} mpi)
