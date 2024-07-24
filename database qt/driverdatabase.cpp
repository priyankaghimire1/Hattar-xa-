#include "driverdatabase.h"

DriverDatabase::DriverDatabase(QObject *parent) : QObject(parent)
{

}

void DriverDatabase::connectToRiderDataBase()
{
    if(!QFile("D:/Priyanka/Coding/qt/untitled3/database/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool DriverDatabase::openDataBase()
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

bool DriverDatabase::restoreDataBase()
{
    if(this->openDataBase()){
        return (this->createTable()) ? true : false;
    } else {
        return false;
    }
    return false;
}

bool DriverDatabase::createTable()
{
    QSqlQuery query(QSqlDatabase::database("riderDatabase.db"));

    if(!query.exec( "CREATE TABLE " TABLE2 " ("
                    "driverid INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_PHONENUM     " VARCHAR(255)    NOT NULL,"
                    TABLE_PIN     " INT    NOT NULL,"
                    " )"
                    )){
        return false;
    } else {
        return true;
    }
    closeDataBase();
    return false;
}

void DriverDatabase::closeDataBase()
{
    db.close();
}

bool DriverDatabase::insertIntoTable(const QVariantList &data)
{
    QSqlQuery query(QSqlDatabase::database("riderDatabase.db"));
    query.prepare("INSERT INTO " TABLE2 " ( " TABLE_PHONENUM", "
                  TABLE_PIN " ) "
                  "VALUES (:Number, :Pin, :Status, :From, :To)");

    query.bindValue(":Number",       data[0].toString());
    query.bindValue(":Pin",       data[1].toString());

    if(!query.exec()){
        return false;
    } else {
        return true;
    }
    return false;
}

bool DriverDatabase::insertIntoTable(const QString &phonenum, const QString &pin){
    QVariantList data;


    data.append(phonenum);
    data.append(pin);


    if(insertIntoTable(data))
        return true;
    else
        return false;
}
