#ifndef LOGIN_RIDER_H
#define LOGIN_RIDER_H

#include <QMainWindow>
#include<QtSql>
#include<QtDebug>
#include<QFileInfo>
#include <QMessageBox>
#include <QCoreApplication>
namespace Ui {
class login_rider;
}

class login_rider : public QMainWindow
{
    Q_OBJECT

public:
    explicit login_rider(QWidget *parent = nullptr);
    ~login_rider();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::login_rider *ui;
     QSqlDatabase db;
};

#endif // LOGIN_RIDER_H
