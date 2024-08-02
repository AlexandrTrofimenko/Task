#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <object.h>
#include <QVector>
#include <objectmanager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void appendGroupInfo(const QVector<object>& group,const QString& groupName,QString& info);
    ~MainWindow();

private slots:
    void on_readButton_clicked();

    void on_distanceButton_clicked();

    void on_nameButton_clicked();

    void on_timeButton_clicked();

    void on_typeButton_clicked();

    void on_openButton_clicked();

    void on_reloadButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ObjectManager objectManager;
    QString filePath;

};
#endif // MAINWINDOW_H
