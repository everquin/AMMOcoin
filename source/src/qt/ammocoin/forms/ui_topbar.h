/********************************************************************************
** Form generated from reading UI file 'topbar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPBAR_H
#define UI_TOPBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qt/ammocoin/expandablebutton.h"
#include "qt/ammocoin/pfborderimage.h"

QT_BEGIN_NAMESPACE

class Ui_TopBar
{
public:
    QVBoxLayout *verticalLayout_10;
    PFBorderImage *containerTop;
    QVBoxLayout *verticalLayout_11;
    QWidget *top_container_2;
    QHBoxLayout *top_container;
    QWidget *widgetTopAmount;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelAmountTopPiv;
    QLabel *labelTrans;
    QSpacerItem *horizontalSpacer_11;
    QLabel *typeSpacerTop;
    QSpacerItem *horizontalSpacer_12;
    QLabel *labelAmountTopShieldedPiv;
    QLabel *labelShield;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QWidget *layoutSync;
    QVBoxLayout *verticalLayout_9;
    ExpandableButton *pushButtonSync;
    ExpandableButton *pushButtonHDUpgrade;
    ExpandableButton *pushButtonStack;
    ExpandableButton *pushButtonColdStaking;
    ExpandableButton *pushButtonConnection;
    ExpandableButton *pushButtonTor;
    ExpandableButton *pushButtonLock;
    ExpandableButton *pushButtonTheme;
    ExpandableButton *pushButtonFAQ;
    QWidget *bottom_container;
    QHBoxLayout *botton_container;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayoutContainerAvailable;
    QLabel *labelTitle1;
    QPushButton *pushButtonBalanceInfo;
    QSpacerItem *horizontalSpacer_4;
    QLabel *labelAmountPiv;
    QWidget *container_imm_pend;
    QHBoxLayout *horizontalLayout_2;
    QWidget *container_pending;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelTitle3;
    QLabel *labelPendingPiv;
    QSpacerItem *horizontalSpacer_3;
    QWidget *container_immature;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelTitle4;
    QLabel *labelImmaturePiv;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;
    QWidget *qrContainer;
    QVBoxLayout *containerQR;
    QPushButton *btnQr;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonQR;

    void setupUi(QWidget *TopBar)
    {
        if (TopBar->objectName().isEmpty())
            TopBar->setObjectName(QString::fromUtf8("TopBar"));
        TopBar->resize(734, 200);
        TopBar->setMinimumSize(QSize(0, 200));
        TopBar->setMaximumSize(QSize(16777215, 200));
        TopBar->setWindowTitle(QString::fromUtf8("N/A"));
        verticalLayout_10 = new QVBoxLayout(TopBar);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        containerTop = new PFBorderImage(TopBar);
        containerTop->setObjectName(QString::fromUtf8("containerTop"));
        verticalLayout_11 = new QVBoxLayout(containerTop);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        top_container_2 = new QWidget(containerTop);
        top_container_2->setObjectName(QString::fromUtf8("top_container_2"));
        top_container_2->setMinimumSize(QSize(0, 65));
        top_container = new QHBoxLayout(top_container_2);
        top_container->setSpacing(0);
        top_container->setObjectName(QString::fromUtf8("top_container"));
        top_container->setContentsMargins(14, 0, 14, 0);
        widgetTopAmount = new QWidget(top_container_2);
        widgetTopAmount->setObjectName(QString::fromUtf8("widgetTopAmount"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTopAmount->sizePolicy().hasHeightForWidth());
        widgetTopAmount->setSizePolicy(sizePolicy);
        horizontalLayout_5 = new QHBoxLayout(widgetTopAmount);
        horizontalLayout_5->setSpacing(5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        labelAmountTopPiv = new QLabel(widgetTopAmount);
        labelAmountTopPiv->setObjectName(QString::fromUtf8("labelAmountTopPiv"));
        labelAmountTopPiv->setMinimumSize(QSize(0, 36));
        labelAmountTopPiv->setStyleSheet(QString::fromUtf8("padding:0px;margin:0px;"));
        labelAmountTopPiv->setText(QString::fromUtf8("480.0685 PIV"));

        horizontalLayout_5->addWidget(labelAmountTopPiv, 0, Qt::AlignTop);

        labelTrans = new QLabel(widgetTopAmount);
        labelTrans->setObjectName(QString::fromUtf8("labelTrans"));

        horizontalLayout_5->addWidget(labelTrans);

        horizontalSpacer_11 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);

        typeSpacerTop = new QLabel(widgetTopAmount);
        typeSpacerTop->setObjectName(QString::fromUtf8("typeSpacerTop"));
        typeSpacerTop->setMinimumSize(QSize(1, 30));
        typeSpacerTop->setMaximumSize(QSize(1, 30));
        typeSpacerTop->setStyleSheet(QString::fromUtf8("background-color:white;\n"
"padding:0px;\n"
"border:none;"));

        horizontalLayout_5->addWidget(typeSpacerTop, 0, Qt::AlignVCenter);

        horizontalSpacer_12 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);

        labelAmountTopShieldedPiv = new QLabel(widgetTopAmount);
        labelAmountTopShieldedPiv->setObjectName(QString::fromUtf8("labelAmountTopShieldedPiv"));
        labelAmountTopShieldedPiv->setMinimumSize(QSize(0, 36));
        labelAmountTopShieldedPiv->setText(QString::fromUtf8("1.000 PIV"));

        horizontalLayout_5->addWidget(labelAmountTopShieldedPiv, 0, Qt::AlignTop);

        labelShield = new QLabel(widgetTopAmount);
        labelShield->setObjectName(QString::fromUtf8("labelShield"));

        horizontalLayout_5->addWidget(labelShield);


        top_container->addWidget(widgetTopAmount, 0, Qt::AlignVCenter);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        top_container->addItem(horizontalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(12);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 0, -1);
        layoutSync = new QWidget(top_container_2);
        layoutSync->setObjectName(QString::fromUtf8("layoutSync"));
        layoutSync->setMinimumSize(QSize(0, 36));
        layoutSync->setMaximumSize(QSize(16777215, 36));
        verticalLayout_9 = new QVBoxLayout(layoutSync);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        pushButtonSync = new ExpandableButton(layoutSync);
        pushButtonSync->setObjectName(QString::fromUtf8("pushButtonSync"));
        pushButtonSync->setMinimumSize(QSize(36, 36));
        pushButtonSync->setMaximumSize(QSize(16777215, 36));

        verticalLayout_9->addWidget(pushButtonSync);


        horizontalLayout_4->addWidget(layoutSync, 0, Qt::AlignRight);

        pushButtonHDUpgrade = new ExpandableButton(top_container_2);
        pushButtonHDUpgrade->setObjectName(QString::fromUtf8("pushButtonHDUpgrade"));
        pushButtonHDUpgrade->setMinimumSize(QSize(36, 36));

        horizontalLayout_4->addWidget(pushButtonHDUpgrade);

        pushButtonStack = new ExpandableButton(top_container_2);
        pushButtonStack->setObjectName(QString::fromUtf8("pushButtonStack"));
        pushButtonStack->setMinimumSize(QSize(36, 36));

        horizontalLayout_4->addWidget(pushButtonStack);

        pushButtonColdStaking = new ExpandableButton(top_container_2);
        pushButtonColdStaking->setObjectName(QString::fromUtf8("pushButtonColdStaking"));
        pushButtonColdStaking->setMinimumSize(QSize(36, 36));

        horizontalLayout_4->addWidget(pushButtonColdStaking);

        pushButtonConnection = new ExpandableButton(top_container_2);
        pushButtonConnection->setObjectName(QString::fromUtf8("pushButtonConnection"));
        pushButtonConnection->setMinimumSize(QSize(36, 36));

        horizontalLayout_4->addWidget(pushButtonConnection);

        pushButtonTor = new ExpandableButton(top_container_2);
        pushButtonTor->setObjectName(QString::fromUtf8("pushButtonTor"));
        pushButtonTor->setMinimumSize(QSize(36, 36));

        horizontalLayout_4->addWidget(pushButtonTor);

        pushButtonLock = new ExpandableButton(top_container_2);
        pushButtonLock->setObjectName(QString::fromUtf8("pushButtonLock"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonLock->sizePolicy().hasHeightForWidth());
        pushButtonLock->setSizePolicy(sizePolicy1);
        pushButtonLock->setMinimumSize(QSize(36, 0));

        horizontalLayout_4->addWidget(pushButtonLock);

        pushButtonTheme = new ExpandableButton(top_container_2);
        pushButtonTheme->setObjectName(QString::fromUtf8("pushButtonTheme"));
        pushButtonTheme->setMinimumSize(QSize(36, 36));
        pushButtonTheme->setMaximumSize(QSize(16777215, 36));

        horizontalLayout_4->addWidget(pushButtonTheme);

        pushButtonFAQ = new ExpandableButton(top_container_2);
        pushButtonFAQ->setObjectName(QString::fromUtf8("pushButtonFAQ"));
        pushButtonFAQ->setMinimumSize(QSize(36, 36));

        horizontalLayout_4->addWidget(pushButtonFAQ);


        top_container->addLayout(horizontalLayout_4);


        verticalLayout_11->addWidget(top_container_2);

        bottom_container = new QWidget(containerTop);
        bottom_container->setObjectName(QString::fromUtf8("bottom_container"));
        bottom_container->setMinimumSize(QSize(0, 135));
        botton_container = new QHBoxLayout(bottom_container);
        botton_container->setObjectName(QString::fromUtf8("botton_container"));
        botton_container->setContentsMargins(10, 0, 10, 10);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, -1, 30, -1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayoutContainerAvailable = new QHBoxLayout();
        horizontalLayoutContainerAvailable->setSpacing(5);
        horizontalLayoutContainerAvailable->setObjectName(QString::fromUtf8("horizontalLayoutContainerAvailable"));
        labelTitle1 = new QLabel(bottom_container);
        labelTitle1->setObjectName(QString::fromUtf8("labelTitle1"));

        horizontalLayoutContainerAvailable->addWidget(labelTitle1);

        pushButtonBalanceInfo = new QPushButton(bottom_container);
        pushButtonBalanceInfo->setObjectName(QString::fromUtf8("pushButtonBalanceInfo"));
        pushButtonBalanceInfo->setMinimumSize(QSize(26, 26));
        pushButtonBalanceInfo->setMaximumSize(QSize(26, 26));
        pushButtonBalanceInfo->setMouseTracking(true);
        pushButtonBalanceInfo->setFocusPolicy(Qt::NoFocus);
        pushButtonBalanceInfo->setText(QString::fromUtf8(""));
        pushButtonBalanceInfo->setIconSize(QSize(24, 24));
#if QT_CONFIG(shortcut)
        pushButtonBalanceInfo->setShortcut(QString::fromUtf8(""));
#endif // QT_CONFIG(shortcut)

        horizontalLayoutContainerAvailable->addWidget(pushButtonBalanceInfo);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayoutContainerAvailable->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayoutContainerAvailable);

        labelAmountPiv = new QLabel(bottom_container);
        labelAmountPiv->setObjectName(QString::fromUtf8("labelAmountPiv"));
        labelAmountPiv->setText(QString::fromUtf8("480.0685 PIV"));

        verticalLayout_2->addWidget(labelAmountPiv);


        verticalLayout_7->addLayout(verticalLayout_2);

        container_imm_pend = new QWidget(bottom_container);
        container_imm_pend->setObjectName(QString::fromUtf8("container_imm_pend"));
        horizontalLayout_2 = new QHBoxLayout(container_imm_pend);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        container_pending = new QWidget(container_imm_pend);
        container_pending->setObjectName(QString::fromUtf8("container_pending"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(container_pending->sizePolicy().hasHeightForWidth());
        container_pending->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(container_pending);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelTitle3 = new QLabel(container_pending);
        labelTitle3->setObjectName(QString::fromUtf8("labelTitle3"));

        verticalLayout_3->addWidget(labelTitle3);

        labelPendingPiv = new QLabel(container_pending);
        labelPendingPiv->setObjectName(QString::fromUtf8("labelPendingPiv"));
        labelPendingPiv->setText(QString::fromUtf8("6.943 PIV"));

        verticalLayout_3->addWidget(labelPendingPiv);


        horizontalLayout_2->addWidget(container_pending, 0, Qt::AlignLeft);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        container_immature = new QWidget(container_imm_pend);
        container_immature->setObjectName(QString::fromUtf8("container_immature"));
        sizePolicy2.setHeightForWidth(container_immature->sizePolicy().hasHeightForWidth());
        container_immature->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(container_immature);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        labelTitle4 = new QLabel(container_immature);
        labelTitle4->setObjectName(QString::fromUtf8("labelTitle4"));

        verticalLayout_4->addWidget(labelTitle4);

        labelImmaturePiv = new QLabel(container_immature);
        labelImmaturePiv->setObjectName(QString::fromUtf8("labelImmaturePiv"));
        labelImmaturePiv->setText(QString::fromUtf8("10 PIV"));

        verticalLayout_4->addWidget(labelImmaturePiv);


        horizontalLayout_2->addWidget(container_immature, 0, Qt::AlignLeft);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout_7->addWidget(container_imm_pend);


        botton_container->addLayout(verticalLayout_7);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        botton_container->addItem(horizontalSpacer_2);

        qrContainer = new QWidget(bottom_container);
        qrContainer->setObjectName(QString::fromUtf8("qrContainer"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(qrContainer->sizePolicy().hasHeightForWidth());
        qrContainer->setSizePolicy(sizePolicy3);
        qrContainer->setMinimumSize(QSize(90, 110));
        qrContainer->setMaximumSize(QSize(90, 110));
        containerQR = new QVBoxLayout(qrContainer);
        containerQR->setSpacing(0);
        containerQR->setObjectName(QString::fromUtf8("containerQR"));
        containerQR->setContentsMargins(5, 10, 5, 0);
        btnQr = new QPushButton(qrContainer);
        btnQr->setObjectName(QString::fromUtf8("btnQr"));
        btnQr->setMinimumSize(QSize(70, 70));
        btnQr->setMaximumSize(QSize(16777215, 70));
        btnQr->setFocusPolicy(Qt::NoFocus);
        btnQr->setIconSize(QSize(70, 70));

        containerQR->addWidget(btnQr);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        containerQR->addItem(verticalSpacer);

        pushButtonQR = new QPushButton(qrContainer);
        pushButtonQR->setObjectName(QString::fromUtf8("pushButtonQR"));
        pushButtonQR->setMinimumSize(QSize(36, 36));
        pushButtonQR->setMaximumSize(QSize(36, 36));
        pushButtonQR->setFocusPolicy(Qt::NoFocus);

        containerQR->addWidget(pushButtonQR, 0, Qt::AlignHCenter|Qt::AlignBottom);


        botton_container->addWidget(qrContainer, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout_11->addWidget(bottom_container);


        verticalLayout_10->addWidget(containerTop);


        retranslateUi(TopBar);

        QMetaObject::connectSlotsByName(TopBar);
    } // setupUi

    void retranslateUi(QWidget *TopBar)
    {
        labelTrans->setText(QCoreApplication::translate("TopBar", "transparent", nullptr));
        typeSpacerTop->setText(QString());
        labelShield->setText(QCoreApplication::translate("TopBar", "shielded", nullptr));
        labelTitle1->setText(QCoreApplication::translate("TopBar", "Available", nullptr));
        labelTitle3->setText(QCoreApplication::translate("TopBar", "Pending", nullptr));
        labelTitle4->setText(QCoreApplication::translate("TopBar", "Immature", nullptr));
        btnQr->setText(QString());
        pushButtonQR->setText(QString());
        (void)TopBar;
    } // retranslateUi

};

namespace Ui {
    class TopBar: public Ui_TopBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPBAR_H
