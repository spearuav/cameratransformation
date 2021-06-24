set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include/${PROJECT_NAME}")
set(header CameraTransformation.h PointsInPolygon.h)
set(src CameraTransformation.cc PointsInPolygon.cpp)

add_library(${PROJECT_NAME} SHARED
  ${header}
  ${src})

include_directories( Eigen3::Eigen )

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

