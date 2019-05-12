#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "serializable.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QFile>

#include <iostream>
#include <string> 

using namespace std;

class Item : public Serializable
{
public:
	Item();
	~Item();

    bool autoContinue;
    int command ;
    int doJumpId;
    int frame;
    double params[7] = {0.};
    QString type;

    void setLongitude(double longitude);
    void setLatitude(double longitude);
    void setAltitude(double longitude);
    double getLongitude();
    double getLatitude();
    double getAltitude();

    virtual void loadFromJson(QJsonObject& json) override;
    virtual QJsonObject toJson() override;
};



#endif // ITEM_H
