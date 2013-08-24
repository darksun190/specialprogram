/*
 *this lib is for Carl Zeiss Calypso special program
 *this lib read all file information & values in the transfer folder
 *Author: Sun Xin
 *mail: darksun190@gmail.com
 *You can use it in GPL License
 */
#include "sp_xmlread.h"

point::point()
{
	//x=y=z=u=v=w=radius=ut=lt=status=0;
}
point::point(double ix, double iy, double iz, double iu, double iv, double iw, double iradius, double iut, double ilt, double istatus)
{
	x=ix;
	y=iy;
	z=iz;
	u=iu;
	v=iv;
	w=iw;
	radius=iradius;
	ut=iut;
	lt=ilt;
	status = istatus;
}

element::element()
{
	//9999 means not define, as same as Calypso use
	Identifier = QString("NotDefine");
	v.u = 9999;
	v.v = 9999;
	v.w = 9999;
	p.x = 9999;
	p.y = 9999;
	p.z = 9999;
	type = QString("NotDefine");
	radius = 9999;
	direction = 9999;
	width = 9999;
	length = 9999;
	points.resize(0);
	nom_points.resize(0);
	act_points.resize(0);
	mea_points.resize(0);
	height = 9999;
}

Sp_xmlread::Sp_xmlread()
{
}

