#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QVector>
#include "object.h"
#include <QList>
#include <QMap>

struct GroupedObjects
{
    QList<object> group1;
    QList<object> group2;
    QList<object> group3;
    QList<object> farAway;

};

struct NamedGroups {
    QMap<QString, QVector<object>> groups;
    QVector<object> specialGroup;
};

struct TimeGroups {
    QVector<object> today;
    QVector<object> yesterday;
    QVector<object> thisWeek;
    QVector<object> thisMonth;
    QVector<object> thisYear;
    QVector<object> earlier;
    QVector<object> notReal;
};

struct TypeGroups {
    QMap<QString, QVector<object>> groups;
    QVector<object> different;
};

class ObjectManager {
public:

    void loadFromFile(const QString& filePath);
    const QVector<object>& getObjects() const;
    NamedGroups groupByName();
    GroupedObjects groupByDistance();
    TimeGroups groupByTime();
    TypeGroups groupByTypes(int minCount);


private:
    QVector<object> objects;
};

#endif // OBJECTMANAGER_H
