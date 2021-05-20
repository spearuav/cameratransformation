cmake_minimum_required (VERSION 3.0)
project(PixelToVectorTest)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(argvparser)
add_executable (PixelToVectorTest CameraTransformation.cc PixelToVectorUnitTest.cpp)
add_subdirectory(argvparser)
target_link_libraries (PixelToVectorTest PUBLIC Eigen3::Eigen argvparser gtest_main)
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
#add_test(NAME example_test COMMAND example)