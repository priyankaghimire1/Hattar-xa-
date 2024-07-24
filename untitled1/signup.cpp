#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include <QMessageBox>
#include <QtSql>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login),
    loginWindow(nullptr)
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
    if (loginWindow) {
        delete loginWindow;
    }
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

    // Prepare the query to check for duplicates
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM user WHERE phonenumber = :phonenumber");
    checkQuery.bindValue(":phonenumber", Phonenumber);

    // Execute the query
    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to check for duplicates.");
        qDebug() << "Error checking for duplicates: " << checkQuery.lastError();
        return;
    }

    // Check the result
    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Duplicate", "The phone number already exists.");
        return;
    }

    // Prepare the insertion query
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO user (phonenumber, pin) VALUES (:phonenumber, :pin)");
    insertQuery.bindValue(":phonenumber", Phonenumber);
    insertQuery.bindValue(":pin", Pin);

    // Execute the insertion query
    if (!insertQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to insert data into the database.");
        qDebug() << "Error inserting data: " << insertQuery.lastError();
    } else {
        QMessageBox::information(this, "Success", "Data inserted successfully.");
        QMessageBox::information(this, "Success", "Sign-in successful. Redirecting to login...");

        // Show the login window
        if (!loginWindow) {
            loginWindow = new login(this);
        }
        loginWindow->show();
        this->hide(); // Hide the sign-in window
    }
    }

void Login::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}


void Login::on_pushButton_3_clicked()
{
        QString Phonenumber1, Pin1;
        Phonenumber1 = ui->lineEdit_Phonenumber->text();
        Pin1 = ui->lineEdit_Pin->text();

        // Ensure the database is open
        QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE");
        db1.setDatabaseName("C:/sqlite/db1.sqlite");
        if (!db1.isOpen()) {
            if (!db1.open()) {
                QMessageBox::critical(this, "Error", "Failed to connect to the database.");
                return;
            }
        }

        // Prepare the query to check for duplicates
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM rider WHERE phonenumber = :phonenumber");
        checkQuery.bindValue(":phonenumber", Phonenumber1);

        // Execute the query
        if (!checkQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to check for duplicates.");
            qDebug() << "Error checking for duplicates: " << checkQuery.lastError();
            return;
        }

        // Check the result
        if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(this, "Duplicate", "The phone number already exists.");
            return;
        }

        // Prepare the insertion query
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO user (phonenumber, pin) VALUES (:phonenumber, :pin)");
        insertQuery.bindValue(":phonenumber", Phonenumber1);
        insertQuery.bindValue(":pin", Pin1);

        // Execute the insertion query
        if (!insertQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to insert data into the database.");
            qDebug() << "Error inserting data: " << insertQuery.lastError();
        } else {
            QMessageBox::information(this, "Success", "Data inserted successfully.");
            QMessageBox::information(this, "Success", "Sign-in successful. Redirecting to login...");

            // Show the login window
            if (!loginWindow) {
                loginWindow = new login(this);
            }
            loginWindow->show();
            this->hide(); // Hide the sign-in window
        }
    }


