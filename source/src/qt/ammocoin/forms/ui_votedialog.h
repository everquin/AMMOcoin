/********************************************************************************
** Form generated from reading UI file 'votedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOTEDIALOG_H
#define UI_VOTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VoteDialog
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
    QLabel *labelSubtitle;
    QSpacerItem *verticalSpacer_1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelTitleVote;
    QPushButton *btnLink;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelAmount;
    QLabel *labelTime;
    QSpacerItem *verticalSpacer_2;
    QWidget *containerVotes;
    QHBoxLayout *horizontalLayout_3;
    QWidget *containerNo;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_5;
    QWidget *containerYes;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnSelectMasternodes;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnCancel;
    QPushButton *btnSave;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QLabel *labelMessage;
    QSpacerItem *verticalSpacer_7;

    void setupUi(QWidget *VoteDialog)
    {
        if (VoteDialog->objectName().isEmpty())
            VoteDialog->setObjectName(QString::fromUtf8("VoteDialog"));
        VoteDialog->resize(550, 450);
        verticalLayout_1 = new QVBoxLayout(VoteDialog);
        verticalLayout_1->setSpacing(0);
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        verticalLayout_1->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(VoteDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 20, 20, 20);
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(0);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
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

        labelSubtitle = new QLabel(frame);
        labelSubtitle->setObjectName(QString::fromUtf8("labelSubtitle"));

        verticalLayout_2->addWidget(labelSubtitle, 0, Qt::AlignHCenter);

        verticalSpacer_1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        labelTitleVote = new QLabel(frame);
        labelTitleVote->setObjectName(QString::fromUtf8("labelTitleVote"));
        labelTitleVote->setMinimumSize(QSize(0, 30));
        labelTitleVote->setText(QString::fromUtf8("AMMOcoin-MBD-Jan-2021"));
        labelTitleVote->setAlignment(Qt::AlignCenter);
        labelTitleVote->setWordWrap(true);

        horizontalLayout_2->addWidget(labelTitleVote);

        btnLink = new QPushButton(frame);
        btnLink->setObjectName(QString::fromUtf8("btnLink"));
        btnLink->setMinimumSize(QSize(0, 30));
        btnLink->setMaximumSize(QSize(16777215, 30));
        btnLink->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(btnLink);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 50));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelAmount = new QLabel(widget);
        labelAmount->setObjectName(QString::fromUtf8("labelAmount"));
        labelAmount->setText(QString::fromUtf8("5,000 PIV"));

        verticalLayout_3->addWidget(labelAmount);

        labelTime = new QLabel(widget);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));
        labelTime->setText(QString::fromUtf8("2 months of 4"));

        verticalLayout_3->addWidget(labelTime);


        verticalLayout_2->addWidget(widget, 0, Qt::AlignHCenter);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        containerVotes = new QWidget(frame);
        containerVotes->setObjectName(QString::fromUtf8("containerVotes"));
        containerVotes->setMinimumSize(QSize(0, 36));
        horizontalLayout_3 = new QHBoxLayout(containerVotes);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        containerNo = new QWidget(containerVotes);
        containerNo->setObjectName(QString::fromUtf8("containerNo"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(containerNo->sizePolicy().hasHeightForWidth());
        containerNo->setSizePolicy(sizePolicy);
        containerNo->setMinimumSize(QSize(0, 36));
        gridLayout = new QGridLayout(containerNo);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_3->addWidget(containerNo);

        horizontalSpacer_5 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        containerYes = new QWidget(containerVotes);
        containerYes->setObjectName(QString::fromUtf8("containerYes"));
        containerYes->setMinimumSize(QSize(0, 36));
        containerYes->setLayoutDirection(Qt::LeftToRight);
        gridLayout_2 = new QGridLayout(containerYes);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_3->addWidget(containerYes);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(2, 1);

        verticalLayout_2->addWidget(containerVotes);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        btnSelectMasternodes = new QPushButton(frame);
        btnSelectMasternodes->setObjectName(QString::fromUtf8("btnSelectMasternodes"));
        btnSelectMasternodes->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_2->addWidget(btnSelectMasternodes);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        btnCancel = new QPushButton(frame);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(0, 50));
        btnCancel->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(btnCancel);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(0, 50));
        btnSave->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(btnSave);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        horizontalLayout_4->setStretch(1, 2);
        horizontalLayout_4->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);

        labelMessage = new QLabel(frame);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));

        verticalLayout_2->addWidget(labelMessage, 0, Qt::AlignHCenter);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_7);


        verticalLayout_1->addWidget(frame);


        retranslateUi(VoteDialog);

        QMetaObject::connectSlotsByName(VoteDialog);
    } // setupUi

    void retranslateUi(QWidget *VoteDialog)
    {
        labelTitle->setText(QCoreApplication::translate("VoteDialog", "Vote For Proposal", nullptr));
        btnEsc->setText(QString());
        labelSubtitle->setText(QCoreApplication::translate("VoteDialog", "Select vote direction and the masternodes that will vote for it", nullptr));
        btnLink->setText(QString());
        btnSelectMasternodes->setText(QCoreApplication::translate("VoteDialog", "Select Voting Masternodes", nullptr));
        btnCancel->setText(QCoreApplication::translate("VoteDialog", "CANCEL", nullptr));
        btnSave->setText(QCoreApplication::translate("VoteDialog", "VOTE", nullptr));
        labelMessage->setText(QCoreApplication::translate("VoteDialog", "You can change your vote later", nullptr));
        (void)VoteDialog;
    } // retranslateUi

};

namespace Ui {
    class VoteDialog: public Ui_VoteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOTEDIALOG_H
