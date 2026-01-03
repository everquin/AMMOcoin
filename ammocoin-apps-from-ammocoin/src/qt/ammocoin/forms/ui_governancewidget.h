/********************************************************************************
** Form generated from reading UI file 'governancewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOVERNANCEWIDGET_H
#define UI_GOVERNANCEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qt/ammocoin/optionbutton.h"

QT_BEGIN_NAMESPACE

class Ui_governancewidget
{
public:
    QHBoxLayout *horizontalLayout_1;
    QWidget *left;
    QVBoxLayout *verticalLayout_1;
    QWidget *containerTitles;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTitle;
    QLabel *labelSubtitle1;
    QSpacerItem *horizontalSpacer;
    QWidget *containerSort;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBoxSort;
    QWidget *containerFilter;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBoxFilter;
    QWidget *layoutWarning;
    QVBoxLayout *verticalLayout_3;
    QWidget *containerWarning;
    QVBoxLayout *verticalLayout_4;
    QFrame *frameWarning;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *imgWarning;
    QLabel *lblWarning;
    QWidget *mainContainer;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *emptyContainer;
    QVBoxLayout *verticalLayout_6;
    QFrame *emptyScreen;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pushImgEmpty;
    QLabel *labelEmpty;
    QWidget *right;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_9;
    OptionButton *btnCreateProposal;
    QSpacerItem *verticalSpacer_1;
    QWidget *containerBudget;
    QVBoxLayout *verticalLayout_10;
    QLabel *labelBudget;
    QLabel *labelBudgetSubTitle;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_11;
    QLabel *labelAvailableTitle;
    QLabel *labelAvailableAmount;
    QSpacerItem *verticalSpacer_3;
    QWidget *line;
    QSpacerItem *verticalSpacer_4;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_12;
    QLabel *labelAllocatedTitle;
    QLabel *labelAllocatedAmount;
    QSpacerItem *verticalSpacer_5;
    QWidget *line2;
    QSpacerItem *verticalSpacer_6;
    QWidget *containerSuperblockInfo;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *iconClock;
    QLabel *labelNextSuperblock;

    void setupUi(QWidget *governancewidget)
    {
        if (governancewidget->objectName().isEmpty())
            governancewidget->setObjectName(QString::fromUtf8("governancewidget"));
        governancewidget->resize(629, 406);
        governancewidget->setMinimumSize(QSize(0, 150));
        governancewidget->setWindowTitle(QString::fromUtf8("N/A"));
        horizontalLayout_1 = new QHBoxLayout(governancewidget);
        horizontalLayout_1->setSpacing(0);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
        left = new QWidget(governancewidget);
        left->setObjectName(QString::fromUtf8("left"));
        verticalLayout_1 = new QVBoxLayout(left);
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        verticalLayout_1->setContentsMargins(0, 0, 0, 0);
        containerTitles = new QWidget(left);
        containerTitles->setObjectName(QString::fromUtf8("containerTitles"));
        containerTitles->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_2 = new QHBoxLayout(containerTitles);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelTitle = new QLabel(containerTitles);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setText(QString::fromUtf8("N/A"));

        verticalLayout_2->addWidget(labelTitle);

        labelSubtitle1 = new QLabel(containerTitles);
        labelSubtitle1->setObjectName(QString::fromUtf8("labelSubtitle1"));
        labelSubtitle1->setText(QString::fromUtf8("N/A"));

        verticalLayout_2->addWidget(labelSubtitle1, 0, Qt::AlignTop);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        containerSort = new QWidget(containerTitles);
        containerSort->setObjectName(QString::fromUtf8("containerSort"));
        containerSort->setMinimumSize(QSize(0, 0));
        horizontalLayout_3 = new QHBoxLayout(containerSort);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, -1, -1);
        comboBoxSort = new QComboBox(containerSort);
        comboBoxSort->setObjectName(QString::fromUtf8("comboBoxSort"));
        comboBoxSort->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(comboBoxSort);


        horizontalLayout_2->addWidget(containerSort);

        containerFilter = new QWidget(containerTitles);
        containerFilter->setObjectName(QString::fromUtf8("containerFilter"));
        containerFilter->setMinimumSize(QSize(0, 0));
        horizontalLayout_4 = new QHBoxLayout(containerFilter);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, -1, -1);
        comboBoxFilter = new QComboBox(containerFilter);
        comboBoxFilter->setObjectName(QString::fromUtf8("comboBoxFilter"));
        comboBoxFilter->setMinimumSize(QSize(115, 0));
        comboBoxFilter->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        comboBoxFilter->setMinimumContentsLength(15);

        horizontalLayout_4->addWidget(comboBoxFilter);


        horizontalLayout_2->addWidget(containerFilter);


        verticalLayout_1->addWidget(containerTitles);

        layoutWarning = new QWidget(left);
        layoutWarning->setObjectName(QString::fromUtf8("layoutWarning"));
        layoutWarning->setMaximumSize(QSize(16777215, 40));
        verticalLayout_3 = new QVBoxLayout(layoutWarning);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        containerWarning = new QWidget(layoutWarning);
        containerWarning->setObjectName(QString::fromUtf8("containerWarning"));
        verticalLayout_4 = new QVBoxLayout(containerWarning);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(18, 6, 20, 0);
        frameWarning = new QFrame(containerWarning);
        frameWarning->setObjectName(QString::fromUtf8("frameWarning"));
        frameWarning->setStyleSheet(QString::fromUtf8("border:none;"));
        frameWarning->setFrameShape(QFrame::StyledPanel);
        frameWarning->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frameWarning);
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        imgWarning = new QPushButton(frameWarning);
        imgWarning->setObjectName(QString::fromUtf8("imgWarning"));
        imgWarning->setStyleSheet(QString::fromUtf8("border:none;"));
        imgWarning->setIconSize(QSize(24, 24));

        horizontalLayout_5->addWidget(imgWarning, 0, Qt::AlignVCenter);

        lblWarning = new QLabel(frameWarning);
        lblWarning->setObjectName(QString::fromUtf8("lblWarning"));
        lblWarning->setStyleSheet(QString::fromUtf8(""));
        lblWarning->setText(QString::fromUtf8("N/A"));
        lblWarning->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        horizontalLayout_5->addWidget(lblWarning, 0, Qt::AlignVCenter);

        horizontalLayout_5->setStretch(1, 2);

        verticalLayout_4->addWidget(frameWarning);


        verticalLayout_3->addWidget(containerWarning);


        verticalLayout_1->addWidget(layoutWarning);

        mainContainer = new QWidget(left);
        mainContainer->setObjectName(QString::fromUtf8("mainContainer"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainContainer->sizePolicy().hasHeightForWidth());
        mainContainer->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(mainContainer);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(mainContainer);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 417, 157));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_5->addWidget(scrollArea);


        verticalLayout_1->addWidget(mainContainer);

        emptyContainer = new QFrame(left);
        emptyContainer->setObjectName(QString::fromUtf8("emptyContainer"));
        sizePolicy.setHeightForWidth(emptyContainer->sizePolicy().hasHeightForWidth());
        emptyContainer->setSizePolicy(sizePolicy);
        emptyContainer->setMinimumSize(QSize(0, 100));
        emptyContainer->setStyleSheet(QString::fromUtf8("margin-bottom:12px;"));
        emptyContainer->setFrameShape(QFrame::StyledPanel);
        emptyContainer->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(emptyContainer);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        emptyScreen = new QFrame(emptyContainer);
        emptyScreen->setObjectName(QString::fromUtf8("emptyScreen"));
        sizePolicy.setHeightForWidth(emptyScreen->sizePolicy().hasHeightForWidth());
        emptyScreen->setSizePolicy(sizePolicy);
        emptyScreen->setFrameShape(QFrame::StyledPanel);
        emptyScreen->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(emptyScreen);
        verticalLayout_7->setSpacing(12);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        pushImgEmpty = new QPushButton(emptyScreen);
        pushImgEmpty->setObjectName(QString::fromUtf8("pushImgEmpty"));
        pushImgEmpty->setMinimumSize(QSize(100, 100));
        pushImgEmpty->setMaximumSize(QSize(100, 100));
        pushImgEmpty->setIconSize(QSize(100, 100));

        verticalLayout_7->addWidget(pushImgEmpty, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        labelEmpty = new QLabel(emptyScreen);
        labelEmpty->setObjectName(QString::fromUtf8("labelEmpty"));
        labelEmpty->setStyleSheet(QString::fromUtf8(""));
        labelEmpty->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(labelEmpty, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout_6->addWidget(emptyScreen, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        verticalLayout_6->setStretch(0, 8);

        verticalLayout_1->addWidget(emptyContainer, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        verticalLayout_1->setStretch(2, 1);

        horizontalLayout_1->addWidget(left);

        right = new QWidget(governancewidget);
        right->setObjectName(QString::fromUtf8("right"));
        verticalLayout_8 = new QVBoxLayout(right);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        btnCreateProposal = new OptionButton(right);
        btnCreateProposal->setObjectName(QString::fromUtf8("btnCreateProposal"));
        btnCreateProposal->setMinimumSize(QSize(0, 60));

        verticalLayout_9->addWidget(btnCreateProposal);

        verticalSpacer_1 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_9->addItem(verticalSpacer_1);

        containerBudget = new QWidget(right);
        containerBudget->setObjectName(QString::fromUtf8("containerBudget"));
        containerBudget->setMinimumSize(QSize(0, 200));
        verticalLayout_10 = new QVBoxLayout(containerBudget);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, -1, 0, 0);
        labelBudget = new QLabel(containerBudget);
        labelBudget->setObjectName(QString::fromUtf8("labelBudget"));

        verticalLayout_10->addWidget(labelBudget);

        labelBudgetSubTitle = new QLabel(containerBudget);
        labelBudgetSubTitle->setObjectName(QString::fromUtf8("labelBudgetSubTitle"));
        labelBudgetSubTitle->setWordWrap(true);

        verticalLayout_10->addWidget(labelBudgetSubTitle);

        verticalSpacer_2 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_2);

        widget = new QWidget(containerBudget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_11 = new QVBoxLayout(widget);
        verticalLayout_11->setSpacing(3);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        labelAvailableTitle = new QLabel(widget);
        labelAvailableTitle->setObjectName(QString::fromUtf8("labelAvailableTitle"));

        verticalLayout_11->addWidget(labelAvailableTitle, 0, Qt::AlignBottom);

        labelAvailableAmount = new QLabel(widget);
        labelAvailableAmount->setObjectName(QString::fromUtf8("labelAvailableAmount"));
        labelAvailableAmount->setText(QString::fromUtf8("N/A"));

        verticalLayout_11->addWidget(labelAvailableAmount);

        verticalSpacer_3 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_11->addItem(verticalSpacer_3);

        line = new QWidget(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMinimumSize(QSize(0, 1));
        line->setMaximumSize(QSize(16777215, 1));
        line->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_11->addWidget(line);


        verticalLayout_10->addWidget(widget);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_4);

        widget_2 = new QWidget(containerBudget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_12 = new QVBoxLayout(widget_2);
        verticalLayout_12->setSpacing(3);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        labelAllocatedTitle = new QLabel(widget_2);
        labelAllocatedTitle->setObjectName(QString::fromUtf8("labelAllocatedTitle"));

        verticalLayout_12->addWidget(labelAllocatedTitle, 0, Qt::AlignBottom);

        labelAllocatedAmount = new QLabel(widget_2);
        labelAllocatedAmount->setObjectName(QString::fromUtf8("labelAllocatedAmount"));
        labelAllocatedAmount->setText(QString::fromUtf8("N/A"));

        verticalLayout_12->addWidget(labelAllocatedAmount);

        verticalSpacer_5 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_12->addItem(verticalSpacer_5);

        line2 = new QWidget(widget_2);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setMinimumSize(QSize(0, 1));
        line2->setMaximumSize(QSize(16777215, 1));
        line2->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_12->addWidget(line2);


        verticalLayout_10->addWidget(widget_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_6);

        containerSuperblockInfo = new QWidget(containerBudget);
        containerSuperblockInfo->setObjectName(QString::fromUtf8("containerSuperblockInfo"));
        horizontalLayout_6 = new QHBoxLayout(containerSuperblockInfo);
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        iconClock = new QPushButton(containerSuperblockInfo);
        iconClock->setObjectName(QString::fromUtf8("iconClock"));
        iconClock->setMinimumSize(QSize(26, 26));
        iconClock->setMaximumSize(QSize(26, 26));
        iconClock->setIconSize(QSize(26, 26));

        horizontalLayout_6->addWidget(iconClock, 0, Qt::AlignTop);

        labelNextSuperblock = new QLabel(containerSuperblockInfo);
        labelNextSuperblock->setObjectName(QString::fromUtf8("labelNextSuperblock"));
        labelNextSuperblock->setText(QString::fromUtf8("Next superblock unknown. Wait until the node is fully sync."));
        labelNextSuperblock->setWordWrap(true);

        horizontalLayout_6->addWidget(labelNextSuperblock);


        verticalLayout_10->addWidget(containerSuperblockInfo);


        verticalLayout_9->addWidget(containerBudget);


        verticalLayout_8->addLayout(verticalLayout_9);


        horizontalLayout_1->addWidget(right);

        horizontalLayout_1->setStretch(0, 2);
        horizontalLayout_1->setStretch(1, 1);

        retranslateUi(governancewidget);

        QMetaObject::connectSlotsByName(governancewidget);
    } // setupUi

    void retranslateUi(QWidget *governancewidget)
    {
        imgWarning->setText(QString());
        pushImgEmpty->setText(QString());
        labelEmpty->setText(QCoreApplication::translate("governancewidget", "No active proposals yet", nullptr));
        labelBudget->setText(QCoreApplication::translate("governancewidget", "Budget Distribution", nullptr));
        labelBudgetSubTitle->setText(QCoreApplication::translate("governancewidget", "Funds accessible for the proposals' implementation", nullptr));
        labelAvailableTitle->setText(QCoreApplication::translate("governancewidget", "Available", nullptr));
        labelAllocatedTitle->setText(QCoreApplication::translate("governancewidget", "Allocated", nullptr));
        iconClock->setText(QString());
        (void)governancewidget;
    } // retranslateUi

};

namespace Ui {
    class governancewidget: public Ui_governancewidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOVERNANCEWIDGET_H
