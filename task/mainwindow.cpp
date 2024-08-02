#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <object.h>
#include <QVector>
#include <QMessageBox>
#include <QInputDialog>
#include <QCoreApplication>
#include <QApplication>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendGroupInfo(const QVector<object> &group, const QString &groupName, QString &info)
{
    if (!group.isEmpty()) {
        info += QString("\n--- %1 ---\n").arg(groupName);
        for (const auto& obj : group) {
            info += QString("Имя: %1, | X: %2, | Y: %3, | Тип объекта: %4, | Время: %5\n")
                .arg(obj.name())
                .arg(obj.x())
                .arg(obj.y())
                .arg(obj.type())
                .arg(obj.getFormattedTime());
        }
    }
}

void MainWindow::on_readButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, "Выберите файл для загрузки", "", "Text Files (*.txt);;All Files (*)");

       if (filePath.isEmpty()) {
           return;
       }

       objectManager.loadFromFile(filePath);
       const QVector<object>& objects = objectManager.getObjects();

       QString fileContent;
       for (const auto& obj : objects) {
           fileContent += QString("%1 %2 %3 %4 %5\n")
              .arg(obj.name())
              .arg(obj.x())
              .arg(obj.y())
              .arg(obj.type())
              .arg(obj.getFormattedTime());
       }
       ui->label->setText(fileContent);
}


void MainWindow::on_distanceButton_clicked()
{
    GroupedObjects grouped = objectManager.groupByDistance();

    QString info;

    appendGroupInfo(grouped.group1, "До 100 ед.",info);
    appendGroupInfo(grouped.group2, "До 1000 ед.",info);
    appendGroupInfo(grouped.group3, "До 10000 ед.",info);
    appendGroupInfo(grouped.farAway, "Слишком далеко",info);

    if (info.isEmpty()) {
        info = "Нет объектов для отображения. Выберите файл";
    }

    QMessageBox::information(this, "Группировка по расстоянию", info);
}


void MainWindow::on_nameButton_clicked()
{
    NamedGroups namedGroups = objectManager.groupByName();
    QString info;

    for (auto it = namedGroups.groups.cbegin(); it != namedGroups.groups.cend(); it++) {
        appendGroupInfo(it.value(), it.key(), info);
    }

    appendGroupInfo(namedGroups.specialGroup, "#", info);

    if (info.isEmpty()) {
        info = "Нет объектов для отображения.";
    }

    QMessageBox::information(this, "Группировка по имени", info);
}


void MainWindow::on_timeButton_clicked()
{
    TimeGroups timeGroups = objectManager.groupByTime();
    QString info;

    appendGroupInfo(timeGroups.today, "Сегодня", info);
    appendGroupInfo(timeGroups.yesterday, "Вчера", info);
    appendGroupInfo(timeGroups.thisWeek, "На этой неделе", info);
    appendGroupInfo(timeGroups.thisMonth, "В этом месяце", info);
    appendGroupInfo(timeGroups.thisYear, "В этом году", info);
    appendGroupInfo(timeGroups.earlier, "Ранее", info);
    appendGroupInfo(timeGroups.notReal, "Ещё не время", info);

    if (info.isEmpty()) {
        info = "Нет объектов для отображения.";
    }

    QMessageBox::information(this, "Группировка по времени создания", info);
}


void MainWindow::on_typeButton_clicked()
{
    bool ok;
    int number = QInputDialog::getInt(this, tr("Введите число"),
                                      tr("Число:"), 1, 0, 10000, 1, &ok);
    if (ok) {
        QMessageBox::information(this, tr("Ввод"), tr("Вы ввели: %1").arg(number));
    } else {
        QMessageBox::information(this, tr("Ввод"), tr("Вы отменили ввод."));
    }
    TypeGroups typeGroups = objectManager.groupByTypes(number);
    QString info;
    for (auto it = typeGroups.groups.cbegin(); it != typeGroups.groups.cend(); it++) {
        appendGroupInfo(it.value(), it.key(), info);
    }

    appendGroupInfo(typeGroups.different,"Разное",info);
    if (info.isEmpty()) {
        info = "Нет объектов для отображения.";
    }

    QMessageBox::information(this, "Группировка по типу создания", info);
}


void MainWindow::on_openButton_clicked()
{
    QString fileName;
    if(!filePath.isEmpty())
        fileName = filePath;
    else
        QFileDialog::getOpenFileName(this, "Выберите файл", "", "Text Files (*.txt)");

    if (!fileName.isEmpty()) {
           QProcess process;
           QString program = "notepad.exe";
           QStringList arguments;
           arguments << fileName;

           if (!process.startDetached(program, arguments)) {
               QMessageBox::information(this,"Ошибка","Файл не был выбран");
               return;
           }
       }
    else {
            QMessageBox::information(this,"Ошибка 1","Файл не был выбран");
    }
}


void MainWindow::on_reloadButton_clicked()
{
    if(!filePath.isEmpty())
    {
        objectManager.loadFromFile(filePath);
        const QVector<object>& objects = objectManager.getObjects();
        QString fileContent;
        for (const auto& obj : objects) {
            fileContent += QString("%1 %2 %3 %4 %5\n")
               .arg(obj.name())
               .arg(obj.x())
               .arg(obj.y())
               .arg(obj.type())
               .arg(obj.getFormattedTime());
        }
        ui->label->setText(fileContent);
    }
    else
        QMessageBox::information(this,"Ошибка","Не выбран файл для открытия");
}


void MainWindow::on_pushButton_clicked()
{
    bool ok;
    QString fileName = QInputDialog::getText(this, "Введите имя файла",
                                             "Имя файла:", QLineEdit::Normal,
                                             "", &ok);
    if (ok && !fileName.isEmpty()) {
        if (!fileName.endsWith(".txt")) {
            fileName += ".txt";
        }

        filePath = QFileDialog::getSaveFileName(this, "Сохранить файл", fileName, "Text Files (*.txt);;All Files (*)");

        if (!filePath.isEmpty()) {
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                file.close();
                QMessageBox::information(this, "Файл создан", "Файл успешно создан: " + filePath);
            }
            else {
                QMessageBox::warning(this, "Ошибка", "Не удалось создать файл.");
            }
        }
        else {
            QMessageBox::information(this, "Отменено", "Создание файла отменено.");
        }
    }
    else {
        QMessageBox::information(this, "Отменено", "Ввод имени файла отменен.");
    }
}

