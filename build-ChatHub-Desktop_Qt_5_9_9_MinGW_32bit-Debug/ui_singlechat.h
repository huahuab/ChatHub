/********************************************************************************
** Form generated from reading UI file 'singlechat.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLECHAT_H
#define UI_SINGLECHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleChat
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;

    void setupUi(QWidget *SingleChat)
    {
        if (SingleChat->objectName().isEmpty())
            SingleChat->setObjectName(QStringLiteral("SingleChat"));
        SingleChat->resize(764, 739);
        gridLayout = new QGridLayout(SingleChat);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new QPlainTextEdit(SingleChat);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 3, 0, 1, 5);

        scrollArea = new QScrollArea(SingleChat);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 744, 313));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 1, 0, 1, 5);

        pushButton_3 = new QPushButton(SingleChat);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 0, 1, 1);

        pushButton_5 = new QPushButton(SingleChat);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 2, 2, 1, 1);

        pushButton = new QPushButton(SingleChat);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 4, 4, 1, 1);

        label = new QLabel(SingleChat);
        label->setObjectName(QStringLiteral("label"));
        label->setTextFormat(Qt::AutoText);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton_4 = new QPushButton(SingleChat);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 2, 1, 1, 1);

        pushButton_2 = new QPushButton(SingleChat);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 4, 3, 1, 1);


        retranslateUi(SingleChat);

        QMetaObject::connectSlotsByName(SingleChat);
    } // setupUi

    void retranslateUi(QWidget *SingleChat)
    {
        SingleChat->setWindowTitle(QApplication::translate("SingleChat", "Form", Q_NULLPTR));
        plainTextEdit->setPlainText(QString());
        pushButton_3->setText(QApplication::translate("SingleChat", "\350\241\250\346\203\205", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("SingleChat", "\350\201\212\345\244\251\350\256\260\345\275\225", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SingleChat", "\345\217\221\351\200\201", Q_NULLPTR));
        label->setText(QApplication::translate("SingleChat", "<html><head/><body><p><span style=\" font-size:14pt;\">\345\245\275\345\217\213</span></p></body></html>", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("SingleChat", "\345\233\276\347\211\207", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SingleChat", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SingleChat: public Ui_SingleChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLECHAT_H
