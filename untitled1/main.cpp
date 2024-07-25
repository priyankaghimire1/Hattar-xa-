#include "signup.h"
#include "login.h"
#include <QApplication>
#include<QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug () << "start";

    QSqlDatabase db;
    db =QSqlDatabase :: addDatabase ("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");

    if(!db.open ()){

    qDebug() << "problem opening database";
    }
    qDebug() << "end";
    QString query="CREATE TABLE IF NOT EXISTS user("
        " USERID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "PHONENUMBER INTEGER NOT NULL,"
                    "PIN INTEGER NOT NULL,"
"location_from TEXT,"
    "location_to TEXT,"
    "status TEXT DEFAULT 'on hold');";

    QSqlQuery qry;
    if(!qry.exec (query))
    {
       qDebug () << "error creating table";
    }
    db.close();
    qDebug () << "end";
    qDebug () << "start";

    db =QSqlDatabase :: addDatabase ("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");

    if(!db.open ()){

        qDebug() << "problem opening database";
    }
    qDebug() << "end";
    QString query1="CREATE TABLE IF NOT EXISTS rider("
                    " RIDERID INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "PHONENUMBER INTEGER NOT NULL,"
                    "PIN INTEGER NOT NULL);";

    QSqlQuery qry1;
    if(!qry1.exec (query1))
    {
        qDebug () << "error creating table";
    }
    db.close();
    qDebug () << "end";
    Login w;
    w.show();
    return a.exec();
}
