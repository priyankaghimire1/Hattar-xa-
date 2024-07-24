#include "login.h"

#include <QApplication>

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
    QString query="CREATE TABLE user("
        " USERID integer PRIMARY KEY AUTOINCREMENT,"
        "PHONENUMBER integer NOT NUL,"
                    "PIN INTEGER NOT NUL);";

    QSqlQuery qry;
    if(!qry.exec (query))
    {
       qDebug () << "error creating table";
    }
    // QString query2="CREATE TABLE rider("
    //                 " USERID integer PRIMARY KEY AUTOINCREMENT,"
    //                 "PHONENUMBER integer NOT NUL,"
    //                 "PIN INTEGER NOT NUL);";

    // QSqlQuery qry;
    // if(!qry.exec (query2))
    // {
    //     qDebug () << "error creating table";
    // }
    db.close();
    qDebug () << "end";
    Login w;
    w.show();
    return a.exec();
}
