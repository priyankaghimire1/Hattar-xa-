#ifndef RIDERDATABASE_H
#define RIDERDATABASE_H

#include <QObject>
//#include <QDebug>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>

#define DATABASE_HOSTNAME   "NameDataBase"
#define DATABASE_NAME       "riderDatabase.db"

#define TABLE1            "riderInformationTable"
#define TABLE_PHONENUM      "phoneNumber"
#define TABLE_PIN           "pin"
#define TABLE_STATUS        "status"
#define TABLE_FROM          "from"
#define TABLE_TO            "to"

class RiderDatabase : public QObject
{
    Q_OBJECT

public:
    explicit RiderDatabase(QObject *parent = nullptr);
    void connectToRiderDataBase();
private:
    QSqlDatabase    db;
    bool openDataBase();
    bool restoreDataBase();
    bool createTable();
    void closeDataBase();

public slots:
    bool insertIntoTable(const QVariantList &data);
    bool insertIntoTable(const QString &phonenum, const QString &pin, const QString &status, const QString &from, const QString &to);

signals:

};

#endif // RIDERDATABASE_H
