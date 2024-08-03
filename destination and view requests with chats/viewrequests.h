#ifndef VIEWREQUESTS_H
#define VIEWREQUESTS_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "chatrider.h"

namespace Ui {
class viewRequests;
}

class viewRequests : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewRequests(QWidget *parent = nullptr);
    ~viewRequests();
    void setCurrentPhoneNumber(const QString &phoneNumber);
    void loadMessages();


private slots:
    void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::viewRequests *ui;
    QSqlDatabase db;
    chatrider *chatriderWindow;
    QString currentPhoneNumber;
};

#endif // VIEWREQUESTS_H
