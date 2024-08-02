#include "objectmanager.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <object.h>
#include <QRegularExpression>
#include <QDateTime>


void ObjectManager::loadFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    objects.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(' ');
        if (parts.size() == 5) {
            QString name = parts[0];
            double x = parts[1].toDouble();
            double y = parts[2].toDouble();
            QString type = parts[3];
            long double time = parts[4].toDouble();
            objects.emplace_back(name, x, y, type, time);
        }
    }

    file.close();
}

const QVector<object>& ObjectManager::getObjects() const {
    return objects;
}

NamedGroups ObjectManager::groupByName()
{
    NamedGroups namedGroups;

    for (const auto& obj : objects) {
        QString name = obj.name();
        if (name.isEmpty()) {
            continue;
        }

        QChar firstChar = name[0].toUpper();

        if (!firstChar.isLetter()) {
            namedGroups.specialGroup.push_back(obj);
        } else {
            QString groupName = firstChar;
            namedGroups.groups[groupName].push_back(obj);
        }
    }

    auto nameComparator = [](const object& a, const object& b) {
        return a.name() < b.name();
    };

    for (auto& group : namedGroups.groups) {
        std::sort(group.begin(), group.end(), nameComparator);
    }
    std::sort(namedGroups.specialGroup.begin(), namedGroups.specialGroup.end(), nameComparator);

    return namedGroups;
}


GroupedObjects ObjectManager::groupByDistance()
{
    QList<object> objects = getObjects();

    GroupedObjects groupedObjects;
    for (const auto& obj : objects) {
        double dist = obj.distance();
        if (dist <= 100) {
            groupedObjects.group1.push_back(obj);
        } else if (dist <= 1000) {
            groupedObjects.group2.push_back(obj);
        } else if (dist <= 10000) {
            groupedObjects.group3.push_back(obj);
        } else {
            groupedObjects.farAway.push_back(obj);
        }
    }


    auto distanceComparator = [](const object& a, const object& b) {
          return a.distance() < b.distance();
      };

    std::sort(groupedObjects.group1.begin(), groupedObjects.group1.end(), distanceComparator);
    std::sort(groupedObjects.group2.begin(), groupedObjects.group2.end(), distanceComparator);
    std::sort(groupedObjects.group3.begin(), groupedObjects.group3.end(), distanceComparator);
    std::sort(groupedObjects.farAway.begin(), groupedObjects.farAway.end(), distanceComparator);

    return groupedObjects;

}

TimeGroups ObjectManager::groupByTime()
{
    TimeGroups timeGroups;
    QDateTime now = QDateTime::currentDateTime();

    QDateTime startOfToday = QDateTime(now.date(), QTime(0, 0), Qt::LocalTime);
    QDateTime startOfYesterday = startOfToday.addDays(-1);
    QDateTime startOfThisWeek = QDateTime(now.date().addDays(-now.date().dayOfWeek() + 1), QTime(0, 0), Qt::LocalTime);
    QDateTime startOfThisMonth = QDateTime(QDate(now.date().year(), now.date().month(), 1), QTime(0, 0), Qt::LocalTime);
    QDateTime startOfThisYear = QDateTime(QDate(now.date().year(), 1, 1), QTime(0, 0), Qt::LocalTime);

    for (const auto& obj : objects) {
        QDateTime objDateTime = QDateTime::fromSecsSinceEpoch(static_cast<qint64>(obj.time()), Qt::UTC);
        if(objDateTime.date().year() > startOfToday.date().year()) {
            timeGroups.notReal.push_back(obj);
        }
        else if (objDateTime >= startOfToday && objDateTime.date().year() == startOfToday.date().year()) {
            timeGroups.today.push_back(obj);
        } else if (objDateTime >= startOfYesterday) {
            timeGroups.yesterday.push_back(obj);
        } else if (objDateTime >= startOfThisWeek) {
            timeGroups.thisWeek.push_back(obj);
        } else if (objDateTime >= startOfThisMonth) {
            timeGroups.thisMonth.push_back(obj);
        } else if (objDateTime >= startOfThisYear) {
            timeGroups.thisYear.push_back(obj);
        } else {
            timeGroups.earlier.push_back(obj);
        }
    }

    auto timeComparator = [](const object& a, const object& b) {
        return a.time() < b.time();
    };

    std::sort(timeGroups.today.begin(), timeGroups.today.end(), timeComparator);
    std::sort(timeGroups.yesterday.begin(), timeGroups.yesterday.end(), timeComparator);
    std::sort(timeGroups.thisWeek.begin(), timeGroups.thisWeek.end(), timeComparator);
    std::sort(timeGroups.thisMonth.begin(), timeGroups.thisMonth.end(), timeComparator);
    std::sort(timeGroups.thisYear.begin(), timeGroups.thisYear.end(), timeComparator);
    std::sort(timeGroups.earlier.begin(), timeGroups.earlier.end(), timeComparator);
    std::sort(timeGroups.notReal.begin(), timeGroups.notReal.end(), timeComparator);

    return timeGroups;
}

TypeGroups ObjectManager::groupByTypes(int minCount)
{
    NamedGroups namedGroups;
    TypeGroups typeGroups;
    QMap<QString, QVector<object>> tempGroups;

    for (const auto& obj : objects) {
        QString type = obj.type();
        tempGroups[type].push_back(obj);
    }

    for (auto it = tempGroups.cbegin(); it != tempGroups.cend(); it++) {
        const QString& type = it.key();
        const QVector<object>& objs = it.value();

        if (objs.size() > minCount) {
            typeGroups.groups[type] = objs;
        } else {
            typeGroups.different.append(objs);
        }
    }

    auto nameComparator = [](const object& a, const object& b) {
        return a.name() < b.name();
    };

    for (const auto& obj : objects) {
        QString name = obj.name();
        if (name.isEmpty()) {
            continue;
        }
        QChar firstChar = name[0].toUpper();

        if (!firstChar.isLetter()) {
            namedGroups.specialGroup.push_back(obj);
        } else {
            QString groupName = firstChar;
            namedGroups.groups[groupName].push_back(obj);
        }
    }


    for (auto& group : namedGroups.groups) {
        std::sort(group.begin(), group.end(), nameComparator);
    }

    std::sort(typeGroups.different.begin(), typeGroups.different.end(), nameComparator);
    std::sort(namedGroups.specialGroup.begin(), namedGroups.specialGroup.end(), nameComparator);
    return typeGroups;
}


