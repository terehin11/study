#pragma once
#ifndef GEOFENCE_H
#define GEOFENCE_H

#include <iostream>
#include <vector>
#include <string>
#include <QJsonObject>
#include "serializable.h"

using namespace std;

class GeoFence : public Serializable
{
public:
	GeoFence();
	~GeoFence();

    double version=1;
    vector <vector<double>> polygons;

    void loadFromJson(QJsonObject& json) override;
    QJsonObject toJson() override;

};


#endif // GEOFENCE_H
