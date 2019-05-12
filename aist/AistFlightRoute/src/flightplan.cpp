#include "flightplan.h"
#include <QDebug>

#define FP_JSON_FILETYPE "fileType"
#define FP_JSON_GROUNDSTATION "groundStation"
#define FP_JSON_GEOFENCE "geoFence"
#define FP_JSON_MISSION "mission"
#define FP_JSON_RALLYPOINTS "rallyPoints"
#define FP_JSON_VERSION "version"

using namespace std;

FlightPlan::FlightPlan()
{
    fileType = "Plan";
    groundStation = "QGroundControl";
    version=1;
}

FlightPlan::~FlightPlan()
{

}

void FlightPlan::ExportKML()
{
    QString file_path = QFileDialog::getSaveFileName(0, "Выгрузить конфигурацию полёта", "", "*.kml");

    QFile file(file_path);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);

    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("kml");

    xmlWriter.writeStartElement("Document");

    xmlWriter.writeStartElement("name");
     xmlWriter.writeCharacters("KMLDocument");
    xmlWriter.writeEndElement();


    int tempIndex = 0;
    for(Item pointRaw : this->mission.items)
    {
        xmlWriter.writeStartElement("Placemark");
           xmlWriter.writeStartElement("name");
           xmlWriter.writeCharacters(QString::number(tempIndex+1));
           xmlWriter.writeEndElement();

           xmlWriter.writeStartElement("description");
           if (tempIndex == 0){

               xmlWriter.writeCharacters("HomePoint");

           } else {

               xmlWriter.writeCharacters("MiddlePoint");
           }

           xmlWriter.writeEndElement();

           xmlWriter.writeStartElement("Point");
               xmlWriter.writeStartElement("altitudeMode");

               xmlWriter.writeCharacters("relativeToGround");
               xmlWriter.writeEndElement();

               xmlWriter.writeStartElement("coordinates");
                xmlWriter.writeCharacters(QString::number(pointRaw.params[4]) + "," +
                                          QString::number(pointRaw.params[5]) + "," +
                                          QString::number(pointRaw.params[6]));
               xmlWriter.writeEndElement();
           xmlWriter.writeEndElement();
          xmlWriter.writeEndElement();

        tempIndex++;
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
 xmlWriter.writeEndElement();

}

void FlightPlan::loadFromJson(QJsonObject &json)
{
    if(json.empty())
    {
        return;
    }

    QJsonValue tmp;

    tmp = json.value(FP_JSON_FILETYPE);
    if(tmp != QJsonValue::Undefined)
    {
        fileType = static_cast<QString>(tmp.toString());
    }

    tmp = json.value(FP_JSON_GEOFENCE);
    if(tmp != QJsonValue::Undefined)
    {
        QJsonObject o = tmp.toObject();
        geoFence.loadFromJson(o);
    }


    tmp = json.value(FP_JSON_GROUNDSTATION);
    if(tmp != QJsonValue::Undefined)
    {
        groundStation = static_cast<QString>(tmp.toString());
    }

    tmp = json.value(FP_JSON_MISSION);
    if(tmp != QJsonValue::Undefined)
    {
        QJsonObject o = tmp.toObject();
        mission.loadFromJson(o);
    }

    tmp = json.value(FP_JSON_RALLYPOINTS);
    if(tmp != QJsonValue::Undefined)
    {
        QJsonObject o = tmp.toObject();
        rallyPoints.loadFromJson(o);
    }
    tmp = json.value(FP_JSON_VERSION);
    if(tmp != QJsonValue::Undefined)
    {
         version = tmp.toDouble();
    }

}

QJsonObject FlightPlan::toJson()
{
      QJsonObject json;
      json[FP_JSON_FILETYPE] = fileType;
      json[FP_JSON_GEOFENCE] = geoFence.toJson();
      json[FP_JSON_GROUNDSTATION] = groundStation;
      json[FP_JSON_MISSION] = mission.toJson();
      json[FP_JSON_RALLYPOINTS] = rallyPoints.toJson();
      json[FP_JSON_VERSION] = version;
      return json;
}
