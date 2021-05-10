/***********************************************************************
 *
 *   File Name      :  PointsInPolygon.cpp
 *
 *   Project        :  NinoxC2
 *
 *   Date created   :  May 10, 2021
 *
 *   Author         :  Eden Ben Asulin
 *
 *   Description    :  A C++ program to check if a given point lies inside a given polygon.
 *
 *   Change History :
 *
 *   Copyright (c) 2020, SpearUAV Ltd. Confidential Proprietary
 *
 **********************************************************************************************/

 /*************************************  INCLUDE FILES*****************************************/

#include "PointsInPolygon.h"
#include <iostream>
//#include <algorithm>  

using namespace std;

struct GeoPoint;

// Returns true if the point p lies inside the polygon[] with n vertices
// Time Complexity : O(n) where n is the number of vertices in the given polygon.
bool pointInPolygon(GeoPoint p, GeoPoint polygon[], int n) {
	int count = 0, i = 1;
	GeoPoint p1 = polygon[0];

	// There must be at least 3 vertices in polygon[]
	if (n < 3) return false;

	do {
		int next = (i + 1) % n;
		GeoPoint p2 = polygon[i%n];

		if ((p.longitude > std::min(p1.longitude, p2.longitude))
			&& (p.longitude <= std::max(p1.longitude, p2.longitude))
			&& (p.latitude <= std::max(p1.latitude, p2.latitude))
			&& (p1.longitude != p2.longitude)) {
			double xinters = (p.longitude - p1.longitude)*(p2.latitude - p1.latitude) / (p2.longitude - p1.longitude) + p1.latitude;
			if (p1.latitude == p2.latitude || p.latitude <= xinters) {
				count++;
			}
		}
		p1 = p2;
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise
	return count & 1; // Same as (count%2 == 1)
}