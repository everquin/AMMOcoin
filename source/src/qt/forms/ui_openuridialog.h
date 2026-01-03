/********************************************************************************
** Form generated from reading UI file 'openuridialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENURIDIALOG_H
#define UI_OPENURIDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qvalidatedlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_OpenURIDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTitle;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelSubtitle;
    QHBoxLayout *horizontalLayout;
    QValidatedLineEdit *uriEdit;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *OpenURIDialog)
    {
        if (OpenURIDialog->objectName().isEmpty())
            OpenURIDialog->setObjectName(QString::fromUtf8("OpenURIDialog"));
        OpenURIDialog->resize(564, 260);
        verticalLayout = new QVBoxLayout(OpenURIDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(OpenURIDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 20, 20, 16);
        labelTitle = new QLabel(frame);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(labelTitle);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        labelSubtitle = new QLabel(frame);
        labelSubtitle->setObjectName(QString::fromUtf8("labelSubtitle"));
        labelSubtitle->setText(QString::fromUtf8("TextLabel"));

        verticalLayout_2->addWidget(labelSubtitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        uriEdit = new QValidatedLineEdit(frame);
        uriEdit->setObjectName(QString::fromUtf8("uriEdit"));
        uriEdit->setStyleSheet(QString::fromUtf8("#uriEdit{\n"
"	border-top-right-radius:0px;\n"
"	border-bottom-right-radius:0px;\n"
"}"));

        horizontalLayout->addWidget(uriEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 50));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(289, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonCancel = new QPushButton(widget);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setMinimumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(pushButtonCancel);

        pushButtonOK = new QPushButton(widget);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setMinimumSize(QSize(100, 40));

        horizontalLayout_2->addWidget(pushButtonOK);


        verticalLayout_2->addWidget(widget);


        verticalLayout->addWidget(frame);


        retranslateUi(OpenURIDialog);

        QMetaObject::connectSlotsByName(OpenURIDialog);
    } // setupUi

    void retranslateUi(QDialog *OpenURIDialog)
    {
        OpenURIDialog->setWindowTitle(QCoreApplication::translate("OpenURIDialog", "Open URI", nullptr));
        labelTitle->setText(QCoreApplication::translate("OpenURIDialog", "Open AMMOcoin URI", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("OpenURIDialog", "CANCEL", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("OpenURIDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenURIDialog: public Ui_OpenURIDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENURIDIALOG_H
