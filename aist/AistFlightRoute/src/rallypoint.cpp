#include "rallypoint.h"
#define RALLYPOINT_JSON_VERSION "version"
#define RALLYPOINT_JSON_POINTS "points"
RallyPoint::RallyPoint()
{
    version = 1;
}

RallyPoint::~RallyPoint()
{

}

void RallyPoint::loadFromJson(QJsonObject& json)
{
    if(json.empty())
    {
        return;
    }

    QJsonValue tmp;

    tmp = json[RALLYPOINT_JSON_VERSION];
    if(tmp != QJsonValue::Undefined)
    {
        version = static_cast<double>(tmp.toDouble());
    }
}
QJsonObject RallyPoint::toJson()
{
    QJsonObject json;
    QJsonArray json_array_global;

    for(auto &it : points)
    {
       QJsonArray json_array_local;
        for(auto &j : it)
        {
           json_array_local.append(j);
        }
        json_array_global.append(json_array_local);
    }
    json.insert(RALLYPOINT_JSON_POINTS, json_array_global);
    json[RALLYPOINT_JSON_VERSION] = version;
    return json;
}
