set(header CameraTransformation.h PointsInPolygon.h)
set(src CameraTransformation.cc PointsInPolygon.cpp)

add_library(${PROJECT_NAME} SHARED
  ${header}
  ${src})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

