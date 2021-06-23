#ifndef __CAMERATRANSFORMATION_H
#define __CAMERATRANSFORMATION_H
/***********************************************************************
 *
 *   File Name      :  CameraTransformation.h
 *
 *   Project        :  NinoxC2
 *
 *   Date created   :  Aug 26, 2020
 *
 *   Author         :  Ram Sobol
 *
 *   Description    :  the file implements camera transformation class header file
 *
 *   Change History :  
 *                                   
 *   Copyright (c) 2020, SpearUAV Ltd. Confidential Proprietary
 *
 **********************************************************************************************/

/*************************************  INCLUDE FILES*****************************************/
#include "Eigen/Core"
#include "Eigen/Geometry"

using namespace std;
using namespace Eigen;

/************************************* CLASS DEFINITION  ****************************************/

class CameraTransformation{

  public:
  
  CameraTransformation();
  
  // Setters for model parameters
  
   void setBodyOrientation(double yaw, double pitch, double roll);
   void setGimbalOrientation(double yaw, double pitch, double roll);
   void setCameraParameters(double w_pixels, double h_pixels, double w_fov, double pixsize = 2.9E-6);
   void setWindowSize(int wpixels, int hpixels);
   void setCurrentAltitude(double alt);
  
  
  // Getters for model results - world-axes position of an image pixel
  
   void getPixelDirection(double xraw, double yraw, double &v1, double &v2, double &v3);
   void getPixelVector(double xraw, double yraw, double &x, double &y, double &z);
   void getPixelVectorPolar(double x_raw, double y_raw, double &radius, double &angle);

   // Getters for model results - pixel position of a real-world

   bool getPointPixel(double v1, double v2, double v3, double &xpoint, double &ypoint);
	
 private:

  const double Z_EPSILON = 0.001;

  // Body angles. All radians.
  
  double bodyYaw = 0;
  double bodyPitch = 0;
  double bodyRoll = 0;
  
  
  // Gimbal angles. All radians.
  double gimbalYawRad   = 0;
  double gimbalPitchRad = 0;
  double gimbalRollRad  = 0;
    
  // Camera and sensor information

  double sensorW = 1280;    // Pixels on sensor
  double sensorH = 720;     // Pxels on sensor
  double wFovRad = 30;      // Vertical feild of view in radians #### doesnt make sense in radians 
  double focalLength = 1;   // Focal length normalized in sensor pixels.
  double pixsize = 2.9e-6;  
    
  //Video window information

  double windowW = 640;    // Pixels on window (may change)
  double windowH = 480;    // Pixels on window(may change)
    
  //World information
  
  double height=50;             //Above sea level height estimate. Meters, but can be anything really.
  
  //Internal geometric representations
  
  Matrix<double, 3, 3> Rc_p;    //Window pixels to camera axes transformation
  Matrix3d Rg_c;                //Camera to gimbal axes transformation
  Quaterniond Rb_g;             //Gimbal to body axes transformation
  Quaterniond Rw_b;             //Body to world axes transformation
  
  
  Quaterniond euler2Quaternion(double yaw, double pitch, double roll);
  void updateCamera();
  Vector3d pixel2Vector(double xraw, double yraw);
  void polar(double x, double y, double& r, double& theta);
};
#endif
