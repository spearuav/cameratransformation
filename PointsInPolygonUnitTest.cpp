/***********************************************************************
 *
 *   File Name      :  PointsInPolygonUnitTest.cc
 *
 *   Project        :  NinoxC2
 *
 *   Date created   :  May 10, 2021
 *
 *   Author         :  Eden Ben Asulin
 *
 *   Description    :  the file implements points in polygon unit test
 *
 *   Change History :
 *
 *   Copyright (c) 2021, SpearUAV Ltd. Confidential Proprietary
 *
 **********************************************************************************************/

 /*************************************  INCLUDE FILES*****************************************/

#include <iostream>
#include <iomanip>
#include "argvparser.h"
#include "PointsInPolygon.h"


using namespace std;
using namespace CommandLineProcessing;

/**************************************  CONSTANTS ******************************************/

/**************************************** MACROS ********************************************/

/************************************* STRUCTURES *******************************************/

/**************************************  STATICS   ******************************************/

/************************************    GLOBALS   ******************************************/

/******************************     Type Definitions   ***************************************/

/******************************     Forward Declarations  ***********************************/

/******************************************++++++*********************************************/

/*********************************************************************************************
 *  Name       : isPOIInsidePolygon
 *  Purpose    : Check if point is inside polygon and print the results
 *  Parameters :
 *  Returns    : void
 **********************************************************************************************/
void isPOIInsidePolygon(GeoPoint p, GeoPoint polygon[], int numberOfVertics) {

	bool flag;

	flag = pointInPolygon(p, polygon, numberOfVertics);

	cout << fixed << showpoint;
	//cout << std::setprecision(6);
	cout << "Point to test :" << setw(10) << left << p.latitude << setw(10) << left << p.longitude;
	cout << "Is inside :  " << setw(10) << left << flag << endl;
	return;
}

/*********************************************************************************************
 *  Name       : printPolygon
 *  Purpose    : Print polygon points
 *  Parameters :
 *  Returns    : void
 **********************************************************************************************/
void printPolygon( GeoPoint polygon[]) {

	cout << "Polygon[0]:" << setw(10) << left << polygon[0].latitude << setw(10) << left << polygon[0].longitude;
	cout << "Polygon[1]:" << setw(10) << left << polygon[1].latitude << setw(10) << left << polygon[1].longitude;
	cout << "Polygon[2]:" << setw(10) << left << polygon[2].latitude << setw(10) << left << polygon[2].longitude;
	cout << "Polygon[3]:" << setw(10) << left << polygon[3].latitude << setw(10) << left << polygon[3].longitude << endl;
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
	GeoPoint polygon1[] = { {0, 0}, {10, 0}, {10, 10}, {0, 10} };
	const GeoPoint PointsToTest1[] = { {20, 20},{5, 5}, {3,1},{5,1} };

	GeoPoint polygon2[] = { {1, 1}, {1, 4}, {4, 4}, {4, 1} };
	const GeoPoint PointsToTest2[] = { { 8,1 }, { 2,2 }, { 1.5333,2.3434 }, { 1.01,1.01 } };

	GeoPoint polygon3[] = { {32.09259, 34.77347}, {32.09156, 34.78280}, {32.08562, 34.78157}, {32.08782, 34.77147} };
	const GeoPoint PointsToTest3[] = { { 32.08816,34.77625 }, { 32.08747,34.79002 }, { 32.08238,34.76918 }, { 32.08701,34.78042 } };

	// Print first polygon
	cout << "First polygon:" << endl;
	printPolygon(polygon1);
	cout << "Check points inside first polygon:" << endl;
	int n1 = sizeof(polygon1) / sizeof(polygon1[0]);
	for (int i = 0; i < sizeof(PointsToTest1) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest1[i],polygon1, n1 );
	}

	// Print second polygon
	cout << "\n Second polygon:" << endl;
	printPolygon(polygon2);
	cout << "Check points inside second polygon" << endl;
	int n2 = sizeof(polygon2) / sizeof(polygon2[0]);
	for (int i = 0; i < sizeof(PointsToTest2) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest2[i], polygon2, n2);
	}

	// Print third polygon
	cout << "\n Third polygon:" << endl;
	printPolygon(polygon3);
	cout << "Check points inside third polygon" << endl;
	int n3 = sizeof(polygon3) / sizeof(polygon3[0]);
	for (int i = 0; i < sizeof(PointsToTest3) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest3[i], polygon3, n3);
	}
	return 0;
}
