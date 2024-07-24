#include "destination.h"
#include "ui_destination.h"

destination::destination(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::destination)
{
    ui->setupUi(this);
}

destination::~destination()
{
    delete ui;
}
void destination::setCurrentPhoneNumber(const QString &phoneNumber) {
    currentPhoneNumber = phoneNumber;
}
void destination::on_pushButton_clicked()
{
        QString fromLocation = ui->lineEdit_From->text();
        QString toLocation = ui->lineEdit_To->text();

        // Ensure the database is open
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/sqlite/db.sqlite");
        if (!db.isOpen()) {
            if (!db.open()) {
                QMessageBox::critical(this, "Error", "Failed to connect to the database.");
                return;
            }
        }

        // Prepare the query to update the user's record
        QSqlQuery query;
        query.prepare("UPDATE user SET location_from = :fromLocation, location_to = :toLocation WHERE phonenumber = :phonenumber");
        query.bindValue(":fromLocation", fromLocation);
        query.bindValue(":toLocation", toLocation);
        query.bindValue(":phonenumber", currentPhoneNumber);

        // Execute the query
        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update the database.");
            qDebug() << "Error executing query: " << query.lastError();
            return;
        }

        QMessageBox::information(this, "Success", "Locations saved successfully.");
    }



    void destination::on_pushButton_2_clicked()
    {
    QCoreApplication::quit();
    }

