/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *readButton;
    QLabel *groupLabel;
    QPushButton *distanceButton;
    QPushButton *timeButton;
    QPushButton *nameButton;
    QPushButton *typeButton;
    QPushButton *openButton;
    QPushButton *reloadButton;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(914, 627);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 70, 561, 531));
        readButton = new QPushButton(centralwidget);
        readButton->setObjectName("readButton");
        readButton->setGeometry(QRect(110, 20, 121, 24));
        groupLabel = new QLabel(centralwidget);
        groupLabel->setObjectName("groupLabel");
        groupLabel->setGeometry(QRect(690, 70, 81, 41));
        distanceButton = new QPushButton(centralwidget);
        distanceButton->setObjectName("distanceButton");
        distanceButton->setGeometry(QRect(590, 130, 111, 31));
        timeButton = new QPushButton(centralwidget);
        timeButton->setObjectName("timeButton");
        timeButton->setGeometry(QRect(750, 130, 111, 31));
        nameButton = new QPushButton(centralwidget);
        nameButton->setObjectName("nameButton");
        nameButton->setGeometry(QRect(590, 170, 111, 31));
        typeButton = new QPushButton(centralwidget);
        typeButton->setObjectName("typeButton");
        typeButton->setGeometry(QRect(750, 170, 111, 31));
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName("openButton");
        openButton->setGeometry(QRect(240, 20, 121, 24));
        reloadButton = new QPushButton(centralwidget);
        reloadButton->setObjectName("reloadButton");
        reloadButton->setGeometry(QRect(380, 20, 80, 24));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ViewRefresh));
        reloadButton->setIcon(icon);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 20, 91, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 914, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\204\320\260\320\271\320\273", nullptr));
        readButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        groupLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\270\321\200\320\276\320\262\320\272\320\270", nullptr));
        distanceButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\321\216", nullptr));
        timeButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
        nameButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276 \320\270\320\274\320\265\320\275\320\270", nullptr));
        typeButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276 \321\202\320\270\320\277\321\203", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        reloadButton->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
