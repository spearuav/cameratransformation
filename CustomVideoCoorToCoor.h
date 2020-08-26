#ifndef CUSTOMVIDEOCOORTOCOOR_H
#define CUSTOMVIDEOCOORTOCOOR_H

#include <QObject>
#include <QGeoCoordinate>
#include "CameraTransformation.h"

class CustomVideoCoorToCoor : public QObject
{
    Q_OBJECT
public:
    CustomVideoCoorToCoor();
    Q_INVOKABLE void setCameraParameters(double w_pixels, double h_pixels, double w_fov);
    Q_INVOKABLE QGeoCoordinate videoCoorToCoor(double gimbalYaw , double gimbalPitch, double gimbalRoll,
                                       double bodyYaw ,double bodyPitch , double bodyRoll ,
                                       double alt ,
                                       int wpixels, int hpixels ,
                                       double videoX , double videoY ,
                                       QGeoCoordinate referenceLocation);


private:
    double const RADIUS_MAX_METER = 5000;
    CameraTransformation *myCameraTransformation;
};

#endif // CUSTOMVIDEOCOORTOCOOR_H
