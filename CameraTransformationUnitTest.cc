/***********************************************************************
 *
 *   File Name      :  CameraTransformationUnitTest.cc
 *
 *   Project        :  NinoxC2
 *
 *   Date created   :  Aug 26, 2020
 *
 *   Author         :  Ram Sobol
 *
 *   Description    :  the file implements camera transform unit test 
 *
 *   Change History :  
 *                                   
 *   Copyright (c) 2020, SpearUAV Ltd. Confidential Proprietary
 *
 **********************************************************************************************/

/*************************************  INCLUDE FILES*****************************************/

#include <iostream>
#include <iomanip>
#include "argvparser.h"
#include "CameraTransformation.h"

using namespace std;
using namespace CommandLineProcessing;

/**************************************  CONSTANTS ******************************************/

/**************************************** MACROS ********************************************/


/************************************* STRUCTURES *******************************************/

struct touchpoint{
	double xraw;
	double yraw;			
};

/**************************************  STATICS   ******************************************/

/************************************    GLOBALS   ******************************************/

/******************************     Type Definitions   ***************************************/

/******************************     Forward Declarations  ***********************************/


/******************************************++++++*********************************************/


/*********************************************************************************************
 *
 *  Name       : rads
 *  Purpose    : convert degrees to radians
 *  Parameters : angle in degrees
 *  Returns    : angle in radians
 * 
 **********************************************************************************************/
double rads(double degs)
{
  return degs/180*M_PI;
}

/*********************************************************************************************
 *  Name       : calculatePoi
 *  Purpose    : calculates POI based on camera 2D x , y and print the results 
 *  Parameters : 
 *  Returns    : void
 **********************************************************************************************/
void calculatePoi(CameraTransformation *myCam , double xraw, double yraw){
	
  double xvec;
  double yvec;
  double zvec;
  double radius;
  double theta;
  double xpix;
  double ypix;
	
  myCam->getPixelVector(xraw, yraw, xvec, yvec, zvec);
  myCam->getPixelVectorPolar(xraw, yraw, radius , theta);
  mycam->getPointPixel(xvec,yvec,zvec,xpix,ypix);
  cout << fixed << showpoint;
  cout << std::setprecision(2);
  cout << "TouchPoint :" << setw(10) << left << xraw << setw(10) << left << yraw ;
  cout << setw(5) << left << " X " << xvec << setw(10) << left << " Y " << yvec << setw(5) << left << " Z " << zvec << setw(5) << left << " Radius: " << radius << setw(5) << left <<  " Theta: " << theta << endl;
  cout << "NewPoint :" << setw(10) << left << xpix << setw(10) << left << ypix ;
  return;	
}

/*********************************************************************************************
 *
 *  Name       : main
 *  Purpose    :  
 *  Parameters : argc argv
 *  Returns    : void
 *
 **********************************************************************************************/
int main(int argc, char** argv)
{
  const double camerawFovRads = (30.0 / 180 ) * M_PI;
  const double cameraWpixels = 1920;
  const double cameraHpixels = 1080;
  const double gimbalPitchRad = rads(-45);
  const double currentAltitude = 100 ;
  const double bodyYawRad = rads(0);
  const double bodyPitchRads = rads(0);
  const double bodyRollRads = rads (0);
  const touchpoint touchPoints[] = {{cameraWpixels / 2, cameraHpixels / 2 	},
									{0				  ,	0					},
									{cameraWpixels	  ,	0					},
									{cameraWpixels	  , cameraHpixels		},
									{0                ,  cameraHpixels 		}
									};

  const touchpoint touchPointsOutside[] = {
                  {-cameraWpixels / 2           , cameraHpixels / 2},
									{cameraWpixels * 1.5				  ,	cameraHpixels / 2},
									{cameraWpixels / 2            ,	-cameraHpixels / 2},
									{cameraWpixels / 2	          , cameraHpixels * 1.5},
									{cameraWpixels * 2            ,  cameraHpixels * 2}
									};
  ArgvParser cmd;     
  CameraTransformation myCam;

  cmd.addErrorCode(0, "Success");
  cmd.addErrorCode(1, "Error");

  cmd.setHelpOption("h", "help", "Print this help page");
  cmd.defineOption("f", "set input filename");
  cmd.defineOptionAlternative("f","file");

  int result = cmd.parse(argc, argv);

  if (result != ArgvParser::NoParserError) {
     cout << cmd.parseErrorDescription(result);
     exit(1);
  }
  
  myCam.setBodyOrientation(bodyYawRad , bodyPitchRads , bodyRollRads );
  myCam.setGimbalOrientation(rads(0), gimbalPitchRad , rads(0));
  myCam.setCameraParameters(cameraWpixels, cameraHpixels, camerawFovRads);
  myCam.setWindowSize(cameraWpixels, cameraHpixels);
  myCam.setCurrentAltitude( currentAltitude );
  
  double xraw = cameraWpixels / 2 ;
  double yraw = cameraHpixels / 2 ;
  double vecx = 0;
  double vecy = 0;
  double vecz = 0;
  
  cout << "POI calculation for normal points:" << endl;
  for (int i = 0 ; i < sizeof(touchPoints)/sizeof(touchpoint) ;i++ ){
	  calculatePoi(&myCam , touchPoints[i].xraw , touchPoints[i].yraw);
  }
  cout << "POI calculations for points outside the FOV"
  for (int i = 0 ; i < sizeof(touchPointsOutside)/sizeof(touchpoint) ;i++ ){
	  calculatePoi(&myCam , touchPointsOutside[i].xraw , touchPoints[i].yraw);
  }
  
  return 0;
}
