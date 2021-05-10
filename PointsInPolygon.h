#ifndef __POINTSINPOLYGON_H
#define __POINTSINPOLYGON_H
/***********************************************************************
 *
 *   File Name      :  PointsInPolygon.h
 *
 *   Project        :  NinoxC2
 *
 *   Date created   :  May 10, 2021
 *
 *   Author         :  Eden Ben Asulin
 *
 *   Description    :  Header file for PointsInPolygon.cpp
 *
 *   Change History :
 *
 *   Copyright (c) 2021, SpearUAV Ltd. Confidential Proprietary
 *
 **********************************************************************************************/

// A struct that represents a 2D point GeoLocation (Latitude and longitude)
struct GeoPoint {
	double latitude;
	double longitude;
};

// Returns true if the point p lies inside the polygon[] with n vertices
bool pointInPolygon(GeoPoint p, GeoPoint polygon[], int numberOfVertics);

#endif