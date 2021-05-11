#include "opencv2\highgui.hpp"
#include "opencv2\core.hpp"
#include "opencv2\imgproc.hpp"
#include <iostream>
#include <iomanip>
#include "CameraTransformation.h"
#include "CustomVideoCoorToCoor.h"

using namespace cv;
using namespace std;

#define window "LiveFeed"
#define M_PI 3.14159265358979323846

Mat frame;
const double camerawFovRads = (55.0 / 180) * M_PI;
const double cameraPixelSize = 2.9e-6;
const double cameraWpixels = 640;
const double cameraHpixels = 480;
const double gimbalPitchRad = -0.34906585;
const double currentAltitude = 2.1;
const double bodyYawRad = 4.712; // In radians
const double bodyPitchRads = 0;
const double bodyRollRads = 0;
const double currentLatitude = 32.14376;
const double currentongitude = 34.791120;

CustomVideoCoorToCoor myCam;
QGeoCoordinate referenceLocation;
QGeoCoordinate newLocation;

vector<Point> pts;

void drawClickedPoints(Mat img)
{

	for (size_t i = 0; i < pts.size(); i++)
	{
		newLocation = myCam.videoCoorToCoor(0, gimbalPitchRad, 0, bodyYawRad, bodyPitchRads, bodyRollRads, currentAltitude, cameraWpixels, cameraHpixels, pts[i].x, pts[i].y, referenceLocation);
		circle(img, pts[i], 4, Scalar(255, 0, 0), 2);
		putText(frame, format("Latitude: %f , Longitude: %f", newLocation.latitude(), newLocation.longitude()), Point(pts[i].x + 7, pts[i].y), FONT_HERSHEY_PLAIN, 0.8, Scalar(230, 140, 70), 1.2);
	}

}
void cbmouse(int event, int x, int y, int flags, void*userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		pts.push_back(Point(x, y));
	}
}

int GeoLocationCameraTest(int argc, char*argv[])
{
	referenceLocation.setLatitude(currentLatitude); // in decimal degrees
	referenceLocation.setLongitude(currentongitude); // in decimal degrees
	referenceLocation.setAltitude(currentAltitude); //in meters

	myCam.setCameraParameters(cameraWpixels, cameraHpixels, camerawFovRads);

	VideoCapture video(1);
	namedWindow(window);
	setMouseCallback(window, cbmouse, NULL);

	while (1)
	{
		video >> frame;
		drawClickedPoints(frame);
		imshow(window, frame);
		if (waitKey(33) == 27)
			break;
	}
}
