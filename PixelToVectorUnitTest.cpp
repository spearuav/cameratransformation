#include <iostream>
#include <iomanip>
#include "CameraTransformation.h"
//#include <assert.h>
#include "gtest/gtest.h"


using namespace std;


/**************************************  CONSTANTS ******************************************/
double const RADIUS_MAX_METER = 5000;
const double Z_EPSILON = 0.001;
const double PRECISION = 0.001;

/************************************* STRUCTURES *******************************************/

struct touchpoint {
	double xraw;
	double yraw;
};


/*********************************************************************************************
 *  Name       : rads
 *  Purpose    : convert degrees to radians
 *  Parameters : angle in degrees
 *  Returns    : angle in radians
 *
 **********************************************************************************************/
double rads(double degs)
{
	return degs / 180 * M_PI;
}

/*********************************************************************************************
 *  Name       : calculatePoiPolar
 *  Purpose    : calculates POI based on camera 2D x , y and print the results
 *  Parameters : CameraTransformation *myCam, double xraw, double yraw, double &outRadius, double &outTheta
 *  Returns    : void
 **********************************************************************************************/
void calculatePoiPolar(CameraTransformation *myCam, double xraw, double yraw, double &outRadius, double &outTheta) { 

	double xvec;
	double yvec;
	double zvec;
	double radius;
	double theta;
	double xpix;
	double ypix;
	bool flag;

	myCam->getPixelVector(xraw, yraw, xvec, yvec, zvec);
	myCam->getPixelVectorPolar(xraw, yraw, radius, theta);
	flag = myCam->getPointPixel(xvec, yvec, zvec, xpix, ypix);

	
	if (radius > RADIUS_MAX_METER) {
		radius = RADIUS_MAX_METER;
	}
	outRadius = radius;
	outTheta = theta;

	/* // Uncomment if you want to print the data
	cout << fixed << showpoint;
	cout << std::setprecision(2);
	cout << "TouchPoint :" << setw(10) << left << xraw << setw(10) << left << yraw;
	cout << setw(5) << left << " X " << xvec << setw(10) << left << " Y " << yvec << setw(5) << left << " Z " << zvec << setw(5) << left << " Radius: " << radius << setw(5) << left << " Theta: " << theta << endl;
	cout << "Estimated pixel from vector:  " << setw(10) << left << xpix << setw(10) << left << ypix << setw(10) << left <<"Not on screen:"<< flag << endl;
	*/
}

/*********************************************************************************************
 *  Name       : calculateExpectedVectorPolar
 *  Purpose    : Calculate the expected output for the camera transformation transform
 *  Parameters : double xraw, double yraw, double &expactedRadius, double &expactedTheta
 *  Returns    : void
 **********************************************************************************************/
void calculateExpectedVectorPolar(double xraw, double yraw, double &expactedRadius, double &expactedTheta) { 

	double x;
	double y;
	double z;
	double radius;
	double theta;
	double height = 100; //in meters

	// the following quaternions and matrix were calculated for:
	// 640x480 sensor and 640x480 frame shape
	// camera FOV of 55 deg
	// gimbal pitch -20 deg
	// and altitude of 100 meters
	
	Matrix<double, 3, 3> Rc_p;
	Rc_p<< 1, 0, -320,
		0, 1, -240,
		0, 0, 614.714280;
	Eigen::Quaterniond Rg_c(0.5, 0.5, 0.5, 0.5);
	Eigen::Quaterniond Rb_g(0.9848078, 0.0, -0.1736482, 0);
	Eigen::Quaterniond Rw_b(1.0, 0.0, 0.0, 0.0);

	Eigen::Quaterniond quaterniond = Rw_b * Rb_g * Rg_c;

	Vector3d pixelVec(xraw, yraw, 1);
	pixelVec = Rc_p * pixelVec;
	pixelVec = quaterniond * pixelVec;
	pixelVec.normalize();

	if (pixelVec.z() < 0) {
		pixelVec.z() = Z_EPSILON;
	}

	double scaler = height / pixelVec.dot(Vector3d::UnitZ());
	pixelVec = pixelVec * scaler;

	x = pixelVec.x();
	y = pixelVec.y();
	z = pixelVec.z();
	
	radius = sqrt((pow(x, 2)) + (pow(y, 2)));
	theta = atan2(y, x);
	theta = (theta * 180) / M_PI;

	
	if (radius > RADIUS_MAX_METER) {
		radius = RADIUS_MAX_METER;
	}

	expactedRadius = radius;
	expactedTheta = theta;

	/* // Uncomment if you want to print the data
	cout << "Expected output for touchpoint:" << setw(10) << left << xraw << setw(10) << left << yraw;
	cout << setw(5) << left << " Radius: " << radius << setw(5) << left << " Theta: " << theta <<"\n"<< endl;
	*/
}

/*********************************************************************************************
 *
 *  Name       : main
 *  Purpose    :
 *  Parameters : argc argv
 *  Returns    : void
 *
 **********************************************************************************************/
TEST(CameraTransformationTest, CheckRadiusAdnAngleMatch)
{
	const double camerawFovRads = (55.0 / 180) * M_PI;
	const double cameraPixelSize = 2.9e-6;
	const double cameraWpixels = 640; 
	const double cameraHpixels = 480; 
	const double gimbalPitchRad = rads(-20);
	const double currentAltitude = 100;
	const double bodyYawRad = rads(0);
	const double bodyPitchRads = rads(0);
	const double bodyRollRads = rads(0);
	const touchpoint touchPoints[] = { {cameraWpixels / 2    , cameraHpixels / 2 	},
					{0    , cameraHpixels / 2 				},
					{cameraWpixels    , cameraHpixels / 2	},
					{0					, 0    				},
					{cameraWpixels		, 0	        		},
					{cameraWpixels		, cameraHpixels    	},
					{0					, cameraHpixels    	},
					{cameraWpixels/2	, 0      			},
					{cameraWpixels / 4  , cameraHpixels / 4 },
					{1	    			,1					},
					{100				,100				},
					{20					,20					},
					{630				,470				},
					{639				,0					},
					{0					,479				},
					{639				,479				} };
	double CTRadius;
	double CTTheta;
	double expactedRadius;
	double expactedTheta;

	// Define camera parameters, in this test we define:
	// 640x480 sensor and 640x480 frame shape
	// camera FOV of 55 deg
	// gimbal pitch -20 deg
	// and altitude of 100 meters
	CameraTransformation myCam;
	myCam.setBodyOrientation(bodyYawRad, bodyPitchRads, bodyRollRads);
	myCam.setGimbalOrientation(rads(0), gimbalPitchRad, rads(0));
	myCam.setCameraParameters(cameraWpixels, cameraHpixels, camerawFovRads, cameraPixelSize);
	myCam.setWindowSize(cameraWpixels, cameraHpixels);
	myCam.setCurrentAltitude(currentAltitude);

	for (int i = 0; i < sizeof(touchPoints) / sizeof(touchpoint); i++) {
		calculatePoiPolar(&myCam, touchPoints[i].xraw, touchPoints[i].yraw, CTRadius, CTTheta);
		calculateExpectedVectorPolar(touchPoints[i].xraw, touchPoints[i].yraw, expactedRadius, expactedTheta);
		// Assert outputs are equal with precision of 0.001
		ASSERT_TRUE(abs(CTRadius - expactedRadius) < PRECISION);
		ASSERT_TRUE(abs(CTTheta - expactedTheta) < PRECISION);

	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
