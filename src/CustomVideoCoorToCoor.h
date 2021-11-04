#ifndef CUSTOMVIDEOCOORTOCOOR_H
#define CUSTOMVIDEOCOORTOCOOR_H

#include <QObject>
#include <QGeoCoordinate>
#include "CameraTransformation.h"
#include "PointsInPolygon.h"
#include <QPoint>
#include <QTransform>

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
    Q_INVOKABLE QPoint coorToVideoCoor(double gimbalYaw , double gimbalPitch, double gimbalRoll,
                                       double bodyYaw ,double bodyPitch , double bodyRoll ,
                                       double alt ,
                                       int wpixels, int hpixels,
                                       QGeoCoordinate originLocation,
                                       QGeoCoordinate referenceLocation);
    Q_INVOKABLE void setPixelToCameraTransformation(const QTransform& transform);
    Q_INVOKABLE bool pointInView(const QGeoCoordinate& p, const QGeoCoordinate& p1, const QGeoCoordinate& p2, const QGeoCoordinate& p3, const QGeoCoordinate& p4);


private:
    double const RADIUS_MAX_METER = 5000;
    CameraTransformation *myCameraTransformation;
    static GeoPoint tempGeoPoint[4];
};

#endif // CUSTOMVIDEOCOORTOCOOR_H
