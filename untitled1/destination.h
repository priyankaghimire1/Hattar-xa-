#ifndef DESTINATION_H
#define DESTINATION_H
#include <QWidget>
#include <QtSql>
#include <QMainWindow>
#include<QtDebug>
#include<QFileInfo>
#include <QMessageBox>
#include <QCoreApplication>

namespace Ui {
class destination;
}
class destination : public QMainWindow
{
    Q_OBJECT

public:
    explicit destination(QWidget *parent = nullptr);
    ~destination();
private slots:
    //void on_saveButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::destination *ui;
    QSqlDatabase db;
    QString currentPhoneNumber;  // Store the current user's phone number

public:
    void setCurrentPhoneNumber(const QString &phoneNumber);  // Method to set the current user's phone number
};


#endif // DESTINATION_H
