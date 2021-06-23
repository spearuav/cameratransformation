add_executable(${PROJECT_NAME}.test
  PixelToVectorUnitTest.cpp)

target_link_libraries(${PROJECT_NAME}.test 
  ${PROJECT_NAME} gtest Eigen::Eigen argvparser)

target_compile_definitions(${PROJECT_NAME}.test 
  PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}/test")

