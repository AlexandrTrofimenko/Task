#include "object.h"
#include <QString>
#include <QTextStream>
#include "ui_mainwindow.h"
#include <mainwindow.h>
#include <cmath>
object::object(const QString& name, double x, double y, const QString& type,double time)
    :m_name(name),m_x(x),m_y(y),m_type(type),m_time(time) {}


QString object::name() const
{
    return m_name;
}

double object::x() const
{
    return m_x;
}

double object::y() const
{
    return m_y;
}

QString object::type() const
{
    return m_type;
}

double object::time() const
{
    return m_time;
}

QDateTime object::createDate() const
{
    return QDateTime::fromSecsSinceEpoch(static_cast<double>(m_time), Qt::UTC);
}


QString object::getFormattedTime() const {
    qint64 seconds = static_cast<qint64>(m_time);
    int milliseconds = static_cast<int>((m_time - seconds) * 1000);

    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(seconds, Qt::UTC);
    dateTime = dateTime.addMSecs(milliseconds);

    return dateTime.toString("dd.MM.yyyy hh:mm:ss.zzz");
}


// Допустим, расстояние считается от (0.0)

double object::distance() const
{
    return pow((m_x*m_x+m_y*m_y),0.5);
}
