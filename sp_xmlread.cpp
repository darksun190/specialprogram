/*
  this lib is for Carl Zeiss Calypso special program
  this lib read all file information in the transfer folder
  only for curve files
*/
#include "sp_xmlread.h"


Sp_xmlread::Sp_xmlread()
{
}

Sp_xmlread::Sp_xmlread(const QString &foldername)
{
    {
        //list names
        QString fileName(QString("%1/ElementsToSpecialProgram.xml").arg(foldername));
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            //return false;
        }
        QXmlStreamReader reader;

        reader.setDevice(&file);

        reader.readNext();
        while(!reader.atEnd())
        {
            if (reader.isStartElement())
            {
                if(reader.name()== "Name")
                {
                    paras.insert("Name",reader.readElementText());
                }
                if(reader.name()== "Element")
                {
                    //insert a name;
                    QString buf;
                    buf = reader.attributes().value("Identifier").toString();

                    /*buf = reader.attributes().value("ActPoints").toString();
                    QStringList listbuf;
                    listbuf = buf.split("\\");
                    QString tmp;
                    tmp = listbuf.at(listbuf.size()-1);
                    int pos;
                    pos = tmp.lastIndexOf("_");
                    names.push_back(tmp.left(pos));*/
                    names.push_back(buf);
                    qDebug()<<names.last();
                }
            }
            reader.readNext();
        }
    }
    {
        //sys paras
        QString fileName(QString("%1/SysParaToSpecialProgram.xml").arg(foldername));
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            //return false;
        }
        QXmlStreamReader reader;

        reader.setDevice(&file);

        reader.readNext();
        while(!reader.atEnd())
        {
            if (reader.isStartElement())
            {
                if(reader.name()== "InLengthUnit")
                {
                    paras.insert("InLengthUnit",reader.readElementText());
                }
                if(reader.name()== "OutLengthUnit")
                {
                    paras.insert("OutLengthUnit",reader.readElementText());
                }


                if(reader.name()== "InAngleUnit")
                {
                    paras.insert("InAngleUnit",reader.readElementText());
                }
                if(reader.name()== "OutAngleUnit")
                {
                    paras.insert("OutAngleUnit",reader.readElementText());
                }
                if(reader.name()== "InDecimalUnits")
                {
                    paras.insert("InDecimalUnits",reader.readElementText());
                }
                if(reader.name()== "OutDecimalUnits")
                {
                    paras.insert("OutDecimalUnits",reader.readElementText());
                }
                if(reader.name()== "InLanguage")
                {
                    paras.insert("InLanguage",reader.readElementText());
                }
                if(reader.name()== "OutLanguage")
                {
                    paras.insert("OutLanguage",reader.readElementText());
                }
                if(reader.name()== "CncMode")
                {
                    paras.insert("CncMode",reader.readElementText());
                }

                if(reader.name()== "ProtHeadData")
                {
                    //protocal data
                    QString temp;
                    temp = "changedate";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "changeoper";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "changeswi";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "changeTimestamp";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "changeTimestampOld";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "creationdate";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "creationdme";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "creationswi";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "date";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "dateandtime";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "datedayofmonth";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "datemonthindex";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "datesecondclock";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "datestring";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "dateyear";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "dmeid";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "dmesn";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "drawingno";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "mccplanversion";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "nameOfFile";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "operid";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "order";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "partnbinc";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "partnbpre";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "planid";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "produceoper";
                    paras.insert(temp,reader.attributes().value(temp).toString());
                    temp = "time";
                    paras.insert(temp,reader.attributes().value(temp).toString());

                }
            }
            reader.readNext();
        }
    }
}
