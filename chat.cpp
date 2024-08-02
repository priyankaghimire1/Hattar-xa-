#include "chat.h"
#include "ui_chat.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
chat::chat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chat)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open the database.");
    }
}

chat::~chat()
{
    delete ui;
}
void chat::setCurrentPhoneNumber(const QString &phoneNumber) {
    currentPhoneNumber = phoneNumber;
   // loadMessages();  // Load messages when the phone number is set
}
//this is to load the message for the rider when the rider clicks a phone number and is also asked to send a
//reply saying ok will be ready and that will be displayed in the user side and i think this much will suffice
void chat::loadMessages()
{
    QSqlQuery query;
    query.prepare("SELECT message FROM messages WHERE phonenumber = :phonenumber ORDER BY timestamp DESC LIMIT 1");
    query.bindValue(":phonenumber", currentPhoneNumber);

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
 //void chat::setCurrentPhoneNumber(const QString &phoneNumber) {
  //  currentPhoneNumber = phoneNumber;
 //}
void chat::on_pushButton_clicked()
{
    QString message = ui->lineEdit->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Message cannot be empty.");
        return;
    }

    // Save the message to the database
    QSqlQuery query;
    //query.prepare("UPDATE messages SET message = :message WHERE phonenumber = :phonenumber");
    query.prepare("INSERT INTO messages (phonenumber, message) VALUES (:phonenumber, :message)");
    query.bindValue(":phonenumber", currentPhoneNumber);
    query.bindValue(":message", message);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to send the message.");
        qDebug() << "Error sending message: " << query.lastError();
        return;
    }
    QMessageBox::information(this, "Success", "Message saved successfully.");
    loadMessages();

}

    //ui->lineEdit->clear();
    // Update chat display (assumed to be a QTextEdit or similar)
    //ui->chatDisplay->append("Me: " + message);



void chat::on_pushButton_2_clicked()
{
 QCoreApplication::quit();
}

