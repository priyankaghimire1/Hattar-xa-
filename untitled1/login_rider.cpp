#include "login_rider.h"
#include "ui_login_rider.h"

login_rider::login_rider(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login_rider)
{
    ui->setupUi(this);
}

login_rider::~login_rider()
{
    delete ui;
}

void login_rider::on_pushButton_clicked()
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

    // Prepare the query to check for a matching record
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM rider WHERE phonenumber = :phonenumber AND pin = :pin");
    query.bindValue(":phonenumber", Phonenumber);
    query.bindValue(":pin", Pin);

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to execute query.");
        qDebug() << "Error executing query: " << query.lastError();
        return;
    }

    // Check the result
    if (query.next() && query.value(0).toInt() > 0) {
        QMessageBox::information(this, "Success", "Login successful.");
        // Proceed to the next step, e.g., open the main window
    } else {
        QMessageBox::warning(this, "Failure", "Invalid phone number or pin.");
    }
}




void login_rider::on_pushButton_2_clicked()
{
      QCoreApplication::quit();
}

