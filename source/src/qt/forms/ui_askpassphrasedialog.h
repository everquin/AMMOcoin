/********************************************************************************
** Form generated from reading UI file 'askpassphrasedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASKPASSPHRASEDIALOG_H
#define UI_ASKPASSPHRASEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AskPassphraseDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *left;
    QVBoxLayout *left_3;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayoutTitle;
    QLabel *labelTitle;
    QPushButton *btnEsc;
    QLabel *warningLabel;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QLabel *passLabel1;
    QWidget *layoutEdit;
    QHBoxLayout *horizontalLayout;
    QLineEdit *passEdit1;
    QVBoxLayout *verticalLayout_9;
    QLabel *passLabel2;
    QWidget *layoutEdit2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *passEdit2;
    QVBoxLayout *verticalLayout_10;
    QLabel *passLabel3;
    QLineEdit *passEdit3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QLabel *passWarningLabel;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonOk;

    void setupUi(QDialog *AskPassphraseDialog)
    {
        if (AskPassphraseDialog->objectName().isEmpty())
            AskPassphraseDialog->setObjectName(QString::fromUtf8("AskPassphraseDialog"));
        AskPassphraseDialog->resize(550, 565);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AskPassphraseDialog->sizePolicy().hasHeightForWidth());
        AskPassphraseDialog->setSizePolicy(sizePolicy);
        AskPassphraseDialog->setMinimumSize(QSize(550, 0));
        AskPassphraseDialog->setMaximumSize(QSize(550, 16777215));
        verticalLayout = new QVBoxLayout(AskPassphraseDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        left = new QWidget(AskPassphraseDialog);
        left->setObjectName(QString::fromUtf8("left"));
        left->setStyleSheet(QString::fromUtf8(""));
        left_3 = new QVBoxLayout(left);
        left_3->setSpacing(20);
        left_3->setObjectName(QString::fromUtf8("left_3"));
        left_3->setContentsMargins(20, 20, 20, 20);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget = new QWidget(left);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("padding-left:24px;"));
        verticalLayoutTitle = new QVBoxLayout(widget);
        verticalLayoutTitle->setSpacing(5);
        verticalLayoutTitle->setObjectName(QString::fromUtf8("verticalLayoutTitle"));
        labelTitle = new QLabel(widget);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setText(QString::fromUtf8("N/A"));
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayoutTitle->addWidget(labelTitle, 0, Qt::AlignHCenter);


        horizontalLayout_3->addWidget(widget);

        btnEsc = new QPushButton(left);
        btnEsc->setObjectName(QString::fromUtf8("btnEsc"));
        btnEsc->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_3->addWidget(btnEsc);


        left_3->addLayout(horizontalLayout_3);

        warningLabel = new QLabel(left);
        warningLabel->setObjectName(QString::fromUtf8("warningLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(warningLabel->sizePolicy().hasHeightForWidth());
        warningLabel->setSizePolicy(sizePolicy1);
        warningLabel->setMinimumSize(QSize(400, 0));
        warningLabel->setText(QString::fromUtf8("Placeholder text"));
        warningLabel->setTextFormat(Qt::RichText);
        warningLabel->setAlignment(Qt::AlignCenter);
        warningLabel->setWordWrap(true);

        left_3->addWidget(warningLabel, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(5);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        passLabel1 = new QLabel(left);
        passLabel1->setObjectName(QString::fromUtf8("passLabel1"));
        passLabel1->setMinimumSize(QSize(0, 20));
        passLabel1->setMaximumSize(QSize(16777215, 20));
        passLabel1->setText(QString::fromUtf8("N/A"));

        verticalLayout_7->addWidget(passLabel1, 0, Qt::AlignHCenter);

        layoutEdit = new QWidget(left);
        layoutEdit->setObjectName(QString::fromUtf8("layoutEdit"));
        horizontalLayout = new QHBoxLayout(layoutEdit);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        passEdit1 = new QLineEdit(layoutEdit);
        passEdit1->setObjectName(QString::fromUtf8("passEdit1"));
        passEdit1->setMinimumSize(QSize(0, 50));
        passEdit1->setMaximumSize(QSize(16777215, 50));
        passEdit1->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(passEdit1);


        verticalLayout_7->addWidget(layoutEdit);


        horizontalLayout_6->addLayout(verticalLayout_7);

        horizontalLayout_6->setStretch(0, 2);

        left_3->addLayout(horizontalLayout_6);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(5);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        passLabel2 = new QLabel(left);
        passLabel2->setObjectName(QString::fromUtf8("passLabel2"));
        passLabel2->setText(QString::fromUtf8("N/A"));

        verticalLayout_9->addWidget(passLabel2, 0, Qt::AlignHCenter);

        layoutEdit2 = new QWidget(left);
        layoutEdit2->setObjectName(QString::fromUtf8("layoutEdit2"));
        horizontalLayout_2 = new QHBoxLayout(layoutEdit2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        passEdit2 = new QLineEdit(layoutEdit2);
        passEdit2->setObjectName(QString::fromUtf8("passEdit2"));
        passEdit2->setMinimumSize(QSize(0, 50));
        passEdit2->setMaximumSize(QSize(16777215, 50));
        passEdit2->setEchoMode(QLineEdit::Password);
        passEdit2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(passEdit2);


        verticalLayout_9->addWidget(layoutEdit2);


        left_3->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(5);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        passLabel3 = new QLabel(left);
        passLabel3->setObjectName(QString::fromUtf8("passLabel3"));
        passLabel3->setText(QString::fromUtf8("N/A"));

        verticalLayout_10->addWidget(passLabel3, 0, Qt::AlignHCenter);

        passEdit3 = new QLineEdit(left);
        passEdit3->setObjectName(QString::fromUtf8("passEdit3"));
        passEdit3->setMinimumSize(QSize(0, 50));
        passEdit3->setMaximumSize(QSize(16777215, 50));
        passEdit3->setEchoMode(QLineEdit::Password);
        passEdit3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_10->addWidget(passEdit3);


        left_3->addLayout(verticalLayout_10);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        passWarningLabel = new QLabel(left);
        passWarningLabel->setObjectName(QString::fromUtf8("passWarningLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        passWarningLabel->setFont(font);
        passWarningLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(passWarningLabel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        pushButtonOk = new QPushButton(left);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        pushButtonOk->setMinimumSize(QSize(200, 50));
        pushButtonOk->setMaximumSize(QSize(200, 50));
        pushButtonOk->setText(QString::fromUtf8("N/A"));

        horizontalLayout_7->addWidget(pushButtonOk);


        left_3->addLayout(horizontalLayout_7);


        verticalLayout->addWidget(left);


        retranslateUi(AskPassphraseDialog);

        QMetaObject::connectSlotsByName(AskPassphraseDialog);
    } // setupUi

    void retranslateUi(QDialog *AskPassphraseDialog)
    {
        AskPassphraseDialog->setWindowTitle(QCoreApplication::translate("AskPassphraseDialog", "Passphrase Dialog", nullptr));
        btnEsc->setText(QString());
        passWarningLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AskPassphraseDialog: public Ui_AskPassphraseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASKPASSPHRASEDIALOG_H
