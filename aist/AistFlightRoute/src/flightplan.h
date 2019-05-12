#ifndef FLIGHTPLAN_H
#define FLIGHTPLAN_H
#include "serializable.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QFile>
#include <QVector>
#include "mission.h"
#include "geofence.h"
#include "rallypoint.h"


class FlightPlan : public Serializable
{
public:
    FlightPlan();
    ~FlightPlan();


    virtual void loadFromJson(QJsonObject& json) override;
    virtual QJsonObject toJson() override;

    QString fileType;
    GeoFence geoFence;
    QString groundStation;
    Mission mission;
    double version;
    RallyPoint rallyPoints;
    void ExportKML();
};

#endif // FLIGHTPLAN_H
