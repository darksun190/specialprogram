#ifndef SP_XMLREAD_H
#define SP_XMLREAD_H
#include <QXmlStreamReader>
#include <QVector>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QMap>
class point
{
public:
    point();
    point(double ix,double iy, double iz,
          double iu = 0, double iv = 0, double iw = 1,
          double iradius = 0,
          double iut = 0.01, double ilt = -0.01,
          double istatus = 0);

    double x,y,z,u,v,w,ut,lt,radius,status;
};

class vec
{
public:
    double u,v,w;
};
class pos
{
public:
    double x,y,z;
};

class element
{
public:
    element();
    QString Identifier;
    vec v;
    pos p;
    QString type;
    double radius;  //only for circle cylinder & cone
    int direction;  //for inside or outside circle cylinder
    double width;   //only for plane
    double length;  //length for plane, axis length for circle,always 0. NOT for cylinder
    QVector <point> points; //for type != curve
    QVector <point> nom_points; //these 3 for curve
    QVector <point> act_points;
    QVector <point> mea_points;

    double height;      //for axis length of cylinder cone.

};

class Sp_xmlread {
public:

    Sp_xmlread();
    Sp_xmlread(const QString &foldername);
    QVector <element> names;
    QMap <QString,QString> paras;

private:
    //QVector <QString> names;
    void getelement();
};

#endif // SP_XMLREAD_H
