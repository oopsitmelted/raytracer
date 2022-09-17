cmake_minimum_required(VERSION 3.14)
project(raytracer)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(common_source
  raytracer/Canvas.cpp
  raytracer/Lighting.cpp
  raytracer/Ray.cpp
  raytracer/Sphere.cpp
  raytracer/World.cpp
)

add_executable(
  raytracer
  ${common_source}
  raytracer/raytracer.cpp
)

add_executable(
  raytracer_test
  ${common_source}
  raytracer_test/test.cpp
)
target_link_libraries(
  raytracer_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(raytracer_test)