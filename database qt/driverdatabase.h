#ifndef DRIVERDATABASE_H
#define DRIVERDATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>

#define DATABASE_HOSTNAME   "NameDataBase"
#define DATABASE_NAME       "riderDatabase.db"

#define TABLE2              "driverInformationTable"
#define TABLE_PHONENUM      "phoneNumber"
#define TABLE_PIN           "pin"

class DriverDatabase : public QObject
{
    Q_OBJECT

public:
    explicit DriverDatabase(QObject *parent = nullptr);
    void connectToRiderDataBase();
private:
    QSqlDatabase    db;
    bool openDataBase();
    bool restoreDataBase();
    bool createTable();
    void closeDataBase();

public slots:
    bool insertIntoTable(const QVariantList &data);
    bool insertIntoTable(const QString &phonenum, const QString &pin);

signals:

};

#endif // DRIVERDATABASE_H
