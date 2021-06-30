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
#include "PointsInPolygon.h"


using namespace std;

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
	const GeoPoint PointsToTest1[] = { {20, 20},{5, 5}, {3,1},{5,1} }; // Need to return 0,1,1,1

	GeoPoint polygon2[] = { {1, 1}, {1, 4}, {4, 4}, {4, 1} };
	const GeoPoint PointsToTest2[] = { { 8,1 }, { 2,2 }, { 1.5333,2.3434 }, { 1.01,1.01 } }; // Need to return 0,1,1,1

	GeoPoint polygon3[] = { {32.09259, 34.77347}, {32.09156, 34.78280}, {32.08562, 34.78157}, {32.08782, 34.77147} };
	const GeoPoint PointsToTest3[] = { { 32.08816,34.77625 }, { 32.08747,34.79002 }, { 32.08238,34.76918 }, { 32.08701,34.78042 } }; //Need to return 1,0,0,1

	GeoPoint polygon4[] = { { 60.87114,-2.92401} , {60.89949,0.57570},{59.86490,0.19504}, {59.67717,-2.76476} };
	const GeoPoint PointsToTest4[] = { {60.35078,-1.47519},{60.58245,-1.11784},{60.13099,-2.07725}, {59.79267,-3.44839}, {60.38535, 1.63610 }, {61.08972,0.9024} }; // Need to return 1,1,1,0,0,0

	// Check polygon on the 180th meridian
	GeoPoint polygon5[] = { {26.800399629288354, -176.22466496854983},{27.717896219550493, -168.42484891637156},{ 22.636058731914588, -169.326335193759},{22.080250792745936, -178.78540859707067} };
	const GeoPoint PointsToTest5[] = { {25.333450917600157, -173.91215669177336}, {23.860453385784098, -171.67803852607406}, {20.595635969377824, 179.98647966272037} }; // Need to return 1,1,0

	GeoPoint polygon6[] = { {32.22750154329686, 34.82284113410079} , {32.22314564167055, 34.8230546245235}, {32.22486347283182, 34.818282968855975}, {32.22534551924556, 34.81825366362779} };
	const GeoPoint PointsToTest6[] = { {32.225063 ,34.818363} ,{32.225049, 34.818673} }; // Need to return 1,1

	GeoPoint polygon7[] = { {0, 5}, {0, 10}, {5, 15}, {5, 0} };
	const GeoPoint PointsToTest7[] = { {4, 3},{4, 7}, {4, 12}, {1,14}, {0, 0} }; // Need to return 1,1,1,0,0

	GeoPoint polygon8[] = { {0, 10}, {5, 15}, {5, 0}, {0, 5} };
	const GeoPoint PointsToTest8[] = { {4, 3},{4, 7}, {4, 12}, {1,14}, {0, 0} }; // Need to return 1,1,1,0,0

	GeoPoint polygon9[] = { {5, 15}, {5, 0}, {0, 5}, {0, 10} };
	const GeoPoint PointsToTest9[] = { {4, 3},{4, 7}, {4, 12}, {1,14}, {0, 0} }; // Need to return 1,1,1,0,0

	GeoPoint polygon10[] = { {5, 0}, {0, 5}, {0, 10}, {5, 15} };
	const GeoPoint PointsToTest10[] = { {4, 3},{4, 7}, {4, 12}, {1,14}, {0, 0} }; // Need to return 1,1,1,0,0

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

	// Print fourth polygon
	cout << "\n Fourth polygon:" << endl;
	printPolygon(polygon4);
	cout << "Check points inside fourth polygon" << endl;
	int n4 = sizeof(polygon4) / sizeof(polygon4[0]);
	for (int i = 0; i < sizeof(PointsToTest4) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest4[i], polygon4, n4);
	}

	// Print fifth polygon
	cout << "\n Fifth polygon:" << endl;
	printPolygon(polygon5);
	cout << "Check points inside fifth polygon" << endl;
	int n5 = sizeof(polygon5) / sizeof(polygon5[0]);
	for (int i = 0; i < sizeof(PointsToTest5) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest5[i], polygon5, n5);
	}

	// Print sixth polygon
	cout << "\n Sixth polygon:" << endl;
	printPolygon(polygon6);
	cout << "Check points inside sixth polygon" << endl;
	int n6 = sizeof(polygon6) / sizeof(polygon6[0]);
	for (int i = 0; i < sizeof(PointsToTest6) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest6[i], polygon6, n6);
	}

	// Print seventh polygon
	cout << "\n Seventh polygon:" << endl;
	printPolygon(polygon7);
	cout << "Check points inside seventh polygon" << endl;
	int n7 = sizeof(polygon7) / sizeof(polygon7[0]);
	for (int i = 0; i < sizeof(PointsToTest7) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest7[i], polygon7, n7);
	}

	// Print eighth polygon
	cout << "\n Eighth polygon:" << endl;
	printPolygon(polygon8);
	cout << "Check points inside eighth polygon" << endl;
	int n8 = sizeof(polygon8) / sizeof(polygon8[0]);
	for (int i = 0; i < sizeof(PointsToTest8) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest8[i], polygon8, n8);
	}

	// Print ninth polygon
	cout << "\n Ninth polygon:" << endl;
	printPolygon(polygon9);
	cout << "Check points inside ninth polygon" << endl;
	int n9 = sizeof(polygon9) / sizeof(polygon9[0]);
	for (int i = 0; i < sizeof(PointsToTest9) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest9[i], polygon9, n9);
	}

	// Print tenth polygon
	cout << "\n Tenth polygon:" << endl;
	printPolygon(polygon10);
	cout << "Check points inside tenth polygon" << endl;
	int n10 = sizeof(polygon10) / sizeof(polygon10[0]);
	for (int i = 0; i < sizeof(PointsToTest10) / sizeof(GeoPoint); i++) {
		isPOIInsidePolygon(PointsToTest10[i], polygon10, n10);
	}


	return 0;
}
