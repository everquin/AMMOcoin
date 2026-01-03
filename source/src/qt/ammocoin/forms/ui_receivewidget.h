/********************************************************************************
** Form generated from reading UI file 'receivewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVEWIDGET_H
#define UI_RECEIVEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qt/ammocoin/optionbutton.h"

QT_BEGIN_NAMESPACE

class Ui_ReceiveWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *left;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelTitle;
    QLabel *labelSubtitle1;
    QSpacerItem *horizontalSpacer;
    QWidget *containerViewPrivacyChecks;
    QVBoxLayout *containerPrivacyChecks;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2_1;
    QPushButton *pushLeft;
    QPushButton *pushRight;
    QLabel *labelSubtitle2;
    QSpacerItem *verticalSpacer_2;
    QWidget *layoutQR;
    QVBoxLayout *verticalLayoutQr;
    QSpacerItem *verticalSpacer11;
    QLabel *labelQrImg;
    QSpacerItem *verticalSpacer_21;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelDate;
    QLabel *labelAddress;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonLabel;
    QPushButton *pushButtonNewAddress;
    QPushButton *pushButtonCopy;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QWidget *right;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *container_right;
    QVBoxLayout *verticalLayout;
    OptionButton *btnRequest;
    OptionButton *btnMyAddresses;
    QWidget *sortWidget;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEditFilter;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBoxSort;
    QComboBox *comboBoxSortOrder;
    QListView *listViewAddress;

    void setupUi(QWidget *ReceiveWidget)
    {
        if (ReceiveWidget->objectName().isEmpty())
            ReceiveWidget->setObjectName(QString::fromUtf8("ReceiveWidget"));
        ReceiveWidget->resize(819, 629);
        ReceiveWidget->setMinimumSize(QSize(0, 0));
        ReceiveWidget->setWindowTitle(QString::fromUtf8("N/A"));
        horizontalLayout_2 = new QHBoxLayout(ReceiveWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        left = new QWidget(ReceiveWidget);
        left->setObjectName(QString::fromUtf8("left"));
        verticalLayout_3 = new QVBoxLayout(left);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, -1, -1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        labelTitle = new QLabel(left);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));

        verticalLayout_4->addWidget(labelTitle);

        labelSubtitle1 = new QLabel(left);
        labelSubtitle1->setObjectName(QString::fromUtf8("labelSubtitle1"));

        verticalLayout_4->addWidget(labelSubtitle1, 0, Qt::AlignTop);


        horizontalLayout_3->addLayout(verticalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        containerViewPrivacyChecks = new QWidget(left);
        containerViewPrivacyChecks->setObjectName(QString::fromUtf8("containerViewPrivacyChecks"));
        containerPrivacyChecks = new QVBoxLayout(containerViewPrivacyChecks);
        containerPrivacyChecks->setSpacing(0);
        containerPrivacyChecks->setObjectName(QString::fromUtf8("containerPrivacyChecks"));
        containerPrivacyChecks->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(containerViewPrivacyChecks);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2_1 = new QHBoxLayout(groupBox);
        horizontalLayout_2_1->setSpacing(0);
        horizontalLayout_2_1->setObjectName(QString::fromUtf8("horizontalLayout_2_1"));
        horizontalLayout_2_1->setContentsMargins(0, 0, 0, 0);
        pushLeft = new QPushButton(groupBox);
        pushLeft->setObjectName(QString::fromUtf8("pushLeft"));
        pushLeft->setMinimumSize(QSize(120, 30));
        pushLeft->setMaximumSize(QSize(120, 30));
        pushLeft->setFocusPolicy(Qt::NoFocus);
        pushLeft->setCheckable(true);
        pushLeft->setAutoExclusive(true);

        horizontalLayout_2_1->addWidget(pushLeft);

        pushRight = new QPushButton(groupBox);
        pushRight->setObjectName(QString::fromUtf8("pushRight"));
        pushRight->setMinimumSize(QSize(120, 30));
        pushRight->setMaximumSize(QSize(120, 30));
        pushRight->setFocusPolicy(Qt::NoFocus);
        pushRight->setCheckable(true);
        pushRight->setChecked(true);
        pushRight->setAutoExclusive(true);

        horizontalLayout_2_1->addWidget(pushRight);


        containerPrivacyChecks->addWidget(groupBox, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        labelSubtitle2 = new QLabel(containerViewPrivacyChecks);
        labelSubtitle2->setObjectName(QString::fromUtf8("labelSubtitle2"));
        labelSubtitle2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        containerPrivacyChecks->addWidget(labelSubtitle2, 0, Qt::AlignHCenter|Qt::AlignTop);


        horizontalLayout_3->addWidget(containerViewPrivacyChecks);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        layoutQR = new QWidget(left);
        layoutQR->setObjectName(QString::fromUtf8("layoutQR"));
        layoutQR->setMaximumSize(QSize(510, 16777215));
        verticalLayoutQr = new QVBoxLayout(layoutQR);
        verticalLayoutQr->setObjectName(QString::fromUtf8("verticalLayoutQr"));
        verticalSpacer11 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayoutQr->addItem(verticalSpacer11);

        labelQrImg = new QLabel(layoutQR);
        labelQrImg->setObjectName(QString::fromUtf8("labelQrImg"));
        labelQrImg->setMinimumSize(QSize(260, 260));
        labelQrImg->setMaximumSize(QSize(260, 260));
        labelQrImg->setAlignment(Qt::AlignCenter);

        verticalLayoutQr->addWidget(labelQrImg, 0, Qt::AlignHCenter);

        verticalSpacer_21 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayoutQr->addItem(verticalSpacer_21);

        widget = new QWidget(layoutQR);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 0));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelLabel = new QLabel(widget);
        labelLabel->setObjectName(QString::fromUtf8("labelLabel"));
        labelLabel->setText(QString::fromUtf8("N/A"));

        horizontalLayout_5->addWidget(labelLabel);

        horizontalSpacer_2 = new QSpacerItem(141, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        labelDate = new QLabel(widget);
        labelDate->setObjectName(QString::fromUtf8("labelDate"));
        labelDate->setText(QString::fromUtf8("N/A"));
        labelDate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(labelDate);


        verticalLayoutQr->addWidget(widget);

        labelAddress = new QLabel(layoutQR);
        labelAddress->setObjectName(QString::fromUtf8("labelAddress"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelAddress->sizePolicy().hasHeightForWidth());
        labelAddress->setSizePolicy(sizePolicy);
        labelAddress->setMinimumSize(QSize(300, 0));
        labelAddress->setText(QString::fromUtf8("N/A"));
        labelAddress->setAlignment(Qt::AlignCenter);

        verticalLayoutQr->addWidget(labelAddress);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayoutQr->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonLabel = new QPushButton(layoutQR);
        pushButtonLabel->setObjectName(QString::fromUtf8("pushButtonLabel"));
        pushButtonLabel->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(pushButtonLabel, 0, Qt::AlignHCenter);

        pushButtonNewAddress = new QPushButton(layoutQR);
        pushButtonNewAddress->setObjectName(QString::fromUtf8("pushButtonNewAddress"));
        pushButtonNewAddress->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(pushButtonNewAddress, 0, Qt::AlignHCenter);

        pushButtonCopy = new QPushButton(layoutQR);
        pushButtonCopy->setObjectName(QString::fromUtf8("pushButtonCopy"));
        pushButtonCopy->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(pushButtonCopy, 0, Qt::AlignHCenter);


        verticalLayoutQr->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutQr->addItem(verticalSpacer_3);


        verticalLayout_2->addWidget(layoutQR, 0, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_2->addWidget(left);

        right = new QWidget(ReceiveWidget);
        right->setObjectName(QString::fromUtf8("right"));
        verticalLayout_5 = new QVBoxLayout(right);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(1, 0, 0, 0);
        container_right = new QVBoxLayout();
        container_right->setSpacing(0);
        container_right->setObjectName(QString::fromUtf8("container_right"));
        container_right->setContentsMargins(0, -1, 0, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(19, -1, 19, -1);
        btnRequest = new OptionButton(right);
        btnRequest->setObjectName(QString::fromUtf8("btnRequest"));

        verticalLayout->addWidget(btnRequest);

        btnMyAddresses = new OptionButton(right);
        btnMyAddresses->setObjectName(QString::fromUtf8("btnMyAddresses"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnMyAddresses->sizePolicy().hasHeightForWidth());
        btnMyAddresses->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(btnMyAddresses);


        container_right->addLayout(verticalLayout);

        sortWidget = new QWidget(right);
        sortWidget->setObjectName(QString::fromUtf8("sortWidget"));
        horizontalLayout_6 = new QHBoxLayout(sortWidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(19, -1, 19, 5);
        lineEditFilter = new QLineEdit(sortWidget);
        lineEditFilter->setObjectName(QString::fromUtf8("lineEditFilter"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditFilter->sizePolicy().hasHeightForWidth());
        lineEditFilter->setSizePolicy(sizePolicy2);
        lineEditFilter->setMinimumSize(QSize(0, 0));
        lineEditFilter->setContextMenuPolicy(Qt::DefaultContextMenu);
        lineEditFilter->setAcceptDrops(false);
        lineEditFilter->setMaxLength(40);

        horizontalLayout_6->addWidget(lineEditFilter);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        comboBoxSort = new QComboBox(sortWidget);
        comboBoxSort->setObjectName(QString::fromUtf8("comboBoxSort"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBoxSort->sizePolicy().hasHeightForWidth());
        comboBoxSort->setSizePolicy(sizePolicy3);
        comboBoxSort->setMinimumSize(QSize(115, 0));

        horizontalLayout_6->addWidget(comboBoxSort);

        comboBoxSortOrder = new QComboBox(sortWidget);
        comboBoxSortOrder->setObjectName(QString::fromUtf8("comboBoxSortOrder"));
        sizePolicy3.setHeightForWidth(comboBoxSortOrder->sizePolicy().hasHeightForWidth());
        comboBoxSortOrder->setSizePolicy(sizePolicy3);
        comboBoxSortOrder->setMinimumSize(QSize(75, 0));

        horizontalLayout_6->addWidget(comboBoxSortOrder);

        comboBoxSort->raise();
        comboBoxSortOrder->raise();
        lineEditFilter->raise();

        container_right->addWidget(sortWidget);

        listViewAddress = new QListView(right);
        listViewAddress->setObjectName(QString::fromUtf8("listViewAddress"));

        container_right->addWidget(listViewAddress);


        verticalLayout_5->addLayout(container_right);


        horizontalLayout_2->addWidget(right);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 1);

        retranslateUi(ReceiveWidget);

        QMetaObject::connectSlotsByName(ReceiveWidget);
    } // setupUi

    void retranslateUi(QWidget *ReceiveWidget)
    {
        labelTitle->setText(QCoreApplication::translate("ReceiveWidget", "Receive", nullptr));
        labelSubtitle1->setText(QCoreApplication::translate("ReceiveWidget", "Scan the QR code or copy the address to receive PIV", nullptr));
        groupBox->setTitle(QString());
        pushLeft->setText(QCoreApplication::translate("ReceiveWidget", "Transparent", nullptr));
        pushRight->setText(QCoreApplication::translate("ReceiveWidget", "Shielded", nullptr));
        labelSubtitle2->setText(QCoreApplication::translate("ReceiveWidget", "Accept transparent or shielded PIV", nullptr));
        labelQrImg->setText(QString());
        pushButtonLabel->setText(QCoreApplication::translate("ReceiveWidget", "Add Label", nullptr));
        pushButtonNewAddress->setText(QCoreApplication::translate("ReceiveWidget", "Generate Address", nullptr));
        pushButtonCopy->setText(QCoreApplication::translate("ReceiveWidget", "Copy", nullptr));
        lineEditFilter->setPlaceholderText(QCoreApplication::translate("ReceiveWidget", "Filter", nullptr));
        (void)ReceiveWidget;
    } // retranslateUi

};

namespace Ui {
    class ReceiveWidget: public Ui_ReceiveWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVEWIDGET_H
