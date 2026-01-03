/********************************************************************************
** Form generated from reading UI file 'balancebubble.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANCEBUBBLE_H
#define UI_BALANCEBUBBLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BalanceBubble
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lblFirst;
    QLabel *textTransparent;
    QLabel *lblSecond;
    QLabel *textShielded;

    void setupUi(QWidget *BalanceBubble)
    {
        if (BalanceBubble->objectName().isEmpty())
            BalanceBubble->setObjectName(QString::fromUtf8("BalanceBubble"));
        BalanceBubble->resize(218, 178);
        BalanceBubble->setMinimumSize(QSize(218, 178));
        BalanceBubble->setMaximumSize(QSize(250, 178));
        BalanceBubble->setWindowTitle(QString::fromUtf8("N/A"));
        BalanceBubble->setStyleSheet(QString::fromUtf8("#BalanceBubble{\n"
"background-color:transparent\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(BalanceBubble);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(BalanceBubble);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(200, 160));
        frame->setMaximumSize(QSize(250, 160));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(10);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblFirst = new QLabel(frame);
        lblFirst->setObjectName(QString::fromUtf8("lblFirst"));
        lblFirst->setStyleSheet(QString::fromUtf8(""));
        lblFirst->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lblFirst);


        verticalLayout->addLayout(horizontalLayout);

        textTransparent = new QLabel(frame);
        textTransparent->setObjectName(QString::fromUtf8("textTransparent"));
        textTransparent->setStyleSheet(QString::fromUtf8(""));
        textTransparent->setText(QString::fromUtf8("N/A"));
        textTransparent->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(textTransparent);

        lblSecond = new QLabel(frame);
        lblSecond->setObjectName(QString::fromUtf8("lblSecond"));
        lblSecond->setStyleSheet(QString::fromUtf8(""));
        lblSecond->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblSecond);

        textShielded = new QLabel(frame);
        textShielded->setObjectName(QString::fromUtf8("textShielded"));
        textShielded->setStyleSheet(QString::fromUtf8(""));
        textShielded->setText(QString::fromUtf8("N/A"));
        textShielded->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(textShielded);


        verticalLayout_2->addWidget(frame);


        retranslateUi(BalanceBubble);

        QMetaObject::connectSlotsByName(BalanceBubble);
    } // setupUi

    void retranslateUi(QWidget *BalanceBubble)
    {
        lblFirst->setText(QCoreApplication::translate("BalanceBubble", "Transparent", nullptr));
        lblSecond->setText(QCoreApplication::translate("BalanceBubble", "Shielded", nullptr));
        (void)BalanceBubble;
    } // retranslateUi

};

namespace Ui {
    class BalanceBubble: public Ui_BalanceBubble {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANCEBUBBLE_H
