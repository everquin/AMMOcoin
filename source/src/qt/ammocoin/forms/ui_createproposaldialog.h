/********************************************************************************
** Form generated from reading UI file 'createproposaldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPROPOSALDIALOG_H
#define UI_CREATEPROPOSALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateProposalDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer1;
    QPushButton *pushButtonSkip;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_7;
    QStackedWidget *stackedIcon1;
    QWidget *page;
    QVBoxLayout *layoutIcon1;
    QPushButton *pushNumber1;
    QWidget *page_5;
    QLabel *labelLine1;
    QStackedWidget *stackedIcon2;
    QWidget *pageIcon2;
    QVBoxLayout *layoutIcon2;
    QPushButton *pushNumber2;
    QWidget *page_6;
    QLabel *labelLine2;
    QStackedWidget *stackedIcon3;
    QWidget *pageIcon3;
    QVBoxLayout *layoutIcon3;
    QPushButton *pushNumber3;
    QWidget *page_7;
    QSpacerItem *horizontalSpacer_8;
    QWidget *groupContainer;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBoxName;
    QHBoxLayout *horizontalgroup;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushName1;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushName2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushName3;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_11;
    QLabel *labelTitle1;
    QLabel *labelMessage1b;
    QWidget *widget;
    QVBoxLayout *verticalLayout_91;
    QVBoxLayout *verticalLayout_41;
    QLabel *labelName;
    QLineEdit *lineEditPropName;
    QVBoxLayout *verticalLayout_31;
    QLabel *labelURL;
    QLineEdit *lineEditURL;
    QSpacerItem *verticalSpacer_7;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *containerPage2;
    QVBoxLayout *verticalLayout_51;
    QWidget *widget_61;
    QVBoxLayout *verticalLayout_151;
    QLabel *labelTitleDest;
    QLabel *labelMessageDest;
    QWidget *widget33;
    QVBoxLayout *verticalLayout_92;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelAddress;
    QLineEdit *lineEditAddress;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_32;
    QLabel *labelAmount;
    QLineEdit *lineEditAmount;
    QVBoxLayout *verticalLayout_161;
    QLabel *labelMonths;
    QSpinBox *lineEditMonths;
    QSpacerItem *verticalSpacer_4;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_15;
    QLabel *labelTitle3;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget39;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_17;
    QVBoxLayout *verticalLayout_33;
    QLabel *labelResultNameTitle;
    QLabel *labelResultName;
    QVBoxLayout *verticalLayout_162;
    QLabel *labelResultAmountTitle;
    QLabel *labelResultAmount;
    QHBoxLayout *horizontalLayout_19;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelResultAddressTitle;
    QLabel *labelResultAddress;
    QVBoxLayout *verticalLayout_16;
    QLabel *labelResultMonthsTitle;
    QLabel *labelResultMonths;
    QVBoxLayout *verticalLayout_42;
    QLabel *labelResultUrlTitle;
    QLabel *labelResultUrl;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout1;
    QPushButton *btnGenAddr;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnBack;
    QPushButton *btnNext;

    void setupUi(QDialog *CreateProposalDialog)
    {
        if (CreateProposalDialog->objectName().isEmpty())
            CreateProposalDialog->setObjectName(QString::fromUtf8("CreateProposalDialog"));
        CreateProposalDialog->resize(715, 602);
        CreateProposalDialog->setWindowTitle(QString::fromUtf8("N/A"));
        verticalLayout = new QVBoxLayout(CreateProposalDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(CreateProposalDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 20, -1, 20);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 20, -1);
        horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer1);

        pushButtonSkip = new QPushButton(frame);
        pushButtonSkip->setObjectName(QString::fromUtf8("pushButtonSkip"));
        pushButtonSkip->setMinimumSize(QSize(20, 20));
        pushButtonSkip->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(pushButtonSkip);


        verticalLayout_6->addLayout(horizontalLayout_2);

        widget_2 = new QWidget(frame);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 24));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_7 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        stackedIcon1 = new QStackedWidget(widget_2);
        stackedIcon1->setObjectName(QString::fromUtf8("stackedIcon1"));
        stackedIcon1->setMinimumSize(QSize(22, 22));
        stackedIcon1->setMaximumSize(QSize(22, 22));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setMinimumSize(QSize(22, 22));
        page->setMaximumSize(QSize(22, 22));
        layoutIcon1 = new QVBoxLayout(page);
        layoutIcon1->setSpacing(0);
        layoutIcon1->setObjectName(QString::fromUtf8("layoutIcon1"));
        layoutIcon1->setContentsMargins(0, 0, 0, 0);
        pushNumber1 = new QPushButton(page);
        pushNumber1->setObjectName(QString::fromUtf8("pushNumber1"));
        pushNumber1->setEnabled(false);
        pushNumber1->setMinimumSize(QSize(22, 22));
        pushNumber1->setMaximumSize(QSize(22, 22));
        pushNumber1->setText(QString::fromUtf8("1"));
        pushNumber1->setCheckable(true);
        pushNumber1->setChecked(true);
        pushNumber1->setAutoExclusive(true);

        layoutIcon1->addWidget(pushNumber1, 0, Qt::AlignVCenter);

        stackedIcon1->addWidget(page);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        stackedIcon1->addWidget(page_5);

        horizontalLayout->addWidget(stackedIcon1);

        labelLine1 = new QLabel(widget_2);
        labelLine1->setObjectName(QString::fromUtf8("labelLine1"));
        labelLine1->setMinimumSize(QSize(0, 1));
        labelLine1->setMaximumSize(QSize(16777215, 1));
        labelLine1->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(labelLine1, 0, Qt::AlignVCenter);

        stackedIcon2 = new QStackedWidget(widget_2);
        stackedIcon2->setObjectName(QString::fromUtf8("stackedIcon2"));
        stackedIcon2->setMinimumSize(QSize(22, 22));
        stackedIcon2->setMaximumSize(QSize(22, 22));
        pageIcon2 = new QWidget();
        pageIcon2->setObjectName(QString::fromUtf8("pageIcon2"));
        pageIcon2->setMinimumSize(QSize(22, 22));
        pageIcon2->setMaximumSize(QSize(22, 22));
        layoutIcon2 = new QVBoxLayout(pageIcon2);
        layoutIcon2->setSpacing(0);
        layoutIcon2->setObjectName(QString::fromUtf8("layoutIcon2"));
        layoutIcon2->setContentsMargins(0, 0, 0, 0);
        pushNumber2 = new QPushButton(pageIcon2);
        pushNumber2->setObjectName(QString::fromUtf8("pushNumber2"));
        pushNumber2->setEnabled(false);
        pushNumber2->setMinimumSize(QSize(22, 22));
        pushNumber2->setMaximumSize(QSize(22, 22));
        pushNumber2->setText(QString::fromUtf8("2"));
        pushNumber2->setCheckable(true);
        pushNumber2->setChecked(false);
        pushNumber2->setAutoExclusive(true);

        layoutIcon2->addWidget(pushNumber2, 0, Qt::AlignVCenter);

        stackedIcon2->addWidget(pageIcon2);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        stackedIcon2->addWidget(page_6);

        horizontalLayout->addWidget(stackedIcon2);

        labelLine2 = new QLabel(widget_2);
        labelLine2->setObjectName(QString::fromUtf8("labelLine2"));
        labelLine2->setMinimumSize(QSize(0, 1));
        labelLine2->setMaximumSize(QSize(16777215, 1));
        labelLine2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(labelLine2);

        stackedIcon3 = new QStackedWidget(widget_2);
        stackedIcon3->setObjectName(QString::fromUtf8("stackedIcon3"));
        stackedIcon3->setMinimumSize(QSize(22, 22));
        stackedIcon3->setMaximumSize(QSize(22, 22));
        pageIcon3 = new QWidget();
        pageIcon3->setObjectName(QString::fromUtf8("pageIcon3"));
        pageIcon3->setMinimumSize(QSize(22, 22));
        pageIcon3->setMaximumSize(QSize(22, 22));
        layoutIcon3 = new QVBoxLayout(pageIcon3);
        layoutIcon3->setSpacing(0);
        layoutIcon3->setObjectName(QString::fromUtf8("layoutIcon3"));
        layoutIcon3->setContentsMargins(0, 0, 0, 0);
        pushNumber3 = new QPushButton(pageIcon3);
        pushNumber3->setObjectName(QString::fromUtf8("pushNumber3"));
        pushNumber3->setEnabled(false);
        pushNumber3->setMinimumSize(QSize(22, 22));
        pushNumber3->setMaximumSize(QSize(22, 22));
        pushNumber3->setText(QString::fromUtf8("3"));
        pushNumber3->setCheckable(true);
        pushNumber3->setChecked(false);
        pushNumber3->setAutoExclusive(true);

        layoutIcon3->addWidget(pushNumber3, 0, Qt::AlignVCenter);

        stackedIcon3->addWidget(pageIcon3);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        stackedIcon3->addWidget(page_7);

        horizontalLayout->addWidget(stackedIcon3);

        horizontalSpacer_8 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);


        verticalLayout_6->addWidget(widget_2);

        groupContainer = new QWidget(frame);
        groupContainer->setObjectName(QString::fromUtf8("groupContainer"));
        groupContainer->setAutoFillBackground(true);
        horizontalLayout_3 = new QHBoxLayout(groupContainer);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBoxName = new QGroupBox(groupContainer);
        groupBoxName->setObjectName(QString::fromUtf8("groupBoxName"));
        groupBoxName->setAutoFillBackground(true);
        horizontalgroup = new QHBoxLayout(groupBoxName);
        horizontalgroup->setSpacing(0);
        horizontalgroup->setObjectName(QString::fromUtf8("horizontalgroup"));
        horizontalgroup->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalgroup->addItem(horizontalSpacer_9);

        pushName1 = new QPushButton(groupBoxName);
        pushName1->setObjectName(QString::fromUtf8("pushName1"));
        pushName1->setEnabled(false);
        pushName1->setMinimumSize(QSize(100, 0));
        pushName1->setMaximumSize(QSize(80, 16777215));
        pushName1->setCheckable(true);
        pushName1->setChecked(true);
        pushName1->setAutoExclusive(false);

        horizontalgroup->addWidget(pushName1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalgroup->addItem(horizontalSpacer_4);

        pushName2 = new QPushButton(groupBoxName);
        pushName2->setObjectName(QString::fromUtf8("pushName2"));
        pushName2->setEnabled(false);
        pushName2->setMinimumSize(QSize(100, 0));
        pushName2->setMaximumSize(QSize(80, 16777215));
        pushName2->setCheckable(true);
        pushName2->setAutoExclusive(false);

        horizontalgroup->addWidget(pushName2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalgroup->addItem(horizontalSpacer_3);

        pushName3 = new QPushButton(groupBoxName);
        pushName3->setObjectName(QString::fromUtf8("pushName3"));
        pushName3->setEnabled(false);
        pushName3->setMinimumSize(QSize(100, 0));
        pushName3->setMaximumSize(QSize(80, 16777215));
        pushName3->setCheckable(true);
        pushName3->setAutoExclusive(false);

        horizontalgroup->addWidget(pushName3);

        horizontalSpacer_6 = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalgroup->addItem(horizontalSpacer_6);


        horizontalLayout_3->addWidget(groupBoxName);


        verticalLayout_6->addWidget(groupContainer);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(0, 350));
        stackedWidget->setMaximumSize(QSize(16777215, 350));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        verticalLayout_7 = new QVBoxLayout(page_1);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(40, 0, 40, 12);
        widget_4 = new QWidget(page_1);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy1);
        widget_4->setMaximumSize(QSize(16777215, 75));
        verticalLayout_11 = new QVBoxLayout(widget_4);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(-1, 0, -1, -1);
        labelTitle1 = new QLabel(widget_4);
        labelTitle1->setObjectName(QString::fromUtf8("labelTitle1"));
        sizePolicy1.setHeightForWidth(labelTitle1->sizePolicy().hasHeightForWidth());
        labelTitle1->setSizePolicy(sizePolicy1);
        labelTitle1->setMinimumSize(QSize(0, 40));
        labelTitle1->setMaximumSize(QSize(16777215, 40));

        verticalLayout_11->addWidget(labelTitle1, 0, Qt::AlignHCenter);

        labelMessage1b = new QLabel(widget_4);
        labelMessage1b->setObjectName(QString::fromUtf8("labelMessage1b"));
        sizePolicy1.setHeightForWidth(labelMessage1b->sizePolicy().hasHeightForWidth());
        labelMessage1b->setSizePolicy(sizePolicy1);
        labelMessage1b->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(labelMessage1b);


        verticalLayout_7->addWidget(widget_4);

        widget = new QWidget(page_1);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 150));
        verticalLayout_91 = new QVBoxLayout(widget);
        verticalLayout_91->setObjectName(QString::fromUtf8("verticalLayout_91"));
        verticalLayout_91->setContentsMargins(-1, 0, -1, -1);
        verticalLayout_41 = new QVBoxLayout();
        verticalLayout_41->setSpacing(10);
        verticalLayout_41->setObjectName(QString::fromUtf8("verticalLayout_41"));
        labelName = new QLabel(widget);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        verticalLayout_41->addWidget(labelName, 0, Qt::AlignBottom);

        lineEditPropName = new QLineEdit(widget);
        lineEditPropName->setObjectName(QString::fromUtf8("lineEditPropName"));

        verticalLayout_41->addWidget(lineEditPropName);


        verticalLayout_91->addLayout(verticalLayout_41);

        verticalLayout_31 = new QVBoxLayout();
        verticalLayout_31->setSpacing(10);
        verticalLayout_31->setObjectName(QString::fromUtf8("verticalLayout_31"));
        labelURL = new QLabel(widget);
        labelURL->setObjectName(QString::fromUtf8("labelURL"));

        verticalLayout_31->addWidget(labelURL, 0, Qt::AlignBottom);

        lineEditURL = new QLineEdit(widget);
        lineEditURL->setObjectName(QString::fromUtf8("lineEditURL"));

        verticalLayout_31->addWidget(lineEditURL);


        verticalLayout_91->addLayout(verticalLayout_31);


        verticalLayout_7->addWidget(widget);

        verticalSpacer_7 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer_7);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 3);
        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(40, 0, 40, 12);
        containerPage2 = new QWidget(page_2);
        containerPage2->setObjectName(QString::fromUtf8("containerPage2"));
        verticalLayout_51 = new QVBoxLayout(containerPage2);
        verticalLayout_51->setSpacing(0);
        verticalLayout_51->setObjectName(QString::fromUtf8("verticalLayout_51"));
        verticalLayout_51->setContentsMargins(0, 0, 0, 0);
        widget_61 = new QWidget(containerPage2);
        widget_61->setObjectName(QString::fromUtf8("widget_61"));
        verticalLayout_151 = new QVBoxLayout(widget_61);
        verticalLayout_151->setObjectName(QString::fromUtf8("verticalLayout_151"));
        verticalLayout_151->setContentsMargins(-1, 0, -1, -1);
        labelTitleDest = new QLabel(widget_61);
        labelTitleDest->setObjectName(QString::fromUtf8("labelTitleDest"));
        sizePolicy1.setHeightForWidth(labelTitleDest->sizePolicy().hasHeightForWidth());
        labelTitleDest->setSizePolicy(sizePolicy1);
        labelTitleDest->setMinimumSize(QSize(0, 40));
        labelTitleDest->setMaximumSize(QSize(16777215, 40));

        verticalLayout_151->addWidget(labelTitleDest, 0, Qt::AlignHCenter);

        labelMessageDest = new QLabel(widget_61);
        labelMessageDest->setObjectName(QString::fromUtf8("labelMessageDest"));
        sizePolicy1.setHeightForWidth(labelMessageDest->sizePolicy().hasHeightForWidth());
        labelMessageDest->setSizePolicy(sizePolicy1);
        labelMessageDest->setAlignment(Qt::AlignCenter);
        labelMessageDest->setWordWrap(true);

        verticalLayout_151->addWidget(labelMessageDest);


        verticalLayout_51->addWidget(widget_61);

        widget33 = new QWidget(containerPage2);
        widget33->setObjectName(QString::fromUtf8("widget33"));
        widget33->setMinimumSize(QSize(0, 150));
        verticalLayout_92 = new QVBoxLayout(widget33);
        verticalLayout_92->setObjectName(QString::fromUtf8("verticalLayout_92"));
        verticalLayout_92->setContentsMargins(-1, 0, -1, -1);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        labelAddress = new QLabel(widget33);
        labelAddress->setObjectName(QString::fromUtf8("labelAddress"));

        verticalLayout_4->addWidget(labelAddress, 0, Qt::AlignBottom);

        lineEditAddress = new QLineEdit(widget33);
        lineEditAddress->setObjectName(QString::fromUtf8("lineEditAddress"));

        verticalLayout_4->addWidget(lineEditAddress);


        verticalLayout_92->addLayout(verticalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_32 = new QVBoxLayout();
        verticalLayout_32->setSpacing(10);
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        labelAmount = new QLabel(widget33);
        labelAmount->setObjectName(QString::fromUtf8("labelAmount"));

        verticalLayout_32->addWidget(labelAmount, 0, Qt::AlignBottom);

        lineEditAmount = new QLineEdit(widget33);
        lineEditAmount->setObjectName(QString::fromUtf8("lineEditAmount"));
        lineEditAmount->setMaxLength(12);

        verticalLayout_32->addWidget(lineEditAmount);


        horizontalLayout_6->addLayout(verticalLayout_32);

        verticalLayout_161 = new QVBoxLayout();
        verticalLayout_161->setSpacing(10);
        verticalLayout_161->setObjectName(QString::fromUtf8("verticalLayout_161"));
        labelMonths = new QLabel(widget33);
        labelMonths->setObjectName(QString::fromUtf8("labelMonths"));

        verticalLayout_161->addWidget(labelMonths, 0, Qt::AlignBottom);

        lineEditMonths = new QSpinBox(widget33);
        lineEditMonths->setObjectName(QString::fromUtf8("lineEditMonths"));
        lineEditMonths->setMinimumSize(QSize(100, 0));
        lineEditMonths->setFocusPolicy(Qt::NoFocus);
        lineEditMonths->setReadOnly(false);
        lineEditMonths->setKeyboardTracking(false);
        lineEditMonths->setMinimum(1);
        lineEditMonths->setMaximum(6);

        verticalLayout_161->addWidget(lineEditMonths);


        horizontalLayout_6->addLayout(verticalLayout_161);


        verticalLayout_92->addLayout(horizontalLayout_6);


        verticalLayout_51->addWidget(widget33);

        verticalLayout_51->setStretch(0, 1);
        verticalLayout_51->setStretch(1, 3);

        verticalLayout_2->addWidget(containerPage2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_10 = new QVBoxLayout(page_3);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(40, 0, 40, 12);
        widget_3 = new QWidget(page_3);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_5 = new QVBoxLayout(widget_3);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        verticalLayout_15 = new QVBoxLayout(widget_6);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(-1, 0, -1, -1);
        labelTitle3 = new QLabel(widget_6);
        labelTitle3->setObjectName(QString::fromUtf8("labelTitle3"));
        sizePolicy1.setHeightForWidth(labelTitle3->sizePolicy().hasHeightForWidth());
        labelTitle3->setSizePolicy(sizePolicy1);
        labelTitle3->setMinimumSize(QSize(0, 40));
        labelTitle3->setMaximumSize(QSize(16777215, 40));

        verticalLayout_15->addWidget(labelTitle3, 0, Qt::AlignHCenter);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_15->addItem(verticalSpacer_2);


        verticalLayout_5->addWidget(widget_6);

        widget39 = new QWidget(widget_3);
        widget39->setObjectName(QString::fromUtf8("widget39"));
        widget39->setMinimumSize(QSize(0, 150));
        verticalLayout_9 = new QVBoxLayout(widget39);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        verticalLayout_33 = new QVBoxLayout();
        verticalLayout_33->setSpacing(10);
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        labelResultNameTitle = new QLabel(widget39);
        labelResultNameTitle->setObjectName(QString::fromUtf8("labelResultNameTitle"));

        verticalLayout_33->addWidget(labelResultNameTitle, 0, Qt::AlignBottom);

        labelResultName = new QLabel(widget39);
        labelResultName->setObjectName(QString::fromUtf8("labelResultName"));
        labelResultName->setText(QString::fromUtf8("AMMOcoin-MBD-JanJun2021"));

        verticalLayout_33->addWidget(labelResultName);


        horizontalLayout_17->addLayout(verticalLayout_33);

        verticalLayout_162 = new QVBoxLayout();
        verticalLayout_162->setSpacing(10);
        verticalLayout_162->setObjectName(QString::fromUtf8("verticalLayout_162"));
        labelResultAmountTitle = new QLabel(widget39);
        labelResultAmountTitle->setObjectName(QString::fromUtf8("labelResultAmountTitle"));
        labelResultAmountTitle->setLayoutDirection(Qt::RightToLeft);
        labelResultAmountTitle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_162->addWidget(labelResultAmountTitle, 0, Qt::AlignBottom);

        labelResultAmount = new QLabel(widget39);
        labelResultAmount->setObjectName(QString::fromUtf8("labelResultAmount"));
        labelResultAmount->setText(QString::fromUtf8("5500 PIV"));
        labelResultAmount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_162->addWidget(labelResultAmount);


        horizontalLayout_17->addLayout(verticalLayout_162);


        verticalLayout_9->addLayout(horizontalLayout_17);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        labelResultAddressTitle = new QLabel(widget39);
        labelResultAddressTitle->setObjectName(QString::fromUtf8("labelResultAddressTitle"));

        verticalLayout_3->addWidget(labelResultAddressTitle, 0, Qt::AlignBottom);

        labelResultAddress = new QLabel(widget39);
        labelResultAddress->setObjectName(QString::fromUtf8("labelResultAddress"));
        labelResultAddress->setText(QString::fromUtf8("N/A"));

        verticalLayout_3->addWidget(labelResultAddress);


        horizontalLayout_19->addLayout(verticalLayout_3);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(10);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        labelResultMonthsTitle = new QLabel(widget39);
        labelResultMonthsTitle->setObjectName(QString::fromUtf8("labelResultMonthsTitle"));
        labelResultMonthsTitle->setLayoutDirection(Qt::RightToLeft);
        labelResultMonthsTitle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_16->addWidget(labelResultMonthsTitle, 0, Qt::AlignBottom);

        labelResultMonths = new QLabel(widget39);
        labelResultMonths->setObjectName(QString::fromUtf8("labelResultMonths"));
        labelResultMonths->setText(QString::fromUtf8("2 Months"));
        labelResultMonths->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_16->addWidget(labelResultMonths);


        horizontalLayout_19->addLayout(verticalLayout_16);


        verticalLayout_9->addLayout(horizontalLayout_19);

        verticalLayout_42 = new QVBoxLayout();
        verticalLayout_42->setSpacing(10);
        verticalLayout_42->setObjectName(QString::fromUtf8("verticalLayout_42"));
        labelResultUrlTitle = new QLabel(widget39);
        labelResultUrlTitle->setObjectName(QString::fromUtf8("labelResultUrlTitle"));

        verticalLayout_42->addWidget(labelResultUrlTitle, 0, Qt::AlignBottom);

        labelResultUrl = new QLabel(widget39);
        labelResultUrl->setObjectName(QString::fromUtf8("labelResultUrl"));
        labelResultUrl->setText(QString::fromUtf8("N/A"));

        verticalLayout_42->addWidget(labelResultUrl, 0, Qt::AlignBottom);


        verticalLayout_9->addLayout(verticalLayout_42);


        verticalLayout_5->addWidget(widget39);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 3);

        verticalLayout_10->addWidget(widget_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page_3);

        verticalLayout_6->addWidget(stackedWidget);

        horizontalLayout1 = new QHBoxLayout();
        horizontalLayout1->setObjectName(QString::fromUtf8("horizontalLayout1"));
        btnGenAddr = new QPushButton(frame);
        btnGenAddr->setObjectName(QString::fromUtf8("btnGenAddr"));
        btnGenAddr->setMinimumSize(QSize(180, 50));
        btnGenAddr->setMaximumSize(QSize(250, 16777215));
        btnGenAddr->setFocusPolicy(Qt::NoFocus);
        btnGenAddr->setText(QString::fromUtf8("N/A"));

        horizontalLayout1->addWidget(btnGenAddr);

        horizontalSpacer = new QSpacerItem(180, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout1->addItem(horizontalSpacer);

        btnBack = new QPushButton(frame);
        btnBack->setObjectName(QString::fromUtf8("btnBack"));
        btnBack->setMinimumSize(QSize(0, 50));
        btnBack->setMaximumSize(QSize(180, 16777215));
        btnBack->setFocusPolicy(Qt::NoFocus);

        horizontalLayout1->addWidget(btnBack);

        btnNext = new QPushButton(frame);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setMinimumSize(QSize(0, 50));
        btnNext->setMaximumSize(QSize(180, 16777215));
        btnNext->setFocusPolicy(Qt::NoFocus);

        horizontalLayout1->addWidget(btnNext);

        horizontalLayout1->setStretch(3, 2);

        verticalLayout_6->addLayout(horizontalLayout1);


        verticalLayout->addWidget(frame);


        retranslateUi(CreateProposalDialog);

        stackedIcon1->setCurrentIndex(0);
        stackedIcon2->setCurrentIndex(0);
        stackedIcon3->setCurrentIndex(1);
        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CreateProposalDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateProposalDialog)
    {
        pushButtonSkip->setText(QString());
        labelLine1->setText(QString());
        labelLine2->setText(QString());
        groupBoxName->setTitle(QString());
        pushName1->setText(QCoreApplication::translate("CreateProposalDialog", "Name", nullptr));
        pushName2->setText(QCoreApplication::translate("CreateProposalDialog", "Receiver", nullptr));
        pushName3->setText(QCoreApplication::translate("CreateProposalDialog", "Summary", nullptr));
        labelTitle1->setText(QCoreApplication::translate("CreateProposalDialog", "Create New Proposal", nullptr));
        labelMessage1b->setText(QCoreApplication::translate("CreateProposalDialog", "Make sure you have 50 PIV for the proposal fee", nullptr));
        labelName->setText(QCoreApplication::translate("CreateProposalDialog", "Proposal Name", nullptr));
        labelURL->setText(QCoreApplication::translate("CreateProposalDialog", "Proposal URL", nullptr));
        labelTitleDest->setText(QCoreApplication::translate("CreateProposalDialog", "Proposal Payee", nullptr));
        labelMessageDest->setText(QCoreApplication::translate("CreateProposalDialog", "Add the requested number of payments, the amount per payment, and the payee address.", nullptr));
        labelAddress->setText(QCoreApplication::translate("CreateProposalDialog", "Address", nullptr));
        labelAmount->setText(QCoreApplication::translate("CreateProposalDialog", "Amount", nullptr));
        labelMonths->setText(QCoreApplication::translate("CreateProposalDialog", "Months", nullptr));
        labelTitle3->setText(QCoreApplication::translate("CreateProposalDialog", "Proposal Summary", nullptr));
        labelResultNameTitle->setText(QCoreApplication::translate("CreateProposalDialog", "Name", nullptr));
        labelResultAmountTitle->setText(QCoreApplication::translate("CreateProposalDialog", "Amount", nullptr));
        labelResultAddressTitle->setText(QCoreApplication::translate("CreateProposalDialog", "Address", nullptr));
        labelResultMonthsTitle->setText(QCoreApplication::translate("CreateProposalDialog", "Months", nullptr));
        labelResultUrlTitle->setText(QCoreApplication::translate("CreateProposalDialog", "Proposal URL", nullptr));
        btnBack->setText(QCoreApplication::translate("CreateProposalDialog", "CANCEL", nullptr));
        btnNext->setText(QCoreApplication::translate("CreateProposalDialog", "OK", nullptr));
        (void)CreateProposalDialog;
    } // retranslateUi

};

namespace Ui {
    class CreateProposalDialog: public Ui_CreateProposalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPROPOSALDIALOG_H
