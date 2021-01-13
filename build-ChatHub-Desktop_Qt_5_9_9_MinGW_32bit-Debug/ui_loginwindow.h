/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QRadioButton *radioButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(420, 250);
        LoginWindow->setMinimumSize(QSize(420, 250));
        LoginWindow->setMaximumSize(QSize(420, 250));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 180, 75, 23));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(130, 100, 141, 21));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(130, 140, 141, 21));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 100, 31, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 140, 31, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(120, 20, 161, 61));
        QFont font;
        font.setFamily(QStringLiteral("Constantia"));
        font.setPointSize(30);
        label_3->setFont(font);
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(290, 140, 89, 16));
        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 420, 22));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        LoginWindow->setStatusBar(statusbar);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "\347\231\273\345\275\225ChatHub", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("LoginWindow", "\347\231\273\345\275\225", Q_NULLPTR));
        label->setText(QApplication::translate("LoginWindow", "\350\264\246\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginWindow", "\345\257\206\347\240\201", Q_NULLPTR));
        label_3->setText(QApplication::translate("LoginWindow", "ChatHub", Q_NULLPTR));
        radioButton->setText(QApplication::translate("LoginWindow", "\350\256\260\344\275\217\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
