#ifndef OBJECT_H
#define OBJECT_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QDateTime>

class object
{
public:
    object(const QString& name, double x, double y, const QString& type,double time);

    QString name() const;
    double x() const;
    double y() const;
    QString type() const;
    double time() const;
    QDateTime createDate() const;
    QString getFormattedTime() const;
    double distance() const;

private:
    QString m_name;
    double m_x,m_y;
    QString m_type;
    double m_time;
};

#endif // OBJECT_H
