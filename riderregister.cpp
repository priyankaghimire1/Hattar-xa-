#include "riderregister.h"
#include "ui_riderregister.h"

riderregister::riderregister(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::riderregister)
{
    ui->setupUi(this);
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Priyanka/Coding/qt/qt/database/databaserider.db");
    if(!db.open ())
        ui->label->setText ("Failed to open the database");
    else
        ui->label->setText("Connected .... ");
}


riderregister::~riderregister()
{
    delete ui;
}

void riderregister::on_pushButton_clicked()
{
    QString Phonenumber, Pin;
    Phonenumber = ui->lineEdit_Phonenumber->text();
    Pin = ui->lineEdit_Pin->text();

    // Ensure the database is open
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Priyanka/Coding/qt/qt/database/databaserider.db");
    if (!db.isOpen()) {
        if (!db.open()) {
            QMessageBox::critical(this, "Error", "Failed to connect to the database.");
            return;
        }
    }

    // Prepare the query
    QSqlQuery query;
    query.prepare("INSERT INTO  rider(phonenumber, pin) VALUES (:phonenumber, :pin)");
    query.bindValue(":phonenumber", Phonenumber);
    query.bindValue(":pin", Pin);

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to insert data into the database.");
        qDebug() << "Error inserting data: " << query.lastError();
    } else {
        QMessageBox::information(this, "Success", "Data inserted successfully rider");
    }


}


