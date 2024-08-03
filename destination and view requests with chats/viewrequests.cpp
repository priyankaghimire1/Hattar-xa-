#include "viewrequests.h"
#include "ui_viewrequests.h"

viewRequests::viewRequests(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::viewRequests)
    ,chatriderWindow(nullptr)
{
    ui->setupUi(this);
}

viewRequests::~viewRequests()
{
    delete ui;
}
void viewRequests::setCurrentPhoneNumber(const QString &phoneNumber) {
    currentPhoneNumber = phoneNumber;
}
void viewRequests::on_pushButton_clicked()
{
    QSqlQueryModel *modal= new QSqlQueryModel();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Priyanka/Coding/qt/qt/database/db.sqlite");
    db.open();
    QSqlQuery query = QSqlQuery(db);
    query.prepare ("SELECT USERID, PHONENUMBER, location_from, location_to, status FROM user WHERE status = 'on hold';");
    query.exec();
    modal->setQuery(std::move(query));
    ui->tableView->setModel(modal);
    db.close();
}





void viewRequests::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/Priyanka/Coding/qt/qt/database/db.sqlite");
    db.open();
    QSqlQuery query = QSqlQuery(db);
    query.prepare("UPDATE user SET status = ' Accepted ' WHERE USERID = " + val + ";");
    query.exec();

    if (!query.exec()){
        QMessageBox::warning(this, "Failure", "Invalid phone number or pin.");
        return;
    }
    loadMessages();
}
void viewRequests::loadMessages()
{
    QSqlQuery query;
    query.prepare("SELECT message FROM messages ORDER BY timestamp DESC LIMIT 1");
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
void viewRequests::on_pushButton_3_clicked()
{
    QString message = ui->lineEdit->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Message cannot be empty.");
        return;
    }

    // Save the message to the database
    QSqlQuery query;
    query.prepare("INSERT INTO messagesRider(message) VALUES (:message)");
    //query.prepare("UPDATE messagesRider SET message=:message WHERE phonenumber=:phonenumber)");
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
void viewRequests::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}


