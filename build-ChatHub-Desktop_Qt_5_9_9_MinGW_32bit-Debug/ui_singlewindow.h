/********************************************************************************
** Form generated from reading UI file 'singlewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEWINDOW_H
#define UI_SINGLEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(542, 565);
        scrollArea = new QScrollArea(Form);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 40, 541, 331));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 539, 329));
        scrollArea->setWidget(scrollAreaWidgetContents_2);
        plainTextEdit = new QPlainTextEdit(Form);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 390, 541, 131));
        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(370, 530, 75, 23));
        pushButton_2 = new QPushButton(Form);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(460, 530, 75, 23));
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 161, 21));
        QFont font;
        font.setFamily(QStringLiteral("18thCentury"));
        font.setPointSize(16);
        label->setFont(font);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Form", "\345\205\263\351\227\255", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Form", "\345\217\221\351\200\201", Q_NULLPTR));
        label->setText(QApplication::translate("Form", "\345\245\275\345\217\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEWINDOW_H