Sp_xmlread::Sp_xmlread(const QString &foldername)
{
	{
		//list names
		qDebug()<<"This is the sp_xmlread part";
		QString fileName(QString("%1/ElementsToSpecialProgram.xml").arg(foldername));
		QFile file(fileName);
		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			;
			return ;
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
					//insert a element;
					element temp;

					QString type;

					type = reader.attributes().value("GeoType").toString();
					qDebug()<<type;
					temp.Identifier = reader.attributes().value("Identifier").toString();
					temp.type = type;

					if (type == QString("SpacePoint"))
					{
						QString buf;
						buf = reader.attributes().value("Vector").toString();
						QStringList vec_buf = buf.split(" ");
						temp.v.u= vec_buf[0].toDouble();
						temp.v.v= vec_buf[1].toDouble();
						temp.v.w= vec_buf[2].toDouble();
						buf = reader.attributes().value("Position").toString();
						QStringList pos_buf = buf.split(" ");
						temp.p.x= pos_buf[0].toDouble();
						temp.p.y= pos_buf[1].toDouble();
						temp.p.z= pos_buf[2].toDouble();

						QFile file(reader.attributes().value("Points").toString());

						qDebug()<<file.fileName();
						qDebug()<<file.exists();
						if (!file.open(QFile::ReadOnly | QFile::Text))
						{
							qDebug()<<"open Error";
						}
						QTextStream point_in(&file);
						QString bufLine;
						while(1)
						{
							bufLine = point_in.readLine();
							if(bufLine.isNull())
								break;
							QStringList temp_list = bufLine.split(" ");
							point temp_p;
							temp_p.x = temp_list.at(0).toDouble();
							temp_p.y = temp_list.at(1).toDouble();
							temp_p.z = temp_list.at(2).toDouble();
							temp_p.u = temp_list.at(3).toDouble();
							temp_p.v = temp_list.at(4).toDouble();
							temp_p.w = temp_list.at(5).toDouble();
							temp.points.push_back(temp_p);
						}
						qDebug()<<temp.points.size();
					}

					if (type == QString("Circle"))
					{
						QString buf;
						buf = reader.attributes().value("Vector").toString();
						QStringList vec_buf = buf.split(" ");
						temp.v.u= vec_buf[0].toDouble();
						temp.v.v= vec_buf[1].toDouble();
						temp.v.w= vec_buf[2].toDouble();
						buf = reader.attributes().value("Position").toString();
						QStringList pos_buf = buf.split(" ");
						temp.p.x= pos_buf[0].toDouble();
						temp.p.y= pos_buf[1].toDouble();
						temp.p.z= pos_buf[2].toDouble();

						temp.length = reader.attributes().value("Length").toString().toDouble();
						if (reader.attributes().value("InverseOrientation").toString() == QString("true"))
						{
							temp.direction = 1; //mean outside circle
						}
						else
						{
							temp.direction = -1;  //mean inside circle
						}
						temp.radius = reader.attributes().value("Radius").toString().toDouble();
						QFile file(reader.attributes().value("Points").toString());

						qDebug()<<file.fileName();
						qDebug()<<file.exists();
						if (!file.open(QFile::ReadOnly | QFile::Text))
						{
							qDebug()<<"open Error";
						}
						QTextStream point_in(&file);
						QString bufLine;
						while(1)
						{
							bufLine = point_in.readLine();
							if(bufLine.isNull())
								break;
							QStringList temp_list = bufLine.split(" ");
							point temp_p;
							temp_p.x = temp_list.at(0).toDouble();
							temp_p.y = temp_list.at(1).toDouble();
							temp_p.z = temp_list.at(2).toDouble();
							temp_p.u = temp_list.at(3).toDouble();
							temp_p.v = temp_list.at(4).toDouble();
							temp_p.w = temp_list.at(5).toDouble();
							temp.points.push_back(temp_p);
						}
						qDebug()<<temp.points.size();
					}

					if (type == QString("Cylinder"))
					{
						QString buf;
						buf = reader.attributes().value("Vector").toString();
						QStringList vec_buf = buf.split(" ");
						temp.v.u= vec_buf[0].toDouble();
						temp.v.v= vec_buf[1].toDouble();
						temp.v.w= vec_buf[2].toDouble();
						buf = reader.attributes().value("Position").toString();
						QStringList pos_buf = buf.split(" ");
						temp.p.x= pos_buf[0].toDouble();
						temp.p.y= pos_buf[1].toDouble();
						temp.p.z= pos_buf[2].toDouble();

						temp.height = reader.attributes().value("Height").toString().toDouble();
						if (reader.attributes().value("InverseOrientation").toString() == QString("true"))
						{
							temp.direction = 1; //mean outside circle
						}
						else
						{
							temp.direction = -1;  //mean inside circle
						}
						temp.radius = reader.attributes().value("Radius").toString().toDouble();
						QFile file(reader.attributes().value("Points").toString());

						qDebug()<<file.fileName();
						qDebug()<<file.exists();
						if (!file.open(QFile::ReadOnly | QFile::Text))
						{
							qDebug()<<"open Error";
						}
						QTextStream point_in(&file);
						QString bufLine;
						while(1)
						{
							bufLine = point_in.readLine();
							if(bufLine.isNull())
								break;
							QStringList temp_list = bufLine.split(" ");
							point temp_p;
							temp_p.x = temp_list.at(0).toDouble();
							temp_p.y = temp_list.at(1).toDouble();
							temp_p.z = temp_list.at(2).toDouble();
							temp_p.u = temp_list.at(3).toDouble();
							temp_p.v = temp_list.at(4).toDouble();
							temp_p.w = temp_list.at(5).toDouble();
							temp.points.push_back(temp_p);
						}
						qDebug()<<temp.points.size();
					}

					if (type == QString("Cone"))
					{
						QString buf;
						buf = reader.attributes().value("Vector").toString();
						QStringList vec_buf = buf.split(" ");
						temp.v.u= vec_buf[0].toDouble();
						temp.v.v= vec_buf[1].toDouble();
						temp.v.w= vec_buf[2].toDouble();
						buf = reader.attributes().value("Position").toString();
						QStringList pos_buf = buf.split(" ");
						temp.p.x= pos_buf[0].toDouble();
						temp.p.y= pos_buf[1].toDouble();
						temp.p.z= pos_buf[2].toDouble();

						temp.height = reader.attributes().value("Height").toString().toDouble();
						if (reader.attributes().value("InverseOrientation").toString() == QString("true"))
						{
							temp.direction = 1; //mean outside circle
						}
						else
						{
							temp.direction = -1;  //mean inside circle
						}
						temp.radius = reader.attributes().value("Radius").toString().toDouble();
						QFile file(reader.attributes().value("Points").toString());

						qDebug()<<file.fileName();
						qDebug()<<file.exists();
						if (!file.open(QFile::ReadOnly | QFile::Text))
						{
							qDebug()<<"open Error";
						}
						QTextStream point_in(&file);
						QString bufLine;
						while(1)
						{
							bufLine = point_in.readLine();
							if(bufLine.isNull())
								break;
							QStringList temp_list = bufLine.split(" ");
							point temp_p;
							temp_p.x = temp_list.at(0).toDouble();
							temp_p.y = temp_list.at(1).toDouble();
							temp_p.z = temp_list.at(2).toDouble();
							temp_p.u = temp_list.at(3).toDouble();
							temp_p.v = temp_list.at(4).toDouble();
							temp_p.w = temp_list.at(5).toDouble();
							temp.points.push_back(temp_p);
						}
						qDebug()<<temp.points.size();
					}

					if (type == QString("Plane"))
					{
						QString buf;
						buf = reader.attributes().value("Vector").toString();
						QStringList vec_buf = buf.split(" ");
						temp.v.u= vec_buf[0].toDouble();
						temp.v.v= vec_buf[1].toDouble();
						temp.v.w= vec_buf[2].toDouble();
						buf = reader.attributes().value("Position").toString();
						QStringList pos_buf = buf.split(" ");
						temp.p.x= pos_buf[0].toDouble();
						temp.p.y= pos_buf[1].toDouble();
						temp.p.z= pos_buf[2].toDouble();

						temp.length = reader.attributes().value("Length").toString().toDouble();
						temp.width =  reader.attributes().value("Width").toString().toDouble();
						QFile file(reader.attributes().value("Points").toString());

						qDebug()<<file.fileName();
						qDebug()<<file.exists();
						if (!file.open(QFile::ReadOnly | QFile::Text))
						{
							qDebug()<<"open Error";
						}
						QTextStream point_in(&file);
						QString bufLine;
						while(1)
						{
							bufLine = point_in.readLine();
							if(bufLine.isNull())
								break;
							QStringList temp_list = bufLine.split(" ");
							point temp_p;
							temp_p.x = temp_list.at(0).toDouble();
							temp_p.y = temp_list.at(1).toDouble();
							temp_p.z = temp_list.at(2).toDouble();
							temp_p.u = temp_list.at(3).toDouble();
							temp_p.v = temp_list.at(4).toDouble();
							temp_p.w = temp_list.at(5).toDouble();
							temp.points.push_back(temp_p);
						}
						qDebug()<<temp.points.size();
					}


					if (type == QString("curve"))
					{
						{
							QFile actfile(reader.attributes().value("ActPoints").toString());

							qDebug()<<actfile.fileName();
							qDebug()<<actfile.exists();
							if (!actfile.open(QFile::ReadOnly | QFile::Text))
							{
								qDebug()<<"open act file Error";
							}
							QTextStream actpoint_in(&actfile);
							QString bufLine;
							while(1)
							{
								bufLine = actpoint_in.readLine();
								if(bufLine.isNull())
									break;
								QStringList temp_list = bufLine.split(" ");
								point temp_p;
								temp_p.x = temp_list.at(1).toDouble();
								temp_p.y = temp_list.at(2).toDouble();
								temp_p.z = temp_list.at(3).toDouble();
								temp_p.u = temp_list.at(4).toDouble();
								temp_p.v = temp_list.at(5).toDouble();
								temp_p.w = temp_list.at(6).toDouble();
								temp_p.radius = temp_list.at(8).toDouble();
								temp.act_points.push_back(temp_p);
							}
						}
						{
							QFile nomfile(reader.attributes().value("NomPoints").toString());

							qDebug()<<nomfile.fileName();
							qDebug()<<nomfile.exists();
							if (!nomfile.open(QFile::ReadOnly | QFile::Text))
							{
								qDebug()<<"open nom file Error";
							}
							QTextStream nompoint_in(&nomfile);
							QString bufLine;
							while(1)
							{
								bufLine = nompoint_in.readLine();
								if(bufLine.isNull())
									break;
								QStringList temp_list = bufLine.split(" ");
								point temp_p;
								temp_p.x = temp_list.at(1).toDouble();
								temp_p.y = temp_list.at(2).toDouble();
								temp_p.z = temp_list.at(3).toDouble();
								temp_p.u = temp_list.at(4).toDouble();
								temp_p.v = temp_list.at(5).toDouble();
								temp_p.w = temp_list.at(6).toDouble();
								temp_p.ut = temp_list.at(8).toDouble();
								temp_p.lt = temp_list.at(9).toDouble();
								temp.nom_points.push_back(temp_p);
							}
						}
						{
							QFile measfile(reader.attributes().value("MeasPoints").toString());

							qDebug()<<measfile.fileName();
							qDebug()<<measfile.exists();
							if (!measfile.open(QFile::ReadOnly | QFile::Text))
							{
								qDebug()<<"open meas file Error";
							}
							QTextStream measpoint_in(&measfile);
							QString bufLine;
							while(1)
							{
								bufLine = measpoint_in.readLine();
								if(bufLine.isNull())
									break;
								QStringList temp_list = bufLine.split(" ");
								point temp_p;
								temp_p.x = temp_list.at(1).toDouble();
								temp_p.y = temp_list.at(2).toDouble();
								temp_p.z = temp_list.at(3).toDouble();
								temp_p.u = temp_list.at(4).toDouble();
								temp_p.v = temp_list.at(5).toDouble();
								temp_p.w = temp_list.at(6).toDouble();
								temp_p.radius = temp_list.at(8).toDouble();
								temp.mea_points.push_back(temp_p);
							}
						}
						{
							//get the curve parameters, max & min dev, index of the point number.
							QFile file(reader.attributes().value("CurveParam").toString());
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
									if(reader.name()== "maxDev")
									{
										temp.curve_paras.insert("maxDev",reader.readElementText());
									}
									if(reader.name()== "indexOfMaxDev")
									{
										temp.curve_paras.insert("indexOfMaxDev",reader.readElementText());
									}
									if(reader.name()== "minDev")
									{
										temp.curve_paras.insert("minDev",reader.readElementText());
									}
									if(reader.name()== "indexOfMinDev")
									{
										temp.curve_paras.insert("indexOfMinDev",reader.readElementText());
									}
									if(reader.name()== "isProjected")
									{
										temp.curve_paras.insert("isProjected",reader.readElementText());
									}
									if(reader.name()== "probeCorrection")
									{
										temp.curve_paras.insert("probeCorrection",reader.readElementText());
									}
								}
								reader.readNext();
							}


							//temp.act_file = reader.attributes().value("ActPoints").toString();
							//temp.nom_file = reader.attributes().value("NomPoints").toString();
							//temp.mea_file = reader.attributes().value("MeaPoints").toString();
						}
					}

					names.push_back(temp);
					qDebug()<<names.last().Identifier;
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
