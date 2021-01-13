/********************************************************************************
** Form generated from reading UI file 'groupchat.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPCHAT_H
#define UI_GROUPCHAT_H

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

class Ui_GroupChat
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QLabel *label_2;
    QPushButton *pushButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton_3;
    QLabel *label;
    QPushButton *pushButton_2;

    void setupUi(QWidget *GroupChat)
    {
        if (GroupChat->objectName().isEmpty())
            GroupChat->setObjectName(QStringLiteral("GroupChat"));
        GroupChat->resize(610, 739);
        gridLayout = new QGridLayout(GroupChat);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new QPlainTextEdit(GroupChat);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 3, 0, 1, 5);

        pushButton_4 = new QPushButton(GroupChat);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 2, 1, 1, 1);

        pushButton_5 = new QPushButton(GroupChat);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 2, 2, 1, 1);

        scrollArea_2 = new QScrollArea(GroupChat);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 185, 691));
        label_2 = new QLabel(scrollAreaWidgetContents_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 61, 21));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout->addWidget(scrollArea_2, 1, 5, 4, 1);

        pushButton = new QPushButton(GroupChat);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 4, 3, 1, 1);

        scrollArea = new QScrollArea(GroupChat);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 397, 313));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 1, 0, 1, 5);

        pushButton_3 = new QPushButton(GroupChat);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 0, 1, 1);

        label = new QLabel(GroupChat);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        pushButton_2 = new QPushButton(GroupChat);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 4, 4, 1, 1);


        retranslateUi(GroupChat);

        QMetaObject::connectSlotsByName(GroupChat);
    } // setupUi

    void retranslateUi(QWidget *GroupChat)
    {
        GroupChat->setWindowTitle(QApplication::translate("GroupChat", "Form", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("GroupChat", "\345\233\276\347\211\207", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("GroupChat", "\350\201\212\345\244\251\350\256\260\345\275\225", Q_NULLPTR));
        label_2->setText(QApplication::translate("GroupChat", "<html><head/><body><p><span style=\" font-size:12pt;\">\347\276\244\346\210\220\345\221\230</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("GroupChat", "\345\205\263\351\227\255", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("GroupChat", "\350\241\250\346\203\205", Q_NULLPTR));
        label->setText(QApplication::translate("GroupChat", "<html><head/><body><p><span style=\" font-size:14pt;\">\347\276\244\350\201\212\345\244\251</span></p></body></html>", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("GroupChat", "\345\217\221\351\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GroupChat: public Ui_GroupChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPCHAT_H
