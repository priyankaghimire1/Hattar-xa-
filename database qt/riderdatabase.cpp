#include "riderdatabase.h"

RiderDatabase::RiderDatabase(QObject *parent) : QObject(parent)
{

}

void RiderDatabase::connectToRiderDataBase()
{
    if(!QFile("D:/Priyanka/Coding/qt/untitled3/database/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool RiderDatabase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "riderDatabase");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("D:/Priyanka/Coding/qt/untitled3/database/" DATABASE_NAME);
    if(db.open()){
        return true;
    }
    else {
        return false;
    }
}

bool RiderDatabase::restoreDataBase()
{
    if(this->openDataBase()){
        return (this->createTable()) ? true : false;
    } else {
        return false;
    }
    return false;
}

bool RiderDatabase::createTable()
{
    QSqlQuery query(QSqlDatabase::database("riderDatabase.db"));

    if(!query.exec( "CREATE TABLE " TABLE1 " ("
                    "riderid INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_PHONENUM     " VARCHAR(255)    NOT NULL,"
                    TABLE_PIN     " INT    NOT NULL,"
                    TABLE_STATUS     " VARCHAR(255)    NOT NULL,"
                    TABLE_FROM     " VARCHAR(255)    NOT NULL,"
                    TABLE_TO     " VARCHAR(255)    NOT NULL,"
                    " )"
                    )){
        return false;
    } else {
        return true;
    }
    closeDataBase();
    return false;
}

void RiderDatabase::closeDataBase()
{
    db.close();
}

bool RiderDatabase::insertIntoTable(const QVariantList &data)
{
    QSqlQuery query(QSqlDatabase::database("riderDatabase.db"));
    query.prepare("INSERT INTO " TABLE1 " ( " TABLE_PHONENUM", "
                  TABLE_PIN ", "
                    TABLE_STATUS","
                    TABLE_FROM", "
                    TABLE_TO" ) "
                  "VALUES (:Number, :Pin, :Status, :From, :To)");

    query.bindValue(":Number",       data[0].toString());
    query.bindValue(":Pin",       data[1].toString());
    query.bindValue(":Status",       data[2].toString());
    query.bindValue(":From",       data[3].toString());
    query.bindValue(":To",       data[4].toString());
     if(!query.exec()){
        return false;
    } else {
        return true;
    }
    return false;
}

bool RiderDatabase::insertIntoTable(const QString &phonenum, const QString &pin, const QString &status, const QString &from, const QString &to){
    QVariantList data;


    data.append(phonenum);
    data.append(pin);
    data.append (status);
    data.append (from);
    data.append (to);

    if(insertIntoTable(data))
        return true;
    else
        return false;
}
