#pragma once
#ifndef RALLYPOINT_H
#define RALLYPOINT_H
#include <iostream>
#include <vector>
#include <string>
#include <QJsonObject>
#include "serializable.h"

using namespace std;

class RallyPoint: public Serializable
{
public:
	RallyPoint();
	~RallyPoint();

    vector <vector<double>> points;
	double version = 1.0;

    void loadFromJson(QJsonObject& json) override;
    QJsonObject toJson() override;
};

#endif // RALLYPOINT_H

