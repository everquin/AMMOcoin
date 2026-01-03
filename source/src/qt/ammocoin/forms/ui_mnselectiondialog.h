/********************************************************************************
** Form generated from reading UI file 'mnselectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MNSELECTIONDIALOG_H
#define UI_MNSELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MnSelectionDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnEsc;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelTitle;
    QSpacerItem *horizontalSpacer;
    QLabel *labelMessage;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *containerTop;
    QHBoxLayout *horizontalLayout_2;
    QWidget *containerAmountOfVotes;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelAmountOfVotesText;
    QLabel *labelAmountOfVotes;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnSelectAll;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *treeWidget;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCancel;
    QPushButton *btnSave;

    void setupUi(QWidget *MnSelectionDialog)
    {
        if (MnSelectionDialog->objectName().isEmpty())
            MnSelectionDialog->setObjectName(QString::fromUtf8("MnSelectionDialog"));
        MnSelectionDialog->resize(500, 400);
        MnSelectionDialog->setWindowTitle(QString::fromUtf8("N/A"));
        verticalLayout_3 = new QVBoxLayout(MnSelectionDialog);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(MnSelectionDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(30, 20, 30, 20);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnEsc = new QPushButton(frame);
        btnEsc->setObjectName(QString::fromUtf8("btnEsc"));
        btnEsc->setMinimumSize(QSize(24, 24));
        btnEsc->setMaximumSize(QSize(24, 24));
        btnEsc->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(btnEsc);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        labelTitle = new QLabel(frame);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setMinimumSize(QSize(0, 40));
        labelTitle->setMaximumSize(QSize(16777215, 40));
        labelTitle->setStyleSheet(QString::fromUtf8("padding-right:24px;"));
        labelTitle->setAlignment(Qt::AlignCenter);
        labelTitle->setMargin(7);

        horizontalLayout_3->addWidget(labelTitle);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        labelMessage = new QLabel(frame);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));
        labelMessage->setAlignment(Qt::AlignCenter);
        labelMessage->setWordWrap(true);

        verticalLayout_2->addWidget(labelMessage);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 55));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(50, 0, 50, 0);
        containerTop = new QWidget(widget);
        containerTop->setObjectName(QString::fromUtf8("containerTop"));
        horizontalLayout_2 = new QHBoxLayout(containerTop);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        containerAmountOfVotes = new QWidget(containerTop);
        containerAmountOfVotes->setObjectName(QString::fromUtf8("containerAmountOfVotes"));
        containerAmountOfVotes->setMinimumSize(QSize(180, 36));
        containerAmountOfVotes->setMaximumSize(QSize(16777215, 36));
        horizontalLayout_4 = new QHBoxLayout(containerAmountOfVotes);
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(12, 4, 12, 4);
        labelAmountOfVotesText = new QLabel(containerAmountOfVotes);
        labelAmountOfVotesText->setObjectName(QString::fromUtf8("labelAmountOfVotesText"));
        labelAmountOfVotesText->setMinimumSize(QSize(140, 0));
        labelAmountOfVotesText->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_4->addWidget(labelAmountOfVotesText);

        labelAmountOfVotes = new QLabel(containerAmountOfVotes);
        labelAmountOfVotes->setObjectName(QString::fromUtf8("labelAmountOfVotes"));
        labelAmountOfVotes->setText(QString::fromUtf8("0"));

        horizontalLayout_4->addWidget(labelAmountOfVotes);

        horizontalLayout_4->setStretch(0, 1);

        horizontalLayout_2->addWidget(containerAmountOfVotes);

        horizontalSpacer_3 = new QSpacerItem(211, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btnSelectAll = new QPushButton(containerTop);
        btnSelectAll->setObjectName(QString::fromUtf8("btnSelectAll"));
        btnSelectAll->setMinimumSize(QSize(92, 36));
        btnSelectAll->setMaximumSize(QSize(16777215, 36));
        btnSelectAll->setFocusPolicy(Qt::NoFocus);
        btnSelectAll->setCheckable(true);
        btnSelectAll->setChecked(false);

        horizontalLayout_2->addWidget(btnSelectAll);


        verticalLayout->addWidget(containerTop);


        verticalLayout_2->addWidget(widget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(50, -1, 50, -1);
        treeWidget = new QTreeWidget(frame);
        treeWidget->headerItem()->setText(0, QString());
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setFocusPolicy(Qt::NoFocus);
        treeWidget->setStyleSheet(QString::fromUtf8("outline: 0;"));

        horizontalLayout_6->addWidget(treeWidget);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(60, -1, 60, -1);
        btnCancel = new QPushButton(frame);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(0, 50));
        btnCancel->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(btnCancel);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setMinimumSize(QSize(0, 50));
        btnSave->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(btnSave);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(frame);


        retranslateUi(MnSelectionDialog);

        QMetaObject::connectSlotsByName(MnSelectionDialog);
    } // setupUi

    void retranslateUi(QWidget *MnSelectionDialog)
    {
        btnEsc->setText(QString());
        labelTitle->setText(QCoreApplication::translate("MnSelectionDialog", "Select Masternodes", nullptr));
        labelMessage->setText(QCoreApplication::translate("MnSelectionDialog", "Each Masternode refers to a single vote, you can select which one will vote for the proposal", nullptr));
        labelAmountOfVotesText->setText(QCoreApplication::translate("MnSelectionDialog", "Amount of votes:", nullptr));
        btnSelectAll->setText(QCoreApplication::translate("MnSelectionDialog", "Select All", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("MnSelectionDialog", "Status", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MnSelectionDialog", "Vote", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MnSelectionDialog", "Name", nullptr));
        btnCancel->setText(QCoreApplication::translate("MnSelectionDialog", "CANCEL", nullptr));
        btnSave->setText(QCoreApplication::translate("MnSelectionDialog", "SELECT VOTES", nullptr));
        (void)MnSelectionDialog;
    } // retranslateUi

};

namespace Ui {
    class MnSelectionDialog: public Ui_MnSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNSELECTIONDIALOG_H
