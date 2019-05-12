#include "geofence.h"
#define GEOFENCE_JSON_VERSION "version"
#define GEOFENCE_JSON_POLYGONS "polygons"
GeoFence::GeoFence()
{
    version = 1;
}

GeoFence::~GeoFence()
{

}

void GeoFence::loadFromJson(QJsonObject& json)
{
    if(json.empty())
    {
        return;
    }

    QJsonValue tmp;

    tmp = json[GEOFENCE_JSON_VERSION];
    if(tmp != QJsonValue::Undefined)
    {
        version = static_cast<double>(tmp.toDouble());
    }
}
QJsonObject GeoFence::toJson()
{
    QJsonObject json;
    QJsonArray json_array_global;

    for(auto &it : polygons)
    {
       QJsonArray json_array_local;
        for(auto &j : it)
        {
           json_array_local.append(j);
        }
        json_array_global.append(json_array_local);
    }
    json.insert(GEOFENCE_JSON_POLYGONS, json_array_global);
    json[GEOFENCE_JSON_VERSION] = version;
    return json;
}
