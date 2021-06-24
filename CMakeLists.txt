cmake_minimum_required (VERSION 3.0)
project(CameraTransformation)

# set(CMAKE_CXX_STANDARD 17) 
set(include_dest "include/${PROJECT_NAME}")
# set(tool_dest "bin")
# set(lib_dest "lib")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(src Eigen3::Eigen/eigen3)
add_subdirectory(src)
add_subdirectory(test)

include_directories(argvparser)
add_subdirectory(argvparser)

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