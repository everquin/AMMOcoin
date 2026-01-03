/********************************************************************************
** Form generated from reading UI file 'proposalinfodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPOSALINFODIALOG_H
#define UI_PROPOSALINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProposalInfoDialog
{
public:
    QVBoxLayout *verticalLayout_1;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_1;
    QSpacerItem *horizontalSpacer_1;
    QLabel *labelTitle;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnEsc;
    QSpacerItem *verticalSpacer;
    QWidget *layoutScroll;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QWidget *content;
    QVBoxLayout *verticalLayout_5;
    QWidget *contentID;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *contentID_int;
    QLabel *labelId;
    QLabel *textId;
    QPushButton *pushCopy;
    QLabel *labelDividerID;
    QWidget *contentName;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *contentName_int;
    QLabel *labelName;
    QLabel *textName;
    QPushButton *btnNameCopy;
    QLabel *labelDividerName;
    QWidget *gridRecipient;
    QGridLayout *contentRecipient;
    QLabel *textRecipient;
    QPushButton *btnRecipientCopy;
    QLabel *labelRecipient;
    QLabel *labelDividerRecipient;
    QGridLayout *gridAmount;
    QLabel *labelAmount;
    QLabel *textAmount;
    QLabel *labelDividerAmount;
    QWidget *gridConfDateStatus;
    QGridLayout *contentConfDateStatus;
    QLabel *labelStatus;
    QLabel *labelDate;
    QLabel *textEndDate;
    QLabel *textDate;
    QLabel *textStatus;
    QLabel *labelEndDate;
    QLabel *labelDividerMemo;
    QWidget *contentUrl;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *contentUrl_int;
    QLabel *labelUrl;
    QLabel *textUrl;
    QPushButton *btnUrlCopy;
    QLabel *labelDividerUrl;
    QHBoxLayout *contentFeeSize;
    QVBoxLayout *contentFee;
    QLabel *labelPosVotes;
    QLabel *textPosVotes;
    QWidget *contentSize;
    QVBoxLayout *contentSize_layout;
    QLabel *labelNegVotes;
    QLabel *textNegVotes;
    QLabel *labelDividerChange;

    void setupUi(QWidget *ProposalInfoDialog)
    {
        if (ProposalInfoDialog->objectName().isEmpty())
            ProposalInfoDialog->setObjectName(QString::fromUtf8("ProposalInfoDialog"));
        ProposalInfoDialog->resize(604, 618);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProposalInfoDialog->sizePolicy().hasHeightForWidth());
        ProposalInfoDialog->setSizePolicy(sizePolicy);
        ProposalInfoDialog->setMinimumSize(QSize(580, 300));
        ProposalInfoDialog->setWindowTitle(QString::fromUtf8("N/A"));
        ProposalInfoDialog->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_1 = new QVBoxLayout(ProposalInfoDialog);
        verticalLayout_1->setSpacing(0);
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        verticalLayout_1->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(ProposalInfoDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(0);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        horizontalLayout_1->setContentsMargins(20, 10, 20, -1);
        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_1);

        labelTitle = new QLabel(frame);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setMinimumSize(QSize(0, 40));
        labelTitle->setMaximumSize(QSize(16777215, 40));
        labelTitle->setStyleSheet(QString::fromUtf8("padding-left:24px;"));
        labelTitle->setAlignment(Qt::AlignCenter);
        labelTitle->setMargin(7);

        horizontalLayout_1->addWidget(labelTitle);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_2);

        btnEsc = new QPushButton(frame);
        btnEsc->setObjectName(QString::fromUtf8("btnEsc"));
        btnEsc->setMinimumSize(QSize(24, 24));
        btnEsc->setMaximumSize(QSize(24, 24));
        btnEsc->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_1->addWidget(btnEsc);


        verticalLayout_2->addLayout(horizontalLayout_1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        layoutScroll = new QWidget(frame);
        layoutScroll->setObjectName(QString::fromUtf8("layoutScroll"));
        layoutScroll->setMinimumSize(QSize(0, 450));
        verticalLayout_3 = new QVBoxLayout(layoutScroll);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, -1);
        scrollArea = new QScrollArea(layoutScroll);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("#scrollArea {\n"
"background:transparent;\n"
"}"));
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 585, 601));
        scrollAreaWidgetContents->setAutoFillBackground(false);
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8("#scrollAreaWidgetContents {\n"
"background:transparent;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        content = new QWidget(scrollAreaWidgetContents);
        content->setObjectName(QString::fromUtf8("content"));
        verticalLayout_5 = new QVBoxLayout(content);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(16, 0, 16, -1);
        contentID = new QWidget(content);
        contentID->setObjectName(QString::fromUtf8("contentID"));
        horizontalLayout_2 = new QHBoxLayout(contentID);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        contentID_int = new QVBoxLayout();
        contentID_int->setObjectName(QString::fromUtf8("contentID_int"));
        labelId = new QLabel(contentID);
        labelId->setObjectName(QString::fromUtf8("labelId"));
        labelId->setMaximumSize(QSize(16777215, 16777215));

        contentID_int->addWidget(labelId);

        textId = new QLabel(contentID);
        textId->setObjectName(QString::fromUtf8("textId"));
        textId->setText(QString::fromUtf8("N/A"));

        contentID_int->addWidget(textId);


        horizontalLayout_2->addLayout(contentID_int);

        pushCopy = new QPushButton(contentID);
        pushCopy->setObjectName(QString::fromUtf8("pushCopy"));
        pushCopy->setMinimumSize(QSize(34, 34));
        pushCopy->setMaximumSize(QSize(34, 34));
        pushCopy->setFocusPolicy(Qt::NoFocus);
        pushCopy->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(pushCopy);


        verticalLayout_5->addWidget(contentID);

        labelDividerID = new QLabel(content);
        labelDividerID->setObjectName(QString::fromUtf8("labelDividerID"));
        labelDividerID->setMaximumSize(QSize(16777215, 1));
        labelDividerID->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_5->addWidget(labelDividerID);

        contentName = new QWidget(content);
        contentName->setObjectName(QString::fromUtf8("contentName"));
        horizontalLayout_3 = new QHBoxLayout(contentName);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, 0, -1);
        contentName_int = new QVBoxLayout();
        contentName_int->setObjectName(QString::fromUtf8("contentName_int"));
        labelName = new QLabel(contentName);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setMaximumSize(QSize(16777215, 16777215));

        contentName_int->addWidget(labelName);

        textName = new QLabel(contentName);
        textName->setObjectName(QString::fromUtf8("textName"));
        textName->setText(QString::fromUtf8("N/A"));

        contentName_int->addWidget(textName);


        horizontalLayout_3->addLayout(contentName_int);

        btnNameCopy = new QPushButton(contentName);
        btnNameCopy->setObjectName(QString::fromUtf8("btnNameCopy"));
        btnNameCopy->setMinimumSize(QSize(34, 34));
        btnNameCopy->setMaximumSize(QSize(34, 34));
        btnNameCopy->setFocusPolicy(Qt::NoFocus);
        btnNameCopy->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(btnNameCopy);


        verticalLayout_5->addWidget(contentName);

        labelDividerName = new QLabel(content);
        labelDividerName->setObjectName(QString::fromUtf8("labelDividerName"));
        labelDividerName->setMaximumSize(QSize(16777215, 1));
        labelDividerName->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_5->addWidget(labelDividerName);

        gridRecipient = new QWidget(content);
        gridRecipient->setObjectName(QString::fromUtf8("gridRecipient"));
        contentRecipient = new QGridLayout(gridRecipient);
        contentRecipient->setObjectName(QString::fromUtf8("contentRecipient"));
        contentRecipient->setContentsMargins(0, -1, 0, -1);
        textRecipient = new QLabel(gridRecipient);
        textRecipient->setObjectName(QString::fromUtf8("textRecipient"));
        textRecipient->setText(QString::fromUtf8("N/A"));
        textRecipient->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        contentRecipient->addWidget(textRecipient, 2, 0, 1, 1);

        btnRecipientCopy = new QPushButton(gridRecipient);
        btnRecipientCopy->setObjectName(QString::fromUtf8("btnRecipientCopy"));
        btnRecipientCopy->setMinimumSize(QSize(34, 34));
        btnRecipientCopy->setMaximumSize(QSize(34, 34));
        btnRecipientCopy->setFocusPolicy(Qt::NoFocus);
        btnRecipientCopy->setIconSize(QSize(24, 24));

        contentRecipient->addWidget(btnRecipientCopy, 2, 3, 1, 1);

        labelRecipient = new QLabel(gridRecipient);
        labelRecipient->setObjectName(QString::fromUtf8("labelRecipient"));
        labelRecipient->setMaximumSize(QSize(16777215, 16777215));
        labelRecipient->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        contentRecipient->addWidget(labelRecipient, 0, 0, 1, 1);


        verticalLayout_5->addWidget(gridRecipient);

        labelDividerRecipient = new QLabel(content);
        labelDividerRecipient->setObjectName(QString::fromUtf8("labelDividerRecipient"));
        labelDividerRecipient->setMaximumSize(QSize(16777215, 1));
        labelDividerRecipient->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_5->addWidget(labelDividerRecipient);

        gridAmount = new QGridLayout();
        gridAmount->setObjectName(QString::fromUtf8("gridAmount"));
        gridAmount->setContentsMargins(-1, 12, -1, 12);
        labelAmount = new QLabel(content);
        labelAmount->setObjectName(QString::fromUtf8("labelAmount"));
        labelAmount->setMaximumSize(QSize(16777215, 16777215));
        labelAmount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridAmount->addWidget(labelAmount, 0, 0, 1, 1);

        textAmount = new QLabel(content);
        textAmount->setObjectName(QString::fromUtf8("textAmount"));
        textAmount->setLayoutDirection(Qt::LeftToRight);
        textAmount->setText(QString::fromUtf8("N/A"));
        textAmount->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridAmount->addWidget(textAmount, 1, 0, 1, 1);


        verticalLayout_5->addLayout(gridAmount);

        labelDividerAmount = new QLabel(content);
        labelDividerAmount->setObjectName(QString::fromUtf8("labelDividerAmount"));
        labelDividerAmount->setMaximumSize(QSize(16777215, 1));
        labelDividerAmount->setBaseSize(QSize(0, 0));
        QPalette palette;
        QBrush brush(QColor(186, 186, 186, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        labelDividerAmount->setPalette(palette);
        labelDividerAmount->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_5->addWidget(labelDividerAmount);

        gridConfDateStatus = new QWidget(content);
        gridConfDateStatus->setObjectName(QString::fromUtf8("gridConfDateStatus"));
        contentConfDateStatus = new QGridLayout(gridConfDateStatus);
        contentConfDateStatus->setObjectName(QString::fromUtf8("contentConfDateStatus"));
        contentConfDateStatus->setContentsMargins(0, -1, 0, -1);
        labelStatus = new QLabel(gridConfDateStatus);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setMaximumSize(QSize(16777215, 16777215));
        labelStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        contentConfDateStatus->addWidget(labelStatus, 1, 3, 1, 1);

        labelDate = new QLabel(gridConfDateStatus);
        labelDate->setObjectName(QString::fromUtf8("labelDate"));
        labelDate->setMaximumSize(QSize(16777215, 16777215));
        labelDate->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        contentConfDateStatus->addWidget(labelDate, 1, 0, 1, 1);

        textEndDate = new QLabel(gridConfDateStatus);
        textEndDate->setObjectName(QString::fromUtf8("textEndDate"));
        textEndDate->setText(QString::fromUtf8("N/A"));
        textEndDate->setAlignment(Qt::AlignCenter);

        contentConfDateStatus->addWidget(textEndDate, 2, 1, 1, 1);

        textDate = new QLabel(gridConfDateStatus);
        textDate->setObjectName(QString::fromUtf8("textDate"));
        textDate->setText(QString::fromUtf8("N/A"));
        textDate->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        contentConfDateStatus->addWidget(textDate, 2, 0, 1, 1);

        textStatus = new QLabel(gridConfDateStatus);
        textStatus->setObjectName(QString::fromUtf8("textStatus"));
        textStatus->setText(QString::fromUtf8("N/A"));
        textStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        contentConfDateStatus->addWidget(textStatus, 2, 3, 1, 1);

        labelEndDate = new QLabel(gridConfDateStatus);
        labelEndDate->setObjectName(QString::fromUtf8("labelEndDate"));
        labelEndDate->setMaximumSize(QSize(16777215, 16777215));
        labelEndDate->setAlignment(Qt::AlignCenter);

        contentConfDateStatus->addWidget(labelEndDate, 1, 1, 1, 1);


        verticalLayout_5->addWidget(gridConfDateStatus);

        labelDividerMemo = new QLabel(content);
        labelDividerMemo->setObjectName(QString::fromUtf8("labelDividerMemo"));
        labelDividerMemo->setMaximumSize(QSize(16777215, 1));
        labelDividerMemo->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_5->addWidget(labelDividerMemo);

        contentUrl = new QWidget(content);
        contentUrl->setObjectName(QString::fromUtf8("contentUrl"));
        horizontalLayout_4 = new QHBoxLayout(contentUrl);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, 0, -1);
        contentUrl_int = new QVBoxLayout();
        contentUrl_int->setObjectName(QString::fromUtf8("contentUrl_int"));
        labelUrl = new QLabel(contentUrl);
        labelUrl->setObjectName(QString::fromUtf8("labelUrl"));
        labelUrl->setMaximumSize(QSize(16777215, 16777215));

        contentUrl_int->addWidget(labelUrl);

        textUrl = new QLabel(contentUrl);
        textUrl->setObjectName(QString::fromUtf8("textUrl"));
        textUrl->setText(QString::fromUtf8("N/A"));

        contentUrl_int->addWidget(textUrl);


        horizontalLayout_4->addLayout(contentUrl_int);

        btnUrlCopy = new QPushButton(contentUrl);
        btnUrlCopy->setObjectName(QString::fromUtf8("btnUrlCopy"));
        btnUrlCopy->setMinimumSize(QSize(34, 34));
        btnUrlCopy->setMaximumSize(QSize(34, 34));
        btnUrlCopy->setFocusPolicy(Qt::NoFocus);
        btnUrlCopy->setIconSize(QSize(24, 24));

        horizontalLayout_4->addWidget(btnUrlCopy);


        verticalLayout_5->addWidget(contentUrl);

        labelDividerUrl = new QLabel(content);
        labelDividerUrl->setObjectName(QString::fromUtf8("labelDividerUrl"));
        labelDividerUrl->setMaximumSize(QSize(16777215, 1));
        labelDividerUrl->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_5->addWidget(labelDividerUrl);

        contentFeeSize = new QHBoxLayout();
        contentFeeSize->setObjectName(QString::fromUtf8("contentFeeSize"));
        contentFeeSize->setContentsMargins(-1, 9, -1, 9);
        contentFee = new QVBoxLayout();
        contentFee->setObjectName(QString::fromUtf8("contentFee"));
        contentFee->setContentsMargins(-1, 0, -1, 0);
        labelPosVotes = new QLabel(content);
        labelPosVotes->setObjectName(QString::fromUtf8("labelPosVotes"));
        labelPosVotes->setMaximumSize(QSize(16777215, 16777215));

        contentFee->addWidget(labelPosVotes);

        textPosVotes = new QLabel(content);
        textPosVotes->setObjectName(QString::fromUtf8("textPosVotes"));
        textPosVotes->setText(QString::fromUtf8("N/A"));

        contentFee->addWidget(textPosVotes);


        contentFeeSize->addLayout(contentFee);

        contentSize = new QWidget(content);
        contentSize->setObjectName(QString::fromUtf8("contentSize"));
        contentSize_layout = new QVBoxLayout(contentSize);
        contentSize_layout->setObjectName(QString::fromUtf8("contentSize_layout"));
        contentSize_layout->setContentsMargins(-1, 0, 0, 0);
        labelNegVotes = new QLabel(contentSize);
        labelNegVotes->setObjectName(QString::fromUtf8("labelNegVotes"));
        labelNegVotes->setMaximumSize(QSize(16777215, 16777215));
        labelNegVotes->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        contentSize_layout->addWidget(labelNegVotes);

        textNegVotes = new QLabel(contentSize);
        textNegVotes->setObjectName(QString::fromUtf8("textNegVotes"));
        textNegVotes->setText(QString::fromUtf8("N/A"));
        textNegVotes->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        contentSize_layout->addWidget(textNegVotes);


        contentFeeSize->addWidget(contentSize);


        verticalLayout_5->addLayout(contentFeeSize);

        labelDividerChange = new QLabel(content);
        labelDividerChange->setObjectName(QString::fromUtf8("labelDividerChange"));
        labelDividerChange->setMaximumSize(QSize(16777215, 1));
        labelDividerChange->setStyleSheet(QString::fromUtf8("background-color:#bababa;"));

        verticalLayout_5->addWidget(labelDividerChange);


        verticalLayout_4->addWidget(content);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);


        verticalLayout_2->addWidget(layoutScroll);


        verticalLayout_1->addWidget(frame);


        retranslateUi(ProposalInfoDialog);

        QMetaObject::connectSlotsByName(ProposalInfoDialog);
    } // setupUi

    void retranslateUi(QWidget *ProposalInfoDialog)
    {
        labelTitle->setText(QCoreApplication::translate("ProposalInfoDialog", "Proposal Information", nullptr));
        btnEsc->setText(QString());
        labelId->setText(QCoreApplication::translate("ProposalInfoDialog", "ID", nullptr));
        pushCopy->setText(QString());
        labelDividerID->setText(QString());
        labelName->setText(QCoreApplication::translate("ProposalInfoDialog", "Proposal Name", nullptr));
        btnNameCopy->setText(QString());
        labelDividerName->setText(QString());
        btnRecipientCopy->setText(QString());
        labelRecipient->setText(QCoreApplication::translate("ProposalInfoDialog", "Recipient", nullptr));
        labelDividerRecipient->setText(QString());
        labelAmount->setText(QCoreApplication::translate("ProposalInfoDialog", "Amount", nullptr));
        labelDividerAmount->setText(QString());
        labelStatus->setText(QCoreApplication::translate("ProposalInfoDialog", "Status", nullptr));
        labelDate->setText(QCoreApplication::translate("ProposalInfoDialog", "Start Block", nullptr));
        labelEndDate->setText(QCoreApplication::translate("ProposalInfoDialog", "End Block", nullptr));
        labelDividerMemo->setText(QString());
        labelUrl->setText(QCoreApplication::translate("ProposalInfoDialog", "URL", nullptr));
        btnUrlCopy->setText(QString());
        labelDividerUrl->setText(QString());
        labelPosVotes->setText(QCoreApplication::translate("ProposalInfoDialog", "Positive Votes", nullptr));
        labelNegVotes->setText(QCoreApplication::translate("ProposalInfoDialog", "Negative Votes", nullptr));
        labelDividerChange->setText(QString());
        (void)ProposalInfoDialog;
    } // retranslateUi

};

namespace Ui {
    class ProposalInfoDialog: public Ui_ProposalInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPOSALINFODIALOG_H
