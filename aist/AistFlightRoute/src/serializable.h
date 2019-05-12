#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

class Serializable
{
public:

    virtual void loadFromJson(QJsonObject& json) = 0;
    virtual QJsonObject toJson() = 0;
};

#endif // SERIALIZABLE_H
