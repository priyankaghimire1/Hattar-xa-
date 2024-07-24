#ifndef RIDERREGISTER_H
#define RIDERREGISTER_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
namespace Ui {
class riderregister;
}

class riderregister : public QMainWindow
{
    Q_OBJECT

public:
    explicit riderregister(QWidget *parent = nullptr);
    ~riderregister();

private slots:
    void on_pushButton_clicked();

private:
    Ui::riderregister *ui;
};

#endif // RIDERREGISTER_H
