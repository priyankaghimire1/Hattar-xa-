#include "destination.h"
#include "ui_destination.h"

destination::destination(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::destination)
    ,chatWindow(nullptr)
{
    ui->setupUi(this);
}

destination::~destination()
{
    delete ui;
    if (chatWindow) {
        delete chatWindow;
    }
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
    db.setDatabaseName("D:/Priyanka/Coding/qt/qt/database/db.sqlite");
    if (!db.isOpen()) {
        if (!db.open()) {
            QMessageBox::critical(this, "Error", "Failed to connect to the database.");
            return;
        }
    }

    // Prepare the query to update the user's record
    QSqlQuery query;
    query.prepare("UPDATE user SET location_from = :fromLocation, location_to = :toLocation, status = 'on hold' WHERE phonenumber = :phonenumber");
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
    //loadMessages();
}



void destination::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}
void destination::loadMessages()
{
    QSqlQuery query;
    query.prepare("SELECT message FROM messagesRider ORDER BY timestamp DESC LIMIT 1");
    //query.bindValue(":phonenumber", currentPhoneNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to load messages.");
        qDebug() << "Error loading messages: " << query.lastError();
        return;
    }

    while (query.next()) {
        QString message = query.value(0).toString();
        ui->textEdit->append(message);// text edit widget gives this option so to display message use this
    }
}

void destination::on_pushButton_3_clicked()
{
    QString message = ui->lineEdit->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Message cannot be empty.");
        return;
    }

    // Save the message to the database
    QSqlQuery query;
    query.prepare("INSERT INTO messages ( message) VALUES ( :message)");
    //query.bindValue(":phonenumber", currentPhoneNumber);
    query.bindValue(":message", message);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to send the message.");
        qDebug() << "Error sending message: " << query.lastError();
        return;
    }
    QMessageBox::information(this, "Success", "Message saved successfully.");
    loadMessages();
}


