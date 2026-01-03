/********************************************************************************
** Form generated from reading UI file 'proposalcard.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPOSALCARD_H
#define UI_PROPOSALCARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProposalCard
{
public:
    QVBoxLayout *verticalLayout_1;
    QWidget *card;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_1;
    QLabel *labelPropName;
    QSpacerItem *horizontalSpacer_1;
    QPushButton *btnLink;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *containerAmount;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelPropAmount;
    QLabel *labelPropMonths;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelStatus;
    QWidget *containerVotes;
    QGridLayout *gridLayout;
    QProgressBar *votesBar;
    QWidget *containerText;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelNo;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelYes;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnVote;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *ProposalCard)
    {
        if (ProposalCard->objectName().isEmpty())
            ProposalCard->setObjectName(QString::fromUtf8("ProposalCard"));
        ProposalCard->resize(260, 200);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProposalCard->sizePolicy().hasHeightForWidth());
        ProposalCard->setSizePolicy(sizePolicy);
        ProposalCard->setMinimumSize(QSize(260, 200));
        ProposalCard->setMaximumSize(QSize(330, 200));
        verticalLayout_1 = new QVBoxLayout(ProposalCard);
        verticalLayout_1->setSpacing(0);
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        verticalLayout_1->setContentsMargins(0, 0, 0, 0);
        card = new QWidget(ProposalCard);
        card->setObjectName(QString::fromUtf8("card"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(card->sizePolicy().hasHeightForWidth());
        card->setSizePolicy(sizePolicy1);
        card->setMinimumSize(QSize(0, 200));
        card->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(card);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(12, 12, 12, 12);
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(0);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        labelPropName = new QLabel(card);
        labelPropName->setObjectName(QString::fromUtf8("labelPropName"));
        labelPropName->setText(QString::fromUtf8("N/A"));

        horizontalLayout_1->addWidget(labelPropName);

        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_1);

        btnLink = new QPushButton(card);
        btnLink->setObjectName(QString::fromUtf8("btnLink"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnLink->sizePolicy().hasHeightForWidth());
        btnLink->setSizePolicy(sizePolicy2);
        btnLink->setMaximumSize(QSize(22, 25));
        btnLink->setCursor(QCursor(Qt::PointingHandCursor));
        btnLink->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_1->addWidget(btnLink);


        verticalLayout_2->addLayout(horizontalLayout_1);

        widget = new QWidget(card);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        containerAmount = new QWidget(widget);
        containerAmount->setObjectName(QString::fromUtf8("containerAmount"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(containerAmount->sizePolicy().hasHeightForWidth());
        containerAmount->setSizePolicy(sizePolicy3);
        verticalLayout_3 = new QVBoxLayout(containerAmount);
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelPropAmount = new QLabel(containerAmount);
        labelPropAmount->setObjectName(QString::fromUtf8("labelPropAmount"));
        labelPropAmount->setText(QString::fromUtf8("N/A"));

        verticalLayout_3->addWidget(labelPropAmount, 0, Qt::AlignBottom);

        labelPropMonths = new QLabel(containerAmount);
        labelPropMonths->setObjectName(QString::fromUtf8("labelPropMonths"));
        labelPropMonths->setText(QString::fromUtf8("N/A"));

        verticalLayout_3->addWidget(labelPropMonths);


        horizontalLayout_2->addWidget(containerAmount);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        labelStatus = new QLabel(widget);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setStyleSheet(QString::fromUtf8("margin-top:16;"));
        labelStatus->setText(QString::fromUtf8("N/A"));

        horizontalLayout_2->addWidget(labelStatus, 0, Qt::AlignVCenter);


        verticalLayout_2->addWidget(widget);

        containerVotes = new QWidget(card);
        containerVotes->setObjectName(QString::fromUtf8("containerVotes"));
        sizePolicy3.setHeightForWidth(containerVotes->sizePolicy().hasHeightForWidth());
        containerVotes->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(containerVotes);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        votesBar = new QProgressBar(containerVotes);
        votesBar->setObjectName(QString::fromUtf8("votesBar"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(votesBar->sizePolicy().hasHeightForWidth());
        votesBar->setSizePolicy(sizePolicy4);
        votesBar->setMinimumSize(QSize(0, 25));
        QFont font;
        font.setStyleStrategy(QFont::NoAntialias);
        votesBar->setFont(font);
        votesBar->setValue(24);
        votesBar->setTextVisible(false);

        gridLayout->addWidget(votesBar, 0, 0, 1, 1);

        containerText = new QWidget(containerVotes);
        containerText->setObjectName(QString::fromUtf8("containerText"));
        containerText->setMinimumSize(QSize(0, 0));
        horizontalLayout_3 = new QHBoxLayout(containerText);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, 0);
        labelNo = new QLabel(containerText);
        labelNo->setObjectName(QString::fromUtf8("labelNo"));
        labelNo->setStyleSheet(QString::fromUtf8("color:#4D4D4D;"));
        labelNo->setText(QString::fromUtf8("N/A"));

        horizontalLayout_3->addWidget(labelNo);

        horizontalSpacer_3 = new QSpacerItem(93, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        labelYes = new QLabel(containerText);
        labelYes->setObjectName(QString::fromUtf8("labelYes"));
        labelYes->setStyleSheet(QString::fromUtf8("color:#5C4B7D;"));
        labelYes->setText(QString::fromUtf8("N/A"));

        horizontalLayout_3->addWidget(labelYes);


        gridLayout->addWidget(containerText, 0, 0, 1, 1);


        verticalLayout_2->addWidget(containerVotes);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        btnVote = new QPushButton(card);
        btnVote->setObjectName(QString::fromUtf8("btnVote"));
        btnVote->setMinimumSize(QSize(80, 0));
        btnVote->setFocusPolicy(Qt::NoFocus);
        btnVote->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(btnVote);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_2->setStretch(0, 4);
        verticalLayout_2->setStretch(1, 4);
        verticalLayout_2->setStretch(2, 2);
        verticalLayout_2->setStretch(3, 4);

        verticalLayout_1->addWidget(card);


        retranslateUi(ProposalCard);

        QMetaObject::connectSlotsByName(ProposalCard);
    } // setupUi

    void retranslateUi(QWidget *ProposalCard)
    {
        btnLink->setText(QString());
        btnVote->setText(QCoreApplication::translate("ProposalCard", "Vote", nullptr));
        (void)ProposalCard;
    } // retranslateUi

};

namespace Ui {
    class ProposalCard: public Ui_ProposalCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPOSALCARD_H
