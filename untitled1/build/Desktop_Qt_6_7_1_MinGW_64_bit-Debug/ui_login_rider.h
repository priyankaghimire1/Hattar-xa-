/********************************************************************************
** Form generated from reading UI file 'login_rider.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_RIDER_H
#define UI_LOGIN_RIDER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login_rider
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_Phonenumber;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_Pin;
    QMenuBar *menubar;
    QMenu *menuLogin_as_rider;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *login_rider)
    {
        if (login_rider->objectName().isEmpty())
            login_rider->setObjectName("login_rider");
        login_rider->resize(800, 600);
        centralwidget = new QWidget(login_rider);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(400, 50, 93, 29));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(400, 100, 93, 29));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(130, 50, 226, 28));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_Phonenumber = new QLineEdit(widget);
        lineEdit_Phonenumber->setObjectName("lineEdit_Phonenumber");

        horizontalLayout->addWidget(lineEdit_Phonenumber);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(130, 100, 226, 28));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_Pin = new QLineEdit(widget1);
        lineEdit_Pin->setObjectName("lineEdit_Pin");

        horizontalLayout_2->addWidget(lineEdit_Pin);

        login_rider->setCentralWidget(centralwidget);
        menubar = new QMenuBar(login_rider);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menuLogin_as_rider = new QMenu(menubar);
        menuLogin_as_rider->setObjectName("menuLogin_as_rider");
        login_rider->setMenuBar(menubar);
        statusbar = new QStatusBar(login_rider);
        statusbar->setObjectName("statusbar");
        login_rider->setStatusBar(statusbar);

        menubar->addAction(menuLogin_as_rider->menuAction());

        retranslateUi(login_rider);

        QMetaObject::connectSlotsByName(login_rider);
    } // setupUi

    void retranslateUi(QMainWindow *login_rider)
    {
        login_rider->setWindowTitle(QCoreApplication::translate("login_rider", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("login_rider", "Login", nullptr));
        pushButton_2->setText(QCoreApplication::translate("login_rider", "Exit", nullptr));
        label->setText(QCoreApplication::translate("login_rider", "Phonenumber", nullptr));
        label_2->setText(QCoreApplication::translate("login_rider", "Pin", nullptr));
        menuLogin_as_rider->setTitle(QCoreApplication::translate("login_rider", "Login as rider", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login_rider: public Ui_login_rider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_RIDER_H
