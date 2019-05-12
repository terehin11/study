#ifndef MISSION_H
#define MISSION_H
#include <QJsonObject>
#include "item.h"
#include <vector>
#include "serializable.h"

using namespace std;


typedef enum
{
    //statuses
    BASE,
    WAYPOINT
} Status;

class Mission : public Serializable
{
public:
    Mission();
    ~Mission();
    vector<Item> items;
    double cruiseSpeed;
    double firmwareType;
    double hoverSpeed;
    vector<double> plannedHomePosition;
    double vehicleType;
    double version;
    void loadFromJson(QJsonObject& json) override;
    QJsonObject toJson() override;
};

#endif // MISSION_H
