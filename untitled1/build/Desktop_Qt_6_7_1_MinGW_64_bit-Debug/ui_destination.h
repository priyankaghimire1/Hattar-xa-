/********************************************************************************
** Form generated from reading UI file 'destination.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESTINATION_H
#define UI_DESTINATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_destination
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSplitter *splitter;
    QLabel *label;
    QLineEdit *lineEdit_From;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_To;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *destination)
    {
        if (destination->objectName().isEmpty())
            destination->setObjectName("destination");
        destination->resize(800, 600);
        centralwidget = new QWidget(destination);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(470, 190, 93, 29));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(470, 140, 93, 29));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(140, 110, 217, 26));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName("label");
        splitter->addWidget(label);
        lineEdit_From = new QLineEdit(splitter);
        lineEdit_From->setObjectName("lineEdit_From");
        splitter->addWidget(lineEdit_From);
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(150, 140, 226, 28));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        lineEdit_To = new QLineEdit(widget);
        lineEdit_To->setObjectName("lineEdit_To");

        horizontalLayout->addWidget(lineEdit_To);

        destination->setCentralWidget(centralwidget);
        menubar = new QMenuBar(destination);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        destination->setMenuBar(menubar);
        statusbar = new QStatusBar(destination);
        statusbar->setObjectName("statusbar");
        destination->setStatusBar(statusbar);

        retranslateUi(destination);

        QMetaObject::connectSlotsByName(destination);
    } // setupUi

    void retranslateUi(QMainWindow *destination)
    {
        destination->setWindowTitle(QCoreApplication::translate("destination", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("destination", "Click me!", nullptr));
        pushButton_2->setText(QCoreApplication::translate("destination", "Exit", nullptr));
        label->setText(QCoreApplication::translate("destination", "From", nullptr));
        label_2->setText(QCoreApplication::translate("destination", "To", nullptr));
    } // retranslateUi

};

namespace Ui {
    class destination: public Ui_destination {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESTINATION_H
