/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "CustomVideoCoorToCoor.h"
#include "CameraTransformation.h"
#include "QGCGeo.h"
#include <QDebug>



CustomVideoCoorToCoor::CustomVideoCoorToCoor()
{
    myCameraTransformation = new CameraTransformation;
}


void CustomVideoCoorToCoor::setCameraParameters(double w_pixels, double h_pixels, double w_fov){

    myCameraTransformation->setCameraParameters(w_pixels, h_pixels , w_fov);

}


QGeoCoordinate CustomVideoCoorToCoor:: videoCoorToCoor(double gimbalYaw , double gimbalPitch, double gimbalRoll,
                                   double bodyYaw ,double bodyPitch , double bodyRoll ,
                                   double alt ,
                                   int wpixels, int hpixels ,
                                   double videoX , double videoY ,
                                   QGeoCoordinate referenceLocation){

    myCameraTransformation->setWindowSize(wpixels, hpixels);
    myCameraTransformation->setBodyOrientation(bodyYaw, bodyPitch , bodyRoll);
    myCameraTransformation->setCurrentAltitude(alt);
    myCameraTransformation->setGimbalOrientation(gimbalYaw, gimbalPitch , gimbalRoll);

    double radius;
    double theta;

    myCameraTransformation->getPixelVectorPolar(videoX , videoY, radius, theta);

    if (radius > RADIUS_MAX_METER){
        radius = RADIUS_MAX_METER;
    }

    QGeoCoordinate coordinate = referenceLocation.atDistanceAndAzimuth(radius, theta);

    return  coordinate;
}


QPoint CustomVideoCoorToCoor::coorToVideoCoor(double gimbalYaw , double gimbalPitch, double gimbalRoll,
                                       double bodyYaw ,double bodyPitch , double bodyRoll ,
                                       double alt ,
                                       int wpixels, int hpixels ,
                                       QGeoCoordinate originLocation,
                                       QGeoCoordinate referenceLocation)
{
    if (originLocation.isValid() && referenceLocation.isValid() && originLocation.distanceTo(referenceLocation) > 1 /* 1 meter*/)
    {
        myCameraTransformation->setWindowSize(wpixels, hpixels);
        myCameraTransformation->setBodyOrientation(bodyYaw, bodyPitch , bodyRoll);
        myCameraTransformation->setCurrentAltitude(alt);
        myCameraTransformation->setGimbalOrientation(gimbalYaw, gimbalPitch , gimbalRoll);

        double xpoint, ypoint, x, y, down;
        convertGeoToNed(referenceLocation, originLocation, &y, &x, &down);
//        qDebug() << "Reference : " << referenceLocation.toString() <<
//                  "Origin : " << originLocation.toString();
        bool valid = myCameraTransformation->getPointPixel(x, y, down, xpoint, ypoint);
        qDebug() << "valid : " << valid <<
                    "x : " << xpoint <<
                    "y : " << ypoint;

        return QPoint(static_cast<int>(xpoint), static_cast<int>(ypoint));
    }

    return QPoint(0,0);
}
