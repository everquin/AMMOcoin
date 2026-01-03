/********************************************************************************
** Form generated from reading UI file 'coincontroldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COINCONTROLDIALOG_H
#define UI_COINCONTROLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "coincontroltreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_CoinControlDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frameContainer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_4;
    QLabel *labelTitle;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_8;
    QWidget *layoutAmount;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelCoinControlAmountText;
    QLabel *labelCoinControlAmount;
    QPushButton *pushButtonAmount;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutQuantity;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelCoinControlQuantityText;
    QLabel *labelCoinControlQuantity;
    QPushButton *pushButtonQuantity;
    QSpacerItem *horizontalSpacer_22;
    QWidget *layoutFee;
    QHBoxLayout *horizontalLayout_11;
    QLabel *labelCoinControlFeeText;
    QLabel *labelCoinControlFee;
    QPushButton *pushButtonFee;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayoutPanel;
    QPushButton *pushButtonSelectAll;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButtonToggleLock;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *radioTreeMode;
    QRadioButton *radioListMode;
    QLabel *labelLocked;
    QHBoxLayout *horizontalLayout_13;
    CoinControlTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *layoutBytes;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelCoinControlBytesText;
    QLabel *labelCoinControlBytes;
    QPushButton *pushButtonBytes;
    QWidget *layoutDust;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelCoinControlLowOutputText;
    QLabel *labelCoinControlLowOutput;
    QPushButton *pushButtonDust;
    QWidget *layoutChange;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelCoinControlChangeText;
    QLabel *labelCoinControlChange;
    QPushButton *pushButtonChange;
    QWidget *layoutAfter;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelCoinControlAfterFeeText;
    QLabel *labelCoinControlAfterFee;
    QPushButton *pushButtonAlterFee;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonOk;

    void setupUi(QDialog *CoinControlDialog)
    {
        if (CoinControlDialog->objectName().isEmpty())
            CoinControlDialog->setObjectName(QString::fromUtf8("CoinControlDialog"));
        CoinControlDialog->resize(1000, 650);
        CoinControlDialog->setMinimumSize(QSize(950, 650));
        CoinControlDialog->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(CoinControlDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frameContainer = new QFrame(CoinControlDialog);
        frameContainer->setObjectName(QString::fromUtf8("frameContainer"));
        frameContainer->setToolTipDuration(0);
        frameContainer->setFrameShape(QFrame::StyledPanel);
        frameContainer->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frameContainer);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, 0, 20);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(20, -1, 30, -1);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_4);

        labelTitle = new QLabel(frameContainer);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setMinimumSize(QSize(0, 40));
        labelTitle->setMaximumSize(QSize(16777215, 40));
        labelTitle->setAlignment(Qt::AlignCenter);
        labelTitle->setMargin(7);

        horizontalLayout_12->addWidget(labelTitle);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(20, -1, 20, -1);
        layoutAmount = new QWidget(frameContainer);
        layoutAmount->setObjectName(QString::fromUtf8("layoutAmount"));
        horizontalLayout_9 = new QHBoxLayout(layoutAmount);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        labelCoinControlAmountText = new QLabel(layoutAmount);
        labelCoinControlAmountText->setObjectName(QString::fromUtf8("labelCoinControlAmountText"));

        horizontalLayout_9->addWidget(labelCoinControlAmountText);

        labelCoinControlAmount = new QLabel(layoutAmount);
        labelCoinControlAmount->setObjectName(QString::fromUtf8("labelCoinControlAmount"));
        labelCoinControlAmount->setText(QString::fromUtf8("N/A"));

        horizontalLayout_9->addWidget(labelCoinControlAmount);

        pushButtonAmount = new QPushButton(layoutAmount);
        pushButtonAmount->setObjectName(QString::fromUtf8("pushButtonAmount"));
        pushButtonAmount->setMinimumSize(QSize(0, 24));
        pushButtonAmount->setMaximumSize(QSize(24, 26));
        pushButtonAmount->setFocusPolicy(Qt::NoFocus);
        pushButtonAmount->setStyleSheet(QString::fromUtf8("padding-bottom:2px;\n"
"padding-right:4px;"));

        horizontalLayout_9->addWidget(pushButtonAmount, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_9->setStretch(1, 1);

        horizontalLayout_8->addWidget(layoutAmount);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        layoutQuantity = new QWidget(frameContainer);
        layoutQuantity->setObjectName(QString::fromUtf8("layoutQuantity"));
        horizontalLayout_10 = new QHBoxLayout(layoutQuantity);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        labelCoinControlQuantityText = new QLabel(layoutQuantity);
        labelCoinControlQuantityText->setObjectName(QString::fromUtf8("labelCoinControlQuantityText"));

        horizontalLayout_10->addWidget(labelCoinControlQuantityText);

        labelCoinControlQuantity = new QLabel(layoutQuantity);
        labelCoinControlQuantity->setObjectName(QString::fromUtf8("labelCoinControlQuantity"));
        labelCoinControlQuantity->setText(QString::fromUtf8("0"));

        horizontalLayout_10->addWidget(labelCoinControlQuantity);

        pushButtonQuantity = new QPushButton(layoutQuantity);
        pushButtonQuantity->setObjectName(QString::fromUtf8("pushButtonQuantity"));
        pushButtonQuantity->setMinimumSize(QSize(0, 24));
        pushButtonQuantity->setMaximumSize(QSize(24, 26));
        pushButtonQuantity->setFocusPolicy(Qt::NoFocus);
        pushButtonQuantity->setStyleSheet(QString::fromUtf8("padding-bottom:2px;\n"
"               padding-right:4px;"));

        horizontalLayout_10->addWidget(pushButtonQuantity, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_10->setStretch(1, 1);

        horizontalLayout_8->addWidget(layoutQuantity);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_22);

        layoutFee = new QWidget(frameContainer);
        layoutFee->setObjectName(QString::fromUtf8("layoutFee"));
        horizontalLayout_11 = new QHBoxLayout(layoutFee);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        labelCoinControlFeeText = new QLabel(layoutFee);
        labelCoinControlFeeText->setObjectName(QString::fromUtf8("labelCoinControlFeeText"));

        horizontalLayout_11->addWidget(labelCoinControlFeeText);

        labelCoinControlFee = new QLabel(layoutFee);
        labelCoinControlFee->setObjectName(QString::fromUtf8("labelCoinControlFee"));

        horizontalLayout_11->addWidget(labelCoinControlFee);

        pushButtonFee = new QPushButton(layoutFee);
        pushButtonFee->setObjectName(QString::fromUtf8("pushButtonFee"));
        pushButtonFee->setMinimumSize(QSize(0, 24));
        pushButtonFee->setMaximumSize(QSize(24, 26));
        pushButtonFee->setFocusPolicy(Qt::NoFocus);
        pushButtonFee->setStyleSheet(QString::fromUtf8("padding-bottom:2px;\n"
"               padding-right:4px;"));

        horizontalLayout_11->addWidget(pushButtonFee, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_11->setStretch(1, 1);

        horizontalLayout_8->addWidget(layoutFee);


        verticalLayout_2->addLayout(horizontalLayout_8);

        frame = new QFrame(frameContainer);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 40));
        frame->setStyleSheet(QString::fromUtf8("#frame {\n"
"	border:0;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 0, 20, 0);
        horizontalLayoutPanel = new QHBoxLayout();
        horizontalLayoutPanel->setSpacing(20);
        horizontalLayoutPanel->setObjectName(QString::fromUtf8("horizontalLayoutPanel"));
        pushButtonSelectAll = new QPushButton(frame);
        pushButtonSelectAll->setObjectName(QString::fromUtf8("pushButtonSelectAll"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonSelectAll->sizePolicy().hasHeightForWidth());
        pushButtonSelectAll->setSizePolicy(sizePolicy);
        pushButtonSelectAll->setMinimumSize(QSize(160, 40));
        pushButtonSelectAll->setMaximumSize(QSize(16777215, 40));
        pushButtonSelectAll->setCheckable(true);
        pushButtonSelectAll->setChecked(false);
        pushButtonSelectAll->setAutoExclusive(false);
        pushButtonSelectAll->setAutoDefault(false);

        horizontalLayoutPanel->addWidget(pushButtonSelectAll);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayoutPanel->addItem(horizontalSpacer_6);

        pushButtonToggleLock = new QPushButton(frame);
        pushButtonToggleLock->setObjectName(QString::fromUtf8("pushButtonToggleLock"));
        sizePolicy.setHeightForWidth(pushButtonToggleLock->sizePolicy().hasHeightForWidth());
        pushButtonToggleLock->setSizePolicy(sizePolicy);
        pushButtonToggleLock->setMinimumSize(QSize(160, 40));
        pushButtonToggleLock->setMaximumSize(QSize(16777215, 40));
        pushButtonToggleLock->setCheckable(true);
        pushButtonToggleLock->setAutoExclusive(false);
        pushButtonToggleLock->setAutoDefault(false);

        horizontalLayoutPanel->addWidget(pushButtonToggleLock);

        horizontalSpacer_7 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutPanel->addItem(horizontalSpacer_7);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("#groupBox_2 {\n"
"    background-color:transparent;\n"
"    border-radius:0;\n"
"}"));
        horizontalLayout_14 = new QHBoxLayout(groupBox_2);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        radioTreeMode = new QRadioButton(groupBox_2);
        radioTreeMode->setObjectName(QString::fromUtf8("radioTreeMode"));
        sizePolicy.setHeightForWidth(radioTreeMode->sizePolicy().hasHeightForWidth());
        radioTreeMode->setSizePolicy(sizePolicy);

        horizontalLayout_14->addWidget(radioTreeMode);

        radioListMode = new QRadioButton(groupBox_2);
        radioListMode->setObjectName(QString::fromUtf8("radioListMode"));
        sizePolicy.setHeightForWidth(radioListMode->sizePolicy().hasHeightForWidth());
        radioListMode->setSizePolicy(sizePolicy);
        radioListMode->setChecked(false);

        horizontalLayout_14->addWidget(radioListMode);


        horizontalLayoutPanel->addWidget(groupBox_2, 0, Qt::AlignRight);

        labelLocked = new QLabel(frame);
        labelLocked->setObjectName(QString::fromUtf8("labelLocked"));

        horizontalLayoutPanel->addWidget(labelLocked);


        horizontalLayout->addLayout(horizontalLayoutPanel);


        verticalLayout_2->addWidget(frame);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(20, -1, 20, -1);
        treeWidget = new CoinControlTreeWidget(frameContainer);
        treeWidget->headerItem()->setText(0, QString());
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget->setStyleSheet(QString::fromUtf8(""));
        treeWidget->setSortingEnabled(false);
        treeWidget->setColumnCount(6);
        treeWidget->header()->setProperty("showSortIndicator", QVariant(true));
        treeWidget->header()->setStretchLastSection(false);

        horizontalLayout_13->addWidget(treeWidget);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(20);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, -1, 20, -1);
        layoutBytes = new QWidget(frameContainer);
        layoutBytes->setObjectName(QString::fromUtf8("layoutBytes"));
        horizontalLayout_4 = new QHBoxLayout(layoutBytes);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelCoinControlBytesText = new QLabel(layoutBytes);
        labelCoinControlBytesText->setObjectName(QString::fromUtf8("labelCoinControlBytesText"));

        horizontalLayout_4->addWidget(labelCoinControlBytesText);

        labelCoinControlBytes = new QLabel(layoutBytes);
        labelCoinControlBytes->setObjectName(QString::fromUtf8("labelCoinControlBytes"));
        labelCoinControlBytes->setText(QString::fromUtf8("0"));

        horizontalLayout_4->addWidget(labelCoinControlBytes);

        pushButtonBytes = new QPushButton(layoutBytes);
        pushButtonBytes->setObjectName(QString::fromUtf8("pushButtonBytes"));
        pushButtonBytes->setMinimumSize(QSize(0, 24));
        pushButtonBytes->setMaximumSize(QSize(24, 26));
        pushButtonBytes->setFocusPolicy(Qt::NoFocus);
        pushButtonBytes->setStyleSheet(QString::fromUtf8("padding-bottom:2px;\n"
"               padding-right:4px;"));

        horizontalLayout_4->addWidget(pushButtonBytes, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_4->setStretch(1, 1);

        horizontalLayout_3->addWidget(layoutBytes);

        layoutDust = new QWidget(frameContainer);
        layoutDust->setObjectName(QString::fromUtf8("layoutDust"));
        horizontalLayout_5 = new QHBoxLayout(layoutDust);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelCoinControlLowOutputText = new QLabel(layoutDust);
        labelCoinControlLowOutputText->setObjectName(QString::fromUtf8("labelCoinControlLowOutputText"));

        horizontalLayout_5->addWidget(labelCoinControlLowOutputText);

        labelCoinControlLowOutput = new QLabel(layoutDust);
        labelCoinControlLowOutput->setObjectName(QString::fromUtf8("labelCoinControlLowOutput"));

        horizontalLayout_5->addWidget(labelCoinControlLowOutput);

        pushButtonDust = new QPushButton(layoutDust);
        pushButtonDust->setObjectName(QString::fromUtf8("pushButtonDust"));
        pushButtonDust->setMinimumSize(QSize(0, 24));
        pushButtonDust->setMaximumSize(QSize(24, 26));
        pushButtonDust->setFocusPolicy(Qt::NoFocus);
        pushButtonDust->setStyleSheet(QString::fromUtf8("padding-bottom:2px;\n"
"               padding-right:4px;"));

        horizontalLayout_5->addWidget(pushButtonDust, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_5->setStretch(1, 1);

        horizontalLayout_3->addWidget(layoutDust);

        layoutChange = new QWidget(frameContainer);
        layoutChange->setObjectName(QString::fromUtf8("layoutChange"));
        horizontalLayout_6 = new QHBoxLayout(layoutChange);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelCoinControlChangeText = new QLabel(layoutChange);
        labelCoinControlChangeText->setObjectName(QString::fromUtf8("labelCoinControlChangeText"));

        horizontalLayout_6->addWidget(labelCoinControlChangeText);

        labelCoinControlChange = new QLabel(layoutChange);
        labelCoinControlChange->setObjectName(QString::fromUtf8("labelCoinControlChange"));
        labelCoinControlChange->setText(QString::fromUtf8("0"));

        horizontalLayout_6->addWidget(labelCoinControlChange);

        pushButtonChange = new QPushButton(layoutChange);
        pushButtonChange->setObjectName(QString::fromUtf8("pushButtonChange"));
        pushButtonChange->setMinimumSize(QSize(0, 24));
        pushButtonChange->setMaximumSize(QSize(24, 26));
        pushButtonChange->setFocusPolicy(Qt::NoFocus);
        pushButtonChange->setStyleSheet(QString::fromUtf8("padding-bottom:2px;\n"
"               padding-right:4px;"));

        horizontalLayout_6->addWidget(pushButtonChange, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_6->setStretch(1, 1);

        horizontalLayout_3->addWidget(layoutChange);

        layoutAfter = new QWidget(frameContainer);
        layoutAfter->setObjectName(QString::fromUtf8("layoutAfter"));
        horizontalLayout_7 = new QHBoxLayout(layoutAfter);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        labelCoinControlAfterFeeText = new QLabel(layoutAfter);
        labelCoinControlAfterFeeText->setObjectName(QString::fromUtf8("labelCoinControlAfterFeeText"));

        horizontalLayout_7->addWidget(labelCoinControlAfterFeeText);

        labelCoinControlAfterFee = new QLabel(layoutAfter);
        labelCoinControlAfterFee->setObjectName(QString::fromUtf8("labelCoinControlAfterFee"));

        horizontalLayout_7->addWidget(labelCoinControlAfterFee);

        pushButtonAlterFee = new QPushButton(layoutAfter);
        pushButtonAlterFee->setObjectName(QString::fromUtf8("pushButtonAlterFee"));
        pushButtonAlterFee->setMinimumSize(QSize(0, 24));
        pushButtonAlterFee->setMaximumSize(QSize(24, 26));
        pushButtonAlterFee->setFocusPolicy(Qt::NoFocus);
        pushButtonAlterFee->setStyleSheet(QString::fromUtf8("padding-bottom:2px;\n"
"               padding-right:4px;"));

        horizontalLayout_7->addWidget(pushButtonAlterFee, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_7->setStretch(1, 1);

        horizontalLayout_3->addWidget(layoutAfter);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, -1, 26, -1);
        horizontalSpacer_3 = new QSpacerItem(558, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButtonOk = new QPushButton(frameContainer);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        pushButtonOk->setMinimumSize(QSize(150, 35));

        horizontalLayout_2->addWidget(pushButtonOk);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(frameContainer);


        retranslateUi(CoinControlDialog);

        QMetaObject::connectSlotsByName(CoinControlDialog);
    } // setupUi

    void retranslateUi(QDialog *CoinControlDialog)
    {
        CoinControlDialog->setWindowTitle(QCoreApplication::translate("CoinControlDialog", "Coin Selection", nullptr));
        labelTitle->setText(QCoreApplication::translate("CoinControlDialog", "Select PIV Outputs to Spend", nullptr));
        labelCoinControlAmountText->setText(QCoreApplication::translate("CoinControlDialog", "Amount", nullptr));
        pushButtonAmount->setText(QString());
        labelCoinControlQuantityText->setText(QCoreApplication::translate("CoinControlDialog", "Quantity:", nullptr));
        pushButtonQuantity->setText(QString());
        labelCoinControlFeeText->setText(QCoreApplication::translate("CoinControlDialog", "Fee:", nullptr));
        labelCoinControlFee->setText(QCoreApplication::translate("CoinControlDialog", "0.00 PIV", nullptr));
        pushButtonFee->setText(QString());
        pushButtonSelectAll->setText(QCoreApplication::translate("CoinControlDialog", "Select all", nullptr));
        pushButtonToggleLock->setText(QCoreApplication::translate("CoinControlDialog", "Toggle lock state", nullptr));
        groupBox_2->setTitle(QString());
        radioTreeMode->setText(QCoreApplication::translate("CoinControlDialog", "Tree mode", nullptr));
        radioListMode->setText(QCoreApplication::translate("CoinControlDialog", "List mode", nullptr));
        labelLocked->setText(QCoreApplication::translate("CoinControlDialog", "(1 locked)", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(5, QCoreApplication::translate("CoinControlDialog", "Confirmations", nullptr));
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("CoinControlDialog", "Date", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("CoinControlDialog", "Received with address", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("CoinControlDialog", "Received with label", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("CoinControlDialog", "Amount", nullptr));
#if QT_CONFIG(tooltip)
        ___qtreewidgetitem->setToolTip(5, QCoreApplication::translate("CoinControlDialog", "Confirmed", nullptr));
#endif // QT_CONFIG(tooltip)
        labelCoinControlBytesText->setText(QCoreApplication::translate("CoinControlDialog", "Bytes:", nullptr));
        pushButtonBytes->setText(QString());
        labelCoinControlLowOutputText->setText(QCoreApplication::translate("CoinControlDialog", "Dust:", nullptr));
        labelCoinControlLowOutput->setText(QCoreApplication::translate("CoinControlDialog", "no", nullptr));
        pushButtonDust->setText(QString());
        labelCoinControlChangeText->setText(QCoreApplication::translate("CoinControlDialog", "Change:", nullptr));
        pushButtonChange->setText(QString());
        labelCoinControlAfterFeeText->setText(QCoreApplication::translate("CoinControlDialog", "After Fee: ", nullptr));
        labelCoinControlAfterFee->setText(QCoreApplication::translate("CoinControlDialog", "0.00 PIV", nullptr));
        pushButtonAlterFee->setText(QString());
        pushButtonOk->setText(QCoreApplication::translate("CoinControlDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CoinControlDialog: public Ui_CoinControlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COINCONTROLDIALOG_H
