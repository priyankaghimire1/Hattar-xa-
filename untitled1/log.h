#ifndef LOG_H
#define LOG_H

#include <QDialog>
#include <QMainWindow>
#include<QtSql>
#include<QtDebug>
#include<QFileInfo>
#include <QMessageBox>
#include <QCoreApplication>

namespace Ui {
class log;
}

class log : public QDialog
{
    Q_OBJECT

public:
    explicit log(QWidget *parent = nullptr);
    ~log();

private slots:
    void on_pushButton_clicked();

private:
    Ui::log *ui;
QSqlDatabase db;
};

#endif // LOG_H
