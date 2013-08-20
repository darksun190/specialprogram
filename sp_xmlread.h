#ifndef SP_XMLREAD_H
#define SP_XMLREAD_H
#include <QXmlStreamReader>
#include <QVector>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QMap>

class Sp_xmlread {
public:

    Sp_xmlread();
    Sp_xmlread(const QString &foldername);
    QVector <QString> names;
    QMap <QString,QString> paras;

private:
    //QVector <QString> names;
    void getelement();
};

#endif // SP_XMLREAD_H
