cmake_minimum_required(VERSION 2.6)


PROJECT(RayBeam)

# -ansi needed for uint64_t numbers
ADD_DEFINITIONS("-g -Wall -pedantic")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

ADD_EXECUTABLE(test_image image.cc test_image.cc)
ADD_EXECUTABLE(test_vector2 test_vector2.cc)
ADD_EXECUTABLE(test_vector3 vector3.cc test_vector3.cc)
ADD_EXECUTABLE(test_onb vector3.cc onb.cc test_onb.cc)
ADD_EXECUTABLE(test_dynarray test_dynarray.cc)
ADD_EXECUTABLE(test_rng test_rng.cc)
ADD_EXECUTABLE(test_ray vector3.cc test_ray.cc)
ADD_EXECUTABLE(test_surfaces triangle.cc sphere.cc test_surfaces.cc)
ADD_EXECUTABLE(test_solid_noise solid_noise.cc test_solid_noise.cc)

ADD_EXECUTABLE(test_noise_texture image.cc solid_noise.cc noise_texture.cc test_noise_texture.cc)
ADD_EXECUTABLE(test_wood_texture image.cc solid_noise.cc wood_texture.cc test_wood_texture.cc)
ADD_EXECUTABLE(test_turbulence_texture image.cc solid_noise.cc turbulence_texture.cc test_turbulence_texture.cc)
ADD_EXECUTABLE(test_simple_texture image.cc test_simple_texture.cc)
ADD_EXECUTABLE(test_marble_texture image.cc solid_noise.cc marble_texture.cc test_marble_texture.cc)

ADD_EXECUTABLE(test_uvsphere image.cc solid_noise.cc marble_texture.cc wood_texture.cc uvsphere.cc test_uvsphere.cc)
ADD_EXECUTABLE(test_image_texture image.cc image_texture.cc uvsphere.cc test_image_texture.cc)

ADD_EXECUTABLE(simple_raytrace image.cc triangle.cc sphere.cc simple_raytrace.cc)

SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)
# not sure if the next one even exists
SET(CMAKE_LINKER llvm-ld)
SET(CMAKE_C_LINK_EXECUTABLE llvm-ld)

#SET(CMAKE_VERBOSE_MAKEFILE true)

#target_link_libraries(${EXENAME} mpi)
