/********************************************************************************
** Form generated from reading UI file 'intro.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRO_H
#define UI_INTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Intro
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *frame_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *container;
    QVBoxLayout *verticalLayout_9;
    QWidget *frame;
    QVBoxLayout *verticalLayout_6;
    QLabel *welcomeLabel;
    QSpacerItem *verticalSpacer_4;
    QLabel *storageLabel;
    QLabel *sizeWarningLabel;
    QSpacerItem *verticalSpacer_5;
    QRadioButton *dataDirDefault;
    QSpacerItem *verticalSpacer_7;
    QRadioButton *dataDirCustom;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *dataDirectory;
    QVBoxLayout *verticalLayout_4;
    QPushButton *ellipsisButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *freeSpace;
    QSpacerItem *verticalSpacer_2;
    QLabel *errorMessage;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonOk;

    void setupUi(QDialog *Intro)
    {
        if (Intro->objectName().isEmpty())
            Intro->setObjectName(QString::fromUtf8("Intro"));
        Intro->resize(1200, 750);
        verticalLayout = new QVBoxLayout(Intro);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QWidget(Intro);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        container = new QWidget(frame_2);
        container->setObjectName(QString::fromUtf8("container"));
        container->setMinimumSize(QSize(820, 520));
        container->setMaximumSize(QSize(820, 520));
        verticalLayout_9 = new QVBoxLayout(container);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(1, 1, 1, 1);
        frame = new QWidget(container);
        frame->setObjectName(QString::fromUtf8("frame"));
        verticalLayout_6 = new QVBoxLayout(frame);
        verticalLayout_6->setSpacing(10);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(30, 30, 30, 30);
        welcomeLabel = new QLabel(frame);
        welcomeLabel->setObjectName(QString::fromUtf8("welcomeLabel"));
        welcomeLabel->setStyleSheet(QString::fromUtf8("QLabel { font-style:italic; }"));
        welcomeLabel->setAlignment(Qt::AlignCenter);
        welcomeLabel->setWordWrap(true);

        verticalLayout_6->addWidget(welcomeLabel);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_4);

        storageLabel = new QLabel(frame);
        storageLabel->setObjectName(QString::fromUtf8("storageLabel"));
        storageLabel->setMinimumSize(QSize(0, 0));
        storageLabel->setAlignment(Qt::AlignCenter);
        storageLabel->setWordWrap(true);

        verticalLayout_6->addWidget(storageLabel);

        sizeWarningLabel = new QLabel(frame);
        sizeWarningLabel->setObjectName(QString::fromUtf8("sizeWarningLabel"));
        sizeWarningLabel->setStyleSheet(QString::fromUtf8("#sizeWarningLabel {\n"
"	padding:0 80px;\n"
"}"));
        sizeWarningLabel->setAlignment(Qt::AlignCenter);
        sizeWarningLabel->setWordWrap(true);

        verticalLayout_6->addWidget(sizeWarningLabel);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_5);

        dataDirDefault = new QRadioButton(frame);
        dataDirDefault->setObjectName(QString::fromUtf8("dataDirDefault"));

        verticalLayout_6->addWidget(dataDirDefault);

        verticalSpacer_7 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_7);

        dataDirCustom = new QRadioButton(frame);
        dataDirCustom->setObjectName(QString::fromUtf8("dataDirCustom"));

        verticalLayout_6->addWidget(dataDirCustom);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 0, -1);
        dataDirectory = new QLineEdit(frame);
        dataDirectory->setObjectName(QString::fromUtf8("dataDirectory"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dataDirectory->sizePolicy().hasHeightForWidth());
        dataDirectory->setSizePolicy(sizePolicy);
        dataDirectory->setMinimumSize(QSize(725, 40));
        dataDirectory->setMaximumSize(QSize(725, 40));

        horizontalLayout_2->addWidget(dataDirectory, 0, Qt::AlignTop);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 2);
        ellipsisButton = new QPushButton(frame);
        ellipsisButton->setObjectName(QString::fromUtf8("ellipsisButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ellipsisButton->sizePolicy().hasHeightForWidth());
        ellipsisButton->setSizePolicy(sizePolicy1);
        ellipsisButton->setMinimumSize(QSize(50, 40));
        ellipsisButton->setMaximumSize(QSize(50, 16777215));
        ellipsisButton->setText(QString::fromUtf8("..."));
        ellipsisButton->setAutoDefault(false);

        verticalLayout_4->addWidget(ellipsisButton, 0, Qt::AlignRight|Qt::AlignVCenter);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        freeSpace = new QLabel(frame);
        freeSpace->setObjectName(QString::fromUtf8("freeSpace"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(freeSpace->sizePolicy().hasHeightForWidth());
        freeSpace->setSizePolicy(sizePolicy2);
        freeSpace->setMinimumSize(QSize(500, 0));
        freeSpace->setStyleSheet(QString::fromUtf8(""));
        freeSpace->setWordWrap(false);

        verticalLayout_2->addWidget(freeSpace, 0, Qt::AlignLeft);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        errorMessage = new QLabel(frame);
        errorMessage->setObjectName(QString::fromUtf8("errorMessage"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(errorMessage->sizePolicy().hasHeightForWidth());
        errorMessage->setSizePolicy(sizePolicy3);
        errorMessage->setMinimumSize(QSize(600, 0));
        errorMessage->setStyleSheet(QString::fromUtf8(""));
        errorMessage->setTextFormat(Qt::RichText);
        errorMessage->setWordWrap(false);

        verticalLayout_2->addWidget(errorMessage, 0, Qt::AlignLeft);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_6->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 50));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(535, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonCancel = new QPushButton(widget);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setMinimumSize(QSize(100, 40));

        horizontalLayout_3->addWidget(pushButtonCancel);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButtonOk = new QPushButton(widget);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        pushButtonOk->setMinimumSize(QSize(100, 40));

        horizontalLayout_3->addWidget(pushButtonOk);


        verticalLayout_6->addWidget(widget);


        verticalLayout_9->addWidget(frame);


        verticalLayout_3->addWidget(container, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout->addWidget(frame_2);


        retranslateUi(Intro);

        QMetaObject::connectSlotsByName(Intro);
    } // setupUi

    void retranslateUi(QDialog *Intro)
    {
        Intro->setWindowTitle(QCoreApplication::translate("Intro", "Welcome", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("Intro", "Welcome to %1.", nullptr));
        storageLabel->setText(QCoreApplication::translate("Intro", "As this is the first time the program is launched, you can choose where %1 will store its data.", nullptr));
        sizeWarningLabel->setText(QCoreApplication::translate("Intro", "%1 will download and store a copy of the AMMOcoin block chain. At least %2GB of data will be stored in this directory, and it will grow over time. The wallet will also be stored in this directory.", nullptr));
        dataDirDefault->setText(QCoreApplication::translate("Intro", "Use the default data directory", nullptr));
        dataDirCustom->setText(QCoreApplication::translate("Intro", "Use a custom data directory", nullptr));
        freeSpace->setText(QString());
        pushButtonCancel->setText(QCoreApplication::translate("Intro", "CANCEL", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("Intro", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Intro: public Ui_Intro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRO_H
