#ifndef CHAT_H
#define CHAT_H
#include <QMainWindow>
#include <QtSql>
#include <QString>
namespace Ui {
class chat;
}

class chat : public QMainWindow
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();
    void setCurrentPhoneNumber(const QString &phoneNumber);
     void loadMessages();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::chat *ui;
    QString currentPhoneNumber;
    QSqlDatabase db;
};

#endif // CHAT_H
