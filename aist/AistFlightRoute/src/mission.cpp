#include "mission.h"
#define FP_JSON_CRUISESPEED "cruiseSpeed"
#define FP_JSON_FIRMWARETYPE "firmwareType"
#define FP_JSON_HOVERSPEED "hoverSpeed"
#define FP_JSON_PLANHOMEPOS "plannedHomePosition"
#define FP_JSON_VEHICLETYPE "vehicleType"
#define FP_JSON_VERSION "version"
#define FP_JSON_ITEMS "items"


Mission::Mission()
{
    version = 1.0;
    cruiseSpeed= 0;
    firmwareType = 0;
    hoverSpeed = 0;
    vehicleType = 0;
    plannedHomePosition.resize(3);
    for(uint i = 0 ; i < plannedHomePosition.size();i++)
    {
        plannedHomePosition[i] = 0;
    }
}

Mission::~Mission()
{

}

void Mission::loadFromJson(QJsonObject& json)
{
    if(json.empty())
    {
        return;
    }

    QJsonValue tmp;
    QJsonArray arr;

    tmp = json.value(FP_JSON_CRUISESPEED);
    if(tmp != QJsonValue::Undefined)
    {
        cruiseSpeed = static_cast<double>(tmp.toDouble());
    }

    tmp = json.value(FP_JSON_FIRMWARETYPE);
    if(tmp != QJsonValue::Undefined)
    {
        firmwareType = static_cast<double>(tmp.toDouble());
    }

    arr = json.value(FP_JSON_ITEMS).toArray();
    for(int i(0); i < arr.count(); i++)
    {
        Item item;
        QJsonObject o = arr[i].toObject();
        item.loadFromJson(o);
        items.push_back(item);
    }

    tmp = json.value(FP_JSON_HOVERSPEED);
    if(tmp != QJsonValue::Undefined)
    {
        hoverSpeed = static_cast<double>(tmp.toDouble());
    }

    tmp = json.value(FP_JSON_VEHICLETYPE);
    if(tmp != QJsonValue::Undefined)
    {
        vehicleType = static_cast<double>(tmp.toDouble());
    }

    tmp = json.value(FP_JSON_VERSION);
    if(tmp != QJsonValue::Undefined)
    {
        version = static_cast<double>(tmp.toDouble());
    }

    QJsonArray arrp;
    arrp = json.value(FP_JSON_PLANHOMEPOS).toArray();
    for(int i(0); i < arrp.count(); i++)
    {
        plannedHomePosition[i] = arrp[i].toDouble();
    }
}

QJsonObject Mission::toJson()
{
    QJsonObject json;
    json[FP_JSON_CRUISESPEED] = cruiseSpeed;
    json[FP_JSON_FIRMWARETYPE] = firmwareType;
    json[FP_JSON_HOVERSPEED] = hoverSpeed;
    json[FP_JSON_VEHICLETYPE] = vehicleType;
    json[FP_JSON_VERSION] = version;
    QJsonArray json_array_items;
    for(auto &it : items)
    {
        json_array_items.append(it.toJson());
    }
    json.insert(FP_JSON_ITEMS, json_array_items);


    QJsonArray json_array_planHomePos;
    for(auto &it : plannedHomePosition)
    {
        json_array_planHomePos.append(it);
    }
    json.insert(FP_JSON_PLANHOMEPOS, json_array_planHomePos);
    return json;
}
