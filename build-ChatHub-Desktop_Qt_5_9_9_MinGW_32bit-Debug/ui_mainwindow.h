/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *line;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QFrame *line_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QFrame *line_3;
    QScrollBar *verticalScrollBar;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(310, 710);
        MainWindow->setMinimumSize(QSize(310, 710));
        MainWindow->setMaximumSize(QSize(310, 710));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(-10, 80, 321, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 0, 131, 31));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(0, 90, 221, 21));
        lineEdit->setFrame(false);
        lineEdit->setDragEnabled(false);
        lineEdit->setClearButtonEnabled(true);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 90, 71, 21));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(80, 30, 221, 41));
        textBrowser->setFrameShape(QFrame::NoFrame);
        textBrowser->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 630, 301, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(110, 640, 75, 23));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(220, 640, 75, 23));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(0, 640, 75, 23));
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 110, 311, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        verticalScrollBar = new QScrollBar(centralwidget);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(290, 120, 20, 511));
        verticalScrollBar->setOrientation(Qt::Vertical);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 10, 71, 71));
        label->setPixmap(QPixmap(QString::fromUtf8("img/profile.jpg")));
        label->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 310, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">intmian</span></p></body></html>", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242\345\245\275\345\217\213/\350\201\212\345\244\251\347\276\244...", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\350\277\231\344\270\252\344\272\272\345\276\210\346\207\222\357\274\214\344\273\200\344\271\210\344\271\237\346\262\241\346\234\211\347\225\231\344\270\213</span></p></body></html>", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
