/********************************************************************************
** Form generated from reading UI file 'sendmemodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDMEMODIALOG_H
#define UI_SENDMEMODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SendMemoDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelTitle;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnEsc;
    QLabel *labelMessage;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCancel;
    QPushButton *btnSave;

    void setupUi(QDialog *SendMemoDialog)
    {
        if (SendMemoDialog->objectName().isEmpty())
            SendMemoDialog->setObjectName(QString::fromUtf8("SendMemoDialog"));
        SendMemoDialog->resize(550, 360);
        SendMemoDialog->setWindowTitle(QString::fromUtf8("N/A"));
        verticalLayout = new QVBoxLayout(SendMemoDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(SendMemoDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(30, 20, 30, 20);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        labelTitle = new QLabel(frame);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setMinimumSize(QSize(0, 40));
        labelTitle->setMaximumSize(QSize(16777215, 40));
        labelTitle->setStyleSheet(QString::fromUtf8("padding-left:24px;"));
        labelTitle->setText(QString::fromUtf8("Add Encrypted Memo"));
        labelTitle->setAlignment(Qt::AlignCenter);
        labelTitle->setMargin(7);

        horizontalLayout_3->addWidget(labelTitle);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnEsc = new QPushButton(frame);
        btnEsc->setObjectName(QString::fromUtf8("btnEsc"));
        btnEsc->setMinimumSize(QSize(24, 24));
        btnEsc->setMaximumSize(QSize(24, 24));
        btnEsc->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(btnEsc);


        verticalLayout_2->addLayout(horizontalLayout_3);

        labelMessage = new QLabel(frame);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));
        labelMessage->setMinimumSize(QSize(0, 50));
        labelMessage->setAlignment(Qt::AlignCenter);
        labelMessage->setWordWrap(true);

        verticalLayout_2->addWidget(labelMessage, 0, Qt::AlignHCenter);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, -1, 20, -1);
        textEdit = new QTextEdit(frame);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 120));
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setDocumentTitle(QString::fromUtf8(""));
        textEdit->setHtml(QString::fromUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"));

        horizontalLayout_2->addWidget(textEdit);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(30, -1, 30, -1);
        btnCancel = new QPushButton(frame);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(180, 50));
        btnCancel->setFocusPolicy(Qt::NoFocus);
        btnCancel->setText(QString::fromUtf8("CLEAR"));

        horizontalLayout->addWidget(btnCancel);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(180, 50));
        btnSave->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(btnSave);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(frame);


        retranslateUi(SendMemoDialog);

        QMetaObject::connectSlotsByName(SendMemoDialog);
    } // setupUi

    void retranslateUi(QDialog *SendMemoDialog)
    {
        btnEsc->setText(QString());
        labelMessage->setText(QCoreApplication::translate("SendMemoDialog", "Private message only visible for the recipient(s)", nullptr));
        btnSave->setText(QCoreApplication::translate("SendMemoDialog", "SAVE", nullptr));
        (void)SendMemoDialog;
    } // retranslateUi

};

namespace Ui {
    class SendMemoDialog: public Ui_SendMemoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDMEMODIALOG_H
