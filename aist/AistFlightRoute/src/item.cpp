#include "Item.h"


#define FP_JSON_AUTO_COMTINUE "autoContinue"
#define FP_JSON_COMMAND "command"
#define FP_JSON_DO_JUMP_ID "doJumpId"
#define FP_JSON_FRAME "frame"
#define FP_JSON_TYPE "type"
#define FP_JSON_PARAMS "params"



Item::Item()
{
    autoContinue = false;
    command = 0;
    doJumpId = 0;
    frame = 0;
    type = "SimpleItem";
}

Item::~Item()
{

}

void Item::setLongitude(double p)
{
    params[4] = p;
}

void Item::setLatitude(double p)
{
    params[5] = p;
}

void Item::setAltitude(double p)
{
    params[6] = p;
}

double Item::getLongitude()
{
    return params[4];
}

double Item::getLatitude()
{
    return params[5];
}

double Item::getAltitude()
{
    return params[6];
}

void Item::loadFromJson(QJsonObject &json)
{
    if(json.empty())
    {
        return;
    }

    QJsonValue tmp;
    QJsonArray arr;

    tmp = json.value(FP_JSON_AUTO_COMTINUE);
    if(tmp != QJsonValue::Undefined)
    {
        autoContinue = tmp.toBool();
    }

    tmp = json.value(FP_JSON_COMMAND);
    if(tmp != QJsonValue::Undefined)
    {
        command = tmp.toInt();
    }

    tmp = json.value(FP_JSON_DO_JUMP_ID);
    if(tmp != QJsonValue::Undefined)
    {
        doJumpId = tmp.toInt();
    }

    tmp = json.value(FP_JSON_FRAME);
    if(tmp != QJsonValue::Undefined)
    {
        frame = tmp.toInt();
    }

    tmp = json.value(FP_JSON_TYPE);
    if(tmp != QJsonValue::Undefined)
    {
        type = static_cast<QString>(tmp.toString());
    }

    arr = json.value(FP_JSON_PARAMS).toArray();
    for(int i(0); i < arr.count(); i++)
    {
        params[i] = arr[i].toDouble();
    }
}

QJsonObject Item::toJson()
{

      QJsonObject json;
      json[FP_JSON_AUTO_COMTINUE] = autoContinue;
      json[FP_JSON_COMMAND] = command;
      json[FP_JSON_DO_JUMP_ID] = doJumpId;
      json[FP_JSON_FRAME] = frame;
      json[FP_JSON_TYPE] = type;


      QJsonArray json_array;
      for(auto &it : params)
      {
          json_array.append(it);
      }
      json.insert(FP_JSON_PARAMS, json_array);

      return json;
}

