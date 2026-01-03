/********************************************************************************
** Form generated from reading UI file 'txrow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TXROW_H
#define UI_TXROW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TxRow
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *rowContainer;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *icon;
    QVBoxLayout *verticalLayout;
    QLabel *lblAddress;
    QLabel *lblDate;
    QWidget *containerAmounts;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblAmountTop;
    QLabel *lblAmountBottom;
    QLabel *lblDivisory;

    void setupUi(QWidget *TxRow)
    {
        if (TxRow->objectName().isEmpty())
            TxRow->setObjectName(QString::fromUtf8("TxRow"));
        TxRow->resize(601, 70);
        TxRow->setMinimumSize(QSize(0, 40));
        TxRow->setWindowTitle(QString::fromUtf8("N/A"));
        verticalLayout_3 = new QVBoxLayout(TxRow);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        rowContainer = new QWidget(TxRow);
        rowContainer->setObjectName(QString::fromUtf8("rowContainer"));
        verticalLayout_2 = new QVBoxLayout(rowContainer);
        verticalLayout_2->setSpacing(9);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 9, 20, 0);
        frame = new QFrame(rowContainer);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("border:none;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        icon = new QPushButton(frame);
        icon->setObjectName(QString::fromUtf8("icon"));
        icon->setFocusPolicy(Qt::NoFocus);
        icon->setStyleSheet(QString::fromUtf8("border:none;"));
        icon->setIconSize(QSize(28, 28));

        horizontalLayout->addWidget(icon);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(9, -1, -1, -1);
        lblAddress = new QLabel(frame);
        lblAddress->setObjectName(QString::fromUtf8("lblAddress"));
        lblAddress->setStyleSheet(QString::fromUtf8(""));
        lblAddress->setText(QString::fromUtf8("N/A"));
        lblAddress->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        verticalLayout->addWidget(lblAddress);

        lblDate = new QLabel(frame);
        lblDate->setObjectName(QString::fromUtf8("lblDate"));
        lblDate->setStyleSheet(QString::fromUtf8(""));
        lblDate->setText(QString::fromUtf8("N/A"));
        lblDate->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(lblDate);


        horizontalLayout->addLayout(verticalLayout);

        containerAmounts = new QWidget(frame);
        containerAmounts->setObjectName(QString::fromUtf8("containerAmounts"));
        containerAmounts->setMinimumSize(QSize(80, 0));
        verticalLayout_4 = new QVBoxLayout(containerAmounts);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        lblAmountTop = new QLabel(containerAmounts);
        lblAmountTop->setObjectName(QString::fromUtf8("lblAmountTop"));
        lblAmountTop->setStyleSheet(QString::fromUtf8(""));
        lblAmountTop->setText(QString::fromUtf8("N/A"));

        verticalLayout_4->addWidget(lblAmountTop, 0, Qt::AlignRight);

        lblAmountBottom = new QLabel(containerAmounts);
        lblAmountBottom->setObjectName(QString::fromUtf8("lblAmountBottom"));
        lblAmountBottom->setStyleSheet(QString::fromUtf8(""));
        lblAmountBottom->setText(QString::fromUtf8("N/A"));

        verticalLayout_4->addWidget(lblAmountBottom, 0, Qt::AlignRight);


        horizontalLayout->addWidget(containerAmounts);

        horizontalLayout->setStretch(1, 2);

        verticalLayout_2->addWidget(frame);

        lblDivisory = new QLabel(rowContainer);
        lblDivisory->setObjectName(QString::fromUtf8("lblDivisory"));
        lblDivisory->setMinimumSize(QSize(0, 1));
        lblDivisory->setMaximumSize(QSize(16777215, 1));
        lblDivisory->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));
        lblDivisory->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        verticalLayout_2->addWidget(lblDivisory);


        verticalLayout_3->addWidget(rowContainer);


        retranslateUi(TxRow);

        QMetaObject::connectSlotsByName(TxRow);
    } // setupUi

    void retranslateUi(QWidget *TxRow)
    {
        icon->setText(QString());
        lblDivisory->setText(QString());
        (void)TxRow;
    } // retranslateUi

};

namespace Ui {
    class TxRow: public Ui_TxRow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TXROW_H
