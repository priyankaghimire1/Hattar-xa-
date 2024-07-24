#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");
    if(!db.open ())
        ui->label->setText ("Failed to open the database");
    else
        ui->label->setText("Connected .... ");
}


Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
        QString Phonenumber, Pin;
        Phonenumber = ui->lineEdit_Phonenumber->text();
        Pin = ui->lineEdit_Pin->text();

        // Ensure the database is open
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/sqlite/db.sqlite");
        if (!db.isOpen()) {
            if (!db.open()) {
                QMessageBox::critical(this, "Error", "Failed to connect to the database.");
                return;
            }
        }

        // Prepare the query
        QSqlQuery query;
        query.prepare("INSERT INTO user (phonenumber, pin) VALUES (:phonenumber, :pin)");
        query.bindValue(":phonenumber", Phonenumber);
        query.bindValue(":pin", Pin);

        // Execute the query
        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to insert data into the database.");
            qDebug() << "Error inserting data: " << query.lastError();
        } else {
            QMessageBox::information(this, "Success", "Data inserted successfully.");
        }
        // void Login::on_pushButton_clicked()
        // {
        //     QString Phonenumber, Pin;
        //     Phonenumber = ui->lineEdit_Phonenumber->text();
        //     Pin = ui->lineEdit_Pin->text();

        //     // Ensure the database is open
        //     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        //     db.setDatabaseName("C:/sqlite/db.sqlite");
        //     if (!db.isOpen()) {
        //         if (!db.open()) {
        //             QMessageBox::critical(this, "Error", "Failed to connect to the database.");
        //             return;
        //         }
        //     }

        //     // Prepare the query
        //     QSqlQuery query2;
        //     query2.prepare("INSERT INTO rider (phonenumber, pin) VALUES (:phonenumber, :pin)");
        //     query2.bindValue(":phonenumber", Phonenumber);
        //     query2.bindValue(":pin", Pin);

        //     // Execute the query
        //     if (!query2.exec()) {
        //         QMessageBox::critical(this, "Error", "Failed to insert data into the database.");
        //         qDebug() << "Error inserting data: " << query2.lastError();
        //     } else {
        //         QMessageBox::information(this, "Success", "Data inserted successfully in rider.");
        //     }


}




