/********************************************************************************
** Form generated from reading UI file 'myaddressrow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYADDRESSROW_H
#define UI_MYADDRESSROW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyAddressRow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QSpacerItem *horizontalSpacer;
    QLabel *labelDate;
    QLabel *labelAddress;

    void setupUi(QWidget *MyAddressRow)
    {
        if (MyAddressRow->objectName().isEmpty())
            MyAddressRow->setObjectName(QString::fromUtf8("MyAddressRow"));
        MyAddressRow->resize(400, 60);
        MyAddressRow->setWindowTitle(QString::fromUtf8("N/A"));
        verticalLayout = new QVBoxLayout(MyAddressRow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(20, 10, 20, 20);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelName = new QLabel(MyAddressRow);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setText(QString::fromUtf8("Label"));

        horizontalLayout->addWidget(labelName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelDate = new QLabel(MyAddressRow);
        labelDate->setObjectName(QString::fromUtf8("labelDate"));
        labelDate->setText(QString::fromUtf8("N/A"));

        horizontalLayout->addWidget(labelDate);


        verticalLayout->addLayout(horizontalLayout);

        labelAddress = new QLabel(MyAddressRow);
        labelAddress->setObjectName(QString::fromUtf8("labelAddress"));
        labelAddress->setText(QString::fromUtf8("N/A"));

        verticalLayout->addWidget(labelAddress);


        retranslateUi(MyAddressRow);

        QMetaObject::connectSlotsByName(MyAddressRow);
    } // setupUi

    void retranslateUi(QWidget *MyAddressRow)
    {
        (void)MyAddressRow;
    } // retranslateUi

};

namespace Ui {
    class MyAddressRow: public Ui_MyAddressRow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYADDRESSROW_H
