cmake_minimum_required (VERSION 3.0)
project(camera_transfomation)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(argvparser)
add_executable (unit_test CameraTransformation.cc CameraTransformationUnitTest.cc)
add_subdirectory(argvparser)
target_link_libraries (unit_test PUBLIC Eigen3::Eigen argvparser)

