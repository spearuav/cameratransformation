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

#include <cmath>
#include <iostream>
#include "CameraTransformation.h"



CameraTransformation::CameraTransformation()
{
  setBodyOrientation(0, 0, 0);
  setGimbalOrientation(0, 0, 0);
  setCameraParameters(1280, 720, 30);
  setWindowSize(640, 480);
  Rg_c << 0, 0, 1,
          1, 0, 0,
          0, 1, 0;

  updateCamera();

  return;
}

Quaterniond CameraTransformation::euler2Quaternion(double yaw, double pitch, double roll)
{
  // Define rotations for each axis

  AngleAxisd rollAngle(roll, Vector3d::UnitX());
  AngleAxisd pitchAngle(pitch, Vector3d::UnitY());
  AngleAxisd yawAngle(yaw, Vector3d::UnitZ());

  // Generate the combined quaternion

  Eigen::Quaterniond quaterniond = yawAngle * pitchAngle * rollAngle;

  return quaterniond;
}

void CameraTransformation::updateCamera()
{
  //Transformation matrix scaling and translating the pixels
  //Acts on a vector (x,y,1) containing the window coordinates and the number 1.
  Rc_p <<
    sensorW / windowW, 0, -0.5 * sensorW,
    0, sensorH / windowH, -0.5 * sensorH,
    0, 0, focalLength;

  return;
}

Vector3d CameraTransformation::pixel2Vector(double x_raw, double y_raw)
{
  //Returns a unit vector in vehicle system (world axes, vehicle origin),
  //representing the chose pixel's line of sight

  Vector3d pixel(x_raw, y_raw, 1);

  pixel = Rw_b * Rb_g * Rg_c * Rc_p * pixel;

  pixel.normalize();

  return pixel;
}


void CameraTransformation::setBodyOrientation(double yaw, double pitch, double roll)
{
  bodyRoll = roll;
  bodyPitch = pitch;
  bodyYaw = yaw;

  Rw_b = euler2Quaternion(bodyYaw,bodyPitch,bodyRoll);

  return;
}

void CameraTransformation::setGimbalOrientation(double yaw, double pitch, double roll)
{
  gimbalRollRad = roll;
  gimbalPitchRad = pitch;
  gimbalYawRad = yaw;

  Rb_g = euler2Quaternion(gimbalYawRad, gimbalPitchRad, gimbalRollRad);

  return;
}

void CameraTransformation::setCameraParameters(double wpixels, double hpixels, double wFovRad)
{
  sensorW = wpixels;
  sensorH = hpixels;

  focalLength = wpixels/2/tan(wFovRad/2);

  updateCamera();

  return;
}

void CameraTransformation::setWindowSize(int wpixels, int hpixels)
{    
  windowW = wpixels;
  windowH = hpixels;

  updateCamera();

  return;
}

void CameraTransformation::setCurrentAltitude(double alt)
{    
  height=alt;
  return;
}

//Outputs a unit vector independent on heigh estimate
//Axes are north, east and down relative to camera location

void CameraTransformation::getPixelDirection(double x_raw, double y_raw, double &v1, double &v2, double &v3)
{
  Vector3d pixel=pixel2Vector(x_raw, y_raw);

  v1 = pixel.x();
  v2 = pixel.y();
  v3 = pixel.z();

  return;
}

//Outputs a scaled vector based on height estimate
//Axes are north, east and down relative to camera location

void CameraTransformation::getPixelVector(double x_raw, double y_raw, double &x, double &y, double &z)
{
  Vector3d pixel = pixel2Vector(x_raw, y_raw);

  if (pixel.z() < 0){
      pixel.z() = Z_EPSILON;
  }

  double scaler = height / pixel.dot(Vector3d::UnitZ());

  pixel = pixel * scaler;

  x = pixel.x();
  y = pixel.y();
  z = pixel.z();

  return;
}

void CameraTransformation::getPixelVectorPolar(double x_raw, double y_raw, double &radius, double &angle)
{
    double xVec;
    double yVec;
    double zVec;

    getPixelVector(x_raw, y_raw, xVec, yVec , zVec);

    polar(xVec, yVec , radius , angle);

    return;
}

void CameraTransformation::polar(double x, double y, double &r , double &theta)
{
    r = sqrt((pow(x,2))+(pow(y,2)));

    theta = atan2(y , x);
    theta = (theta * 180)/3.141592654;    
}
