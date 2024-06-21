#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{
    QString Phonenumber = ui->lineedit_phone_number->text();
    QString Pin = ui->lineedit_pin_number->text();
    if (Phonenumber=="9876543210" && Pin=="123")
    {
        QMessageBox::information(this,"Login Sucess","Proceed      ");
    }
    else
    {
        QMessageBox::warning(this,"Login failed.", "Please check your phone number and PIN code");
    }

}


void MainWindow::on_pushButton_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"Cancel?","Do you want to quit logging in?");
    if (reply==QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

