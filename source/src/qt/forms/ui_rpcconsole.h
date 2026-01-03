/********************************************************************************
** Form generated from reading UI file 'rpcconsole.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RPCCONSOLE_H
#define UI_RPCCONSOLE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "trafficgraphwidget.h"

QT_BEGIN_NAMESPACE

class Ui_RPCConsole
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_info;
    QGridLayout *gridLayout;
    QLabel *generalHeader;
    QLabel *clientNameLabel;
    QLabel *clientName;
    QLabel *clientVersionLabel;
    QLabel *clientVersion;
    QLabel *berkeleyDBVersionLabel;
    QLabel *berkeleyDBVersion;
    QLabel *startupTimeLabel;
    QLabel *startupTime;
    QLabel *dataDirLabel;
    QLabel *dataDir;
    QLabel *networkHeader;
    QLabel *networkNameLabel;
    QLabel *networkName;
    QLabel *numberOfConnectionsLabel;
    QLabel *numberOfConnections;
    QLabel *masternodeCountLabel;
    QLabel *masternodeCount;
    QLabel *blockchainHeader;
    QLabel *numberOfBlocksLabel;
    QLabel *numberOfBlocks;
    QLabel *lastBlockTimeLabel;
    QLabel *lastBlockTime;
    QLabel *lastBlockHashLabel;
    QLabel *lastBlockHash;
    QSpacerItem *verticalSpacer_2;
    QLabel *debugLogFileHeader;
    QPushButton *openDebugLogfileButton;
    QWidget *tab_console;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *messagesWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *clearButton;
    QWidget *tab_nettraffic;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    TrafficGraphWidget *trafficGraph;
    QHBoxLayout *horizontalLayout_2;
    QSlider *sldGraphRange;
    QLabel *lblGraphRange;
    QPushButton *btnClearTrafficGraph;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QFrame *line;
    QLabel *label_16;
    QLabel *lblBytesIn;
    QHBoxLayout *horizontalLayout_5;
    QFrame *line_2;
    QLabel *label_17;
    QLabel *lblBytesOut;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_peers;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_101;
    QTableView *peerWidget;
    QLabel *banHeading;
    QTableView *banlistWidget;
    QLabel *peerHeading;
    QWidget *detailWidget;
    QGridLayout *gridLayout_3;
    QLabel *label_30;
    QLabel *peerWhitelisted;
    QLabel *label_23;
    QLabel *peerDirection;
    QLabel *label_21;
    QLabel *peerVersion;
    QLabel *label_28;
    QLabel *peerSubversion;
    QLabel *label_4;
    QLabel *peerServices;
    QLabel *label_29;
    QLabel *peerHeight;
    QLabel *label_27;
    QLabel *peerSyncHeight;
    QLabel *label_25;
    QLabel *peerCommonHeight;
    QLabel *label_24;
    QLabel *peerBanScore;
    QLabel *label_22;
    QLabel *peerConnTime;
    QLabel *label_15;
    QLabel *peerLastSend;
    QLabel *label_19;
    QLabel *peerLastRecv;
    QLabel *label_18;
    QLabel *peerBytesSent;
    QLabel *label_20;
    QLabel *peerBytesRecv;
    QLabel *label_26;
    QLabel *peerPingTime;
    QLabel *peerPingWaitLabel;
    QLabel *peerPingWait;
    QLabel *label_timeoffset;
    QLabel *timeoffset;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_repair;
    QGridLayout *gridLayout_4;
    QLabel *label_repair_header;
    QLabel *label_repair_helptext;
    QLabel *wallet_path_label;
    QLabel *wallet_path;
    QSpacerItem *verticalSpacer_repair1;
    QPushButton *btn_salvagewallet;
    QLabel *label_repair_salvage_command;
    QLabel *label_repair_salvage;
    QPushButton *btn_rescan;
    QLabel *label_repair_rescan_command;
    QLabel *label_repair_rescan;
    QPushButton *btn_zapwallettxes1;
    QLabel *label_repair_zap1_command;
    QLabel *label_repair_zap1;
    QPushButton *btn_zapwallettxes2;
    QLabel *label_repair_zap2_command;
    QLabel *label_repair_zap2;
    QPushButton *btn_upgradewallet;
    QLabel *label_repair_upgrade_command;
    QLabel *label_repair_upgrade;
    QPushButton *btn_reindex;
    QLabel *label_repair_reindex_command;
    QLabel *label_repair_reindex;
    QPushButton *btn_resync;
    QLabel *label_repair_resync_command;
    QLabel *label_repair_resync;
    QSpacerItem *verticalSpacer_repair2;

    void setupUi(QDialog *RPCConsole)
    {
        if (RPCConsole->objectName().isEmpty())
            RPCConsole->setObjectName(QString::fromUtf8("RPCConsole"));
        RPCConsole->resize(769, 498);
        verticalLayout_2 = new QVBoxLayout(RPCConsole);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(RPCConsole);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_info = new QWidget();
        tab_info->setObjectName(QString::fromUtf8("tab_info"));
        gridLayout = new QGridLayout(tab_info);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(12);
        generalHeader = new QLabel(tab_info);
        generalHeader->setObjectName(QString::fromUtf8("generalHeader"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        generalHeader->setFont(font);

        gridLayout->addWidget(generalHeader, 0, 0, 1, 1);

        clientNameLabel = new QLabel(tab_info);
        clientNameLabel->setObjectName(QString::fromUtf8("clientNameLabel"));

        gridLayout->addWidget(clientNameLabel, 1, 0, 1, 1);

        clientName = new QLabel(tab_info);
        clientName->setObjectName(QString::fromUtf8("clientName"));
        clientName->setCursor(QCursor(Qt::IBeamCursor));
        clientName->setText(QString::fromUtf8("N/A"));
        clientName->setTextFormat(Qt::PlainText);
        clientName->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(clientName, 1, 1, 1, 1);

        clientVersionLabel = new QLabel(tab_info);
        clientVersionLabel->setObjectName(QString::fromUtf8("clientVersionLabel"));

        gridLayout->addWidget(clientVersionLabel, 2, 0, 1, 1);

        clientVersion = new QLabel(tab_info);
        clientVersion->setObjectName(QString::fromUtf8("clientVersion"));
        clientVersion->setCursor(QCursor(Qt::IBeamCursor));
        clientVersion->setText(QString::fromUtf8("N/A"));
        clientVersion->setTextFormat(Qt::PlainText);
        clientVersion->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(clientVersion, 2, 1, 1, 1);

        berkeleyDBVersionLabel = new QLabel(tab_info);
        berkeleyDBVersionLabel->setObjectName(QString::fromUtf8("berkeleyDBVersionLabel"));
        berkeleyDBVersionLabel->setIndent(10);

        gridLayout->addWidget(berkeleyDBVersionLabel, 3, 0, 1, 1);

        berkeleyDBVersion = new QLabel(tab_info);
        berkeleyDBVersion->setObjectName(QString::fromUtf8("berkeleyDBVersion"));
        berkeleyDBVersion->setCursor(QCursor(Qt::IBeamCursor));
        berkeleyDBVersion->setText(QString::fromUtf8("N/A"));
        berkeleyDBVersion->setTextFormat(Qt::PlainText);
        berkeleyDBVersion->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(berkeleyDBVersion, 3, 1, 1, 1);

        startupTimeLabel = new QLabel(tab_info);
        startupTimeLabel->setObjectName(QString::fromUtf8("startupTimeLabel"));

        gridLayout->addWidget(startupTimeLabel, 4, 0, 1, 1);

        startupTime = new QLabel(tab_info);
        startupTime->setObjectName(QString::fromUtf8("startupTime"));
        startupTime->setCursor(QCursor(Qt::IBeamCursor));
        startupTime->setText(QString::fromUtf8("N/A"));
        startupTime->setTextFormat(Qt::PlainText);
        startupTime->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(startupTime, 4, 1, 1, 1);

        dataDirLabel = new QLabel(tab_info);
        dataDirLabel->setObjectName(QString::fromUtf8("dataDirLabel"));

        gridLayout->addWidget(dataDirLabel, 5, 0, 1, 1);

        dataDir = new QLabel(tab_info);
        dataDir->setObjectName(QString::fromUtf8("dataDir"));
        dataDir->setText(QString::fromUtf8("N/A"));

        gridLayout->addWidget(dataDir, 5, 1, 1, 1);

        networkHeader = new QLabel(tab_info);
        networkHeader->setObjectName(QString::fromUtf8("networkHeader"));
        networkHeader->setFont(font);

        gridLayout->addWidget(networkHeader, 6, 0, 1, 1);

        networkNameLabel = new QLabel(tab_info);
        networkNameLabel->setObjectName(QString::fromUtf8("networkNameLabel"));

        gridLayout->addWidget(networkNameLabel, 7, 0, 1, 1);

        networkName = new QLabel(tab_info);
        networkName->setObjectName(QString::fromUtf8("networkName"));
        networkName->setCursor(QCursor(Qt::IBeamCursor));
        networkName->setText(QString::fromUtf8("N/A"));
        networkName->setTextFormat(Qt::PlainText);
        networkName->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(networkName, 7, 1, 1, 1);

        numberOfConnectionsLabel = new QLabel(tab_info);
        numberOfConnectionsLabel->setObjectName(QString::fromUtf8("numberOfConnectionsLabel"));

        gridLayout->addWidget(numberOfConnectionsLabel, 8, 0, 1, 1);

        numberOfConnections = new QLabel(tab_info);
        numberOfConnections->setObjectName(QString::fromUtf8("numberOfConnections"));
        numberOfConnections->setCursor(QCursor(Qt::IBeamCursor));
        numberOfConnections->setText(QString::fromUtf8("N/A"));
        numberOfConnections->setTextFormat(Qt::PlainText);
        numberOfConnections->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(numberOfConnections, 8, 1, 1, 1);

        masternodeCountLabel = new QLabel(tab_info);
        masternodeCountLabel->setObjectName(QString::fromUtf8("masternodeCountLabel"));

        gridLayout->addWidget(masternodeCountLabel, 9, 0, 1, 1);

        masternodeCount = new QLabel(tab_info);
        masternodeCount->setObjectName(QString::fromUtf8("masternodeCount"));
        masternodeCount->setCursor(QCursor(Qt::IBeamCursor));
        masternodeCount->setText(QString::fromUtf8("N/A"));
        masternodeCount->setTextFormat(Qt::PlainText);
        masternodeCount->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(masternodeCount, 9, 1, 1, 1);

        blockchainHeader = new QLabel(tab_info);
        blockchainHeader->setObjectName(QString::fromUtf8("blockchainHeader"));
        blockchainHeader->setFont(font);

        gridLayout->addWidget(blockchainHeader, 10, 0, 1, 1);

        numberOfBlocksLabel = new QLabel(tab_info);
        numberOfBlocksLabel->setObjectName(QString::fromUtf8("numberOfBlocksLabel"));

        gridLayout->addWidget(numberOfBlocksLabel, 11, 0, 1, 1);

        numberOfBlocks = new QLabel(tab_info);
        numberOfBlocks->setObjectName(QString::fromUtf8("numberOfBlocks"));
        numberOfBlocks->setCursor(QCursor(Qt::IBeamCursor));
        numberOfBlocks->setText(QString::fromUtf8("N/A"));
        numberOfBlocks->setTextFormat(Qt::PlainText);
        numberOfBlocks->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(numberOfBlocks, 11, 1, 1, 1);

        lastBlockTimeLabel = new QLabel(tab_info);
        lastBlockTimeLabel->setObjectName(QString::fromUtf8("lastBlockTimeLabel"));

        gridLayout->addWidget(lastBlockTimeLabel, 12, 0, 1, 1);

        lastBlockTime = new QLabel(tab_info);
        lastBlockTime->setObjectName(QString::fromUtf8("lastBlockTime"));
        lastBlockTime->setCursor(QCursor(Qt::IBeamCursor));
        lastBlockTime->setText(QString::fromUtf8("N/A"));
        lastBlockTime->setTextFormat(Qt::PlainText);
        lastBlockTime->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(lastBlockTime, 12, 1, 1, 1);

        lastBlockHashLabel = new QLabel(tab_info);
        lastBlockHashLabel->setObjectName(QString::fromUtf8("lastBlockHashLabel"));

        gridLayout->addWidget(lastBlockHashLabel, 13, 0, 1, 1);

        lastBlockHash = new QLabel(tab_info);
        lastBlockHash->setObjectName(QString::fromUtf8("lastBlockHash"));
        lastBlockHash->setText(QString::fromUtf8("N/A"));

        gridLayout->addWidget(lastBlockHash, 13, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 14, 0, 1, 1);

        debugLogFileHeader = new QLabel(tab_info);
        debugLogFileHeader->setObjectName(QString::fromUtf8("debugLogFileHeader"));
        debugLogFileHeader->setFont(font);

        gridLayout->addWidget(debugLogFileHeader, 15, 0, 1, 1);

        openDebugLogfileButton = new QPushButton(tab_info);
        openDebugLogfileButton->setObjectName(QString::fromUtf8("openDebugLogfileButton"));
        openDebugLogfileButton->setAutoDefault(false);

        gridLayout->addWidget(openDebugLogfileButton, 16, 0, 1, 1);

        tabWidget->addTab(tab_info, QString());
        tab_console = new QWidget();
        tab_console->setObjectName(QString::fromUtf8("tab_console"));
        verticalLayout_3 = new QVBoxLayout(tab_console);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        messagesWidget = new QTextEdit(tab_console);
        messagesWidget->setObjectName(QString::fromUtf8("messagesWidget"));
        messagesWidget->setMinimumSize(QSize(0, 100));
        messagesWidget->setReadOnly(true);
        messagesWidget->setProperty("tabKeyNavigation", QVariant(false));
        messagesWidget->setProperty("columnCount", QVariant(2));

        verticalLayout_3->addWidget(messagesWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tab_console);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8(">"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(tab_console);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        clearButton = new QPushButton(tab_console);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setMaximumSize(QSize(24, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/remove"), QSize(), QIcon::Normal, QIcon::Off);
        clearButton->setIcon(icon);
#if QT_CONFIG(shortcut)
        clearButton->setShortcut(QString::fromUtf8("Ctrl+L"));
#endif // QT_CONFIG(shortcut)
        clearButton->setAutoDefault(false);

        horizontalLayout->addWidget(clearButton);


        verticalLayout_3->addLayout(horizontalLayout);

        tabWidget->addTab(tab_console, QString());
        tab_nettraffic = new QWidget();
        tab_nettraffic->setObjectName(QString::fromUtf8("tab_nettraffic"));
        horizontalLayout_3 = new QHBoxLayout(tab_nettraffic);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        trafficGraph = new TrafficGraphWidget(tab_nettraffic);
        trafficGraph->setObjectName(QString::fromUtf8("trafficGraph"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(trafficGraph->sizePolicy().hasHeightForWidth());
        trafficGraph->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(trafficGraph);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        sldGraphRange = new QSlider(tab_nettraffic);
        sldGraphRange->setObjectName(QString::fromUtf8("sldGraphRange"));
        sldGraphRange->setMinimum(1);
        sldGraphRange->setMaximum(288);
        sldGraphRange->setPageStep(12);
        sldGraphRange->setValue(6);
        sldGraphRange->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sldGraphRange);

        lblGraphRange = new QLabel(tab_nettraffic);
        lblGraphRange->setObjectName(QString::fromUtf8("lblGraphRange"));
        lblGraphRange->setMinimumSize(QSize(100, 0));
        lblGraphRange->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblGraphRange);

        btnClearTrafficGraph = new QPushButton(tab_nettraffic);
        btnClearTrafficGraph->setObjectName(QString::fromUtf8("btnClearTrafficGraph"));
        btnClearTrafficGraph->setAutoDefault(false);

        horizontalLayout_2->addWidget(btnClearTrafficGraph);


        verticalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tab_nettraffic);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setMinimumSize(QSize(10, 0));
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        line->setPalette(palette);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_4->addWidget(label_16);

        lblBytesIn = new QLabel(groupBox);
        lblBytesIn->setObjectName(QString::fromUtf8("lblBytesIn"));
        lblBytesIn->setMinimumSize(QSize(50, 0));
        lblBytesIn->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(lblBytesIn);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        sizePolicy1.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy1);
        line_2->setMinimumSize(QSize(10, 0));
        QPalette palette1;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        line_2->setPalette(palette1);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_2);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_5->addWidget(label_17);

        lblBytesOut = new QLabel(groupBox);
        lblBytesOut->setObjectName(QString::fromUtf8("lblBytesOut"));
        lblBytesOut->setMinimumSize(QSize(50, 0));
        lblBytesOut->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lblBytesOut);


        verticalLayout_5->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 407, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);


        verticalLayout->addWidget(groupBox);


        horizontalLayout_3->addLayout(verticalLayout);

        tabWidget->addTab(tab_nettraffic, QString());
        tab_peers = new QWidget();
        tab_peers->setObjectName(QString::fromUtf8("tab_peers"));
        gridLayout_2 = new QGridLayout(tab_peers);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_101 = new QVBoxLayout();
        verticalLayout_101->setSpacing(0);
        verticalLayout_101->setObjectName(QString::fromUtf8("verticalLayout_101"));
        peerWidget = new QTableView(tab_peers);
        peerWidget->setObjectName(QString::fromUtf8("peerWidget"));
        peerWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        peerWidget->setSortingEnabled(true);
        peerWidget->horizontalHeader()->setHighlightSections(false);

        verticalLayout_101->addWidget(peerWidget);

        banHeading = new QLabel(tab_peers);
        banHeading->setObjectName(QString::fromUtf8("banHeading"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(banHeading->sizePolicy().hasHeightForWidth());
        banHeading->setSizePolicy(sizePolicy2);
        banHeading->setMinimumSize(QSize(300, 32));
        banHeading->setMaximumSize(QSize(16777215, 32));
        QFont font1;
        font1.setPointSize(12);
        banHeading->setFont(font1);
        banHeading->setCursor(QCursor(Qt::IBeamCursor));
        banHeading->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        banHeading->setWordWrap(true);
        banHeading->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_101->addWidget(banHeading);

        banlistWidget = new QTableView(tab_peers);
        banlistWidget->setObjectName(QString::fromUtf8("banlistWidget"));
        sizePolicy.setHeightForWidth(banlistWidget->sizePolicy().hasHeightForWidth());
        banlistWidget->setSizePolicy(sizePolicy);
        banlistWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        banlistWidget->setSortingEnabled(true);
        banlistWidget->horizontalHeader()->setHighlightSections(false);

        verticalLayout_101->addWidget(banlistWidget);


        gridLayout_2->addLayout(verticalLayout_101, 0, 0, 2, 1);

        peerHeading = new QLabel(tab_peers);
        peerHeading->setObjectName(QString::fromUtf8("peerHeading"));
        sizePolicy2.setHeightForWidth(peerHeading->sizePolicy().hasHeightForWidth());
        peerHeading->setSizePolicy(sizePolicy2);
        peerHeading->setMinimumSize(QSize(300, 32));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        peerHeading->setFont(font2);
        peerHeading->setCursor(QCursor(Qt::IBeamCursor));
        peerHeading->setAlignment(Qt::AlignCenter);
        peerHeading->setWordWrap(true);
        peerHeading->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_2->addWidget(peerHeading, 0, 1, 1, 1);

        detailWidget = new QWidget(tab_peers);
        detailWidget->setObjectName(QString::fromUtf8("detailWidget"));
        detailWidget->setMinimumSize(QSize(300, 0));
        gridLayout_3 = new QGridLayout(detailWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_30 = new QLabel(detailWidget);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_3->addWidget(label_30, 0, 0, 1, 1);

        peerWhitelisted = new QLabel(detailWidget);
        peerWhitelisted->setObjectName(QString::fromUtf8("peerWhitelisted"));
        peerWhitelisted->setCursor(QCursor(Qt::IBeamCursor));
        peerWhitelisted->setText(QString::fromUtf8("N/A"));
        peerWhitelisted->setTextFormat(Qt::PlainText);
        peerWhitelisted->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerWhitelisted, 0, 2, 1, 1);

        label_23 = new QLabel(detailWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_3->addWidget(label_23, 1, 0, 1, 1);

        peerDirection = new QLabel(detailWidget);
        peerDirection->setObjectName(QString::fromUtf8("peerDirection"));
        peerDirection->setCursor(QCursor(Qt::IBeamCursor));
        peerDirection->setText(QString::fromUtf8("N/A"));
        peerDirection->setTextFormat(Qt::PlainText);
        peerDirection->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerDirection, 1, 2, 1, 1);

        label_21 = new QLabel(detailWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_3->addWidget(label_21, 2, 0, 1, 1);

        peerVersion = new QLabel(detailWidget);
        peerVersion->setObjectName(QString::fromUtf8("peerVersion"));
        peerVersion->setCursor(QCursor(Qt::IBeamCursor));
        peerVersion->setText(QString::fromUtf8("N/A"));
        peerVersion->setTextFormat(Qt::PlainText);
        peerVersion->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerVersion, 2, 2, 1, 1);

        label_28 = new QLabel(detailWidget);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_3->addWidget(label_28, 3, 0, 1, 1);

        peerSubversion = new QLabel(detailWidget);
        peerSubversion->setObjectName(QString::fromUtf8("peerSubversion"));
        peerSubversion->setCursor(QCursor(Qt::IBeamCursor));
        peerSubversion->setText(QString::fromUtf8("N/A"));
        peerSubversion->setTextFormat(Qt::PlainText);
        peerSubversion->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerSubversion, 3, 2, 1, 1);

        label_4 = new QLabel(detailWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 4, 0, 1, 1);

        peerServices = new QLabel(detailWidget);
        peerServices->setObjectName(QString::fromUtf8("peerServices"));
        peerServices->setCursor(QCursor(Qt::IBeamCursor));
        peerServices->setText(QString::fromUtf8("N/A"));
        peerServices->setTextFormat(Qt::PlainText);
        peerServices->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerServices, 4, 2, 1, 1);

        label_29 = new QLabel(detailWidget);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_3->addWidget(label_29, 5, 0, 1, 1);

        peerHeight = new QLabel(detailWidget);
        peerHeight->setObjectName(QString::fromUtf8("peerHeight"));
        peerHeight->setCursor(QCursor(Qt::IBeamCursor));
        peerHeight->setText(QString::fromUtf8("N/A"));
        peerHeight->setTextFormat(Qt::PlainText);
        peerHeight->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerHeight, 5, 2, 1, 1);

        label_27 = new QLabel(detailWidget);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_3->addWidget(label_27, 6, 0, 1, 1);

        peerSyncHeight = new QLabel(detailWidget);
        peerSyncHeight->setObjectName(QString::fromUtf8("peerSyncHeight"));
        peerSyncHeight->setCursor(QCursor(Qt::IBeamCursor));
        peerSyncHeight->setText(QString::fromUtf8("N/A"));
        peerSyncHeight->setTextFormat(Qt::PlainText);
        peerSyncHeight->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerSyncHeight, 6, 2, 1, 1);

        label_25 = new QLabel(detailWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_3->addWidget(label_25, 7, 0, 1, 1);

        peerCommonHeight = new QLabel(detailWidget);
        peerCommonHeight->setObjectName(QString::fromUtf8("peerCommonHeight"));
        peerCommonHeight->setCursor(QCursor(Qt::IBeamCursor));
        peerCommonHeight->setText(QString::fromUtf8("N/A"));
        peerCommonHeight->setTextFormat(Qt::PlainText);
        peerCommonHeight->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerCommonHeight, 7, 2, 1, 1);

        label_24 = new QLabel(detailWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_3->addWidget(label_24, 8, 0, 1, 1);

        peerBanScore = new QLabel(detailWidget);
        peerBanScore->setObjectName(QString::fromUtf8("peerBanScore"));
        peerBanScore->setCursor(QCursor(Qt::IBeamCursor));
        peerBanScore->setText(QString::fromUtf8("N/A"));
        peerBanScore->setTextFormat(Qt::PlainText);
        peerBanScore->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerBanScore, 8, 2, 1, 1);

        label_22 = new QLabel(detailWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_3->addWidget(label_22, 9, 0, 1, 1);

        peerConnTime = new QLabel(detailWidget);
        peerConnTime->setObjectName(QString::fromUtf8("peerConnTime"));
        peerConnTime->setCursor(QCursor(Qt::IBeamCursor));
        peerConnTime->setText(QString::fromUtf8("N/A"));
        peerConnTime->setTextFormat(Qt::PlainText);
        peerConnTime->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerConnTime, 9, 2, 1, 1);

        label_15 = new QLabel(detailWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 10, 0, 1, 1);

        peerLastSend = new QLabel(detailWidget);
        peerLastSend->setObjectName(QString::fromUtf8("peerLastSend"));
        peerLastSend->setCursor(QCursor(Qt::IBeamCursor));
        peerLastSend->setText(QString::fromUtf8("N/A"));
        peerLastSend->setTextFormat(Qt::PlainText);
        peerLastSend->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerLastSend, 10, 2, 1, 1);

        label_19 = new QLabel(detailWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_3->addWidget(label_19, 11, 0, 1, 1);

        peerLastRecv = new QLabel(detailWidget);
        peerLastRecv->setObjectName(QString::fromUtf8("peerLastRecv"));
        peerLastRecv->setCursor(QCursor(Qt::IBeamCursor));
        peerLastRecv->setText(QString::fromUtf8("N/A"));
        peerLastRecv->setTextFormat(Qt::PlainText);
        peerLastRecv->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerLastRecv, 11, 2, 1, 1);

        label_18 = new QLabel(detailWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_3->addWidget(label_18, 12, 0, 1, 1);

        peerBytesSent = new QLabel(detailWidget);
        peerBytesSent->setObjectName(QString::fromUtf8("peerBytesSent"));
        peerBytesSent->setCursor(QCursor(Qt::IBeamCursor));
        peerBytesSent->setText(QString::fromUtf8("N/A"));
        peerBytesSent->setTextFormat(Qt::PlainText);
        peerBytesSent->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerBytesSent, 12, 2, 1, 1);

        label_20 = new QLabel(detailWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_3->addWidget(label_20, 13, 0, 1, 1);

        peerBytesRecv = new QLabel(detailWidget);
        peerBytesRecv->setObjectName(QString::fromUtf8("peerBytesRecv"));
        peerBytesRecv->setCursor(QCursor(Qt::IBeamCursor));
        peerBytesRecv->setText(QString::fromUtf8("N/A"));
        peerBytesRecv->setTextFormat(Qt::PlainText);
        peerBytesRecv->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerBytesRecv, 13, 2, 1, 1);

        label_26 = new QLabel(detailWidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_3->addWidget(label_26, 14, 0, 1, 1);

        peerPingTime = new QLabel(detailWidget);
        peerPingTime->setObjectName(QString::fromUtf8("peerPingTime"));
        peerPingTime->setCursor(QCursor(Qt::IBeamCursor));
        peerPingTime->setText(QString::fromUtf8("N/A"));
        peerPingTime->setTextFormat(Qt::PlainText);
        peerPingTime->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerPingTime, 14, 2, 1, 1);

        peerPingWaitLabel = new QLabel(detailWidget);
        peerPingWaitLabel->setObjectName(QString::fromUtf8("peerPingWaitLabel"));

        gridLayout_3->addWidget(peerPingWaitLabel, 15, 0, 1, 1);

        peerPingWait = new QLabel(detailWidget);
        peerPingWait->setObjectName(QString::fromUtf8("peerPingWait"));
        peerPingWait->setCursor(QCursor(Qt::IBeamCursor));
        peerPingWait->setText(QString::fromUtf8("N/A"));
        peerPingWait->setTextFormat(Qt::PlainText);
        peerPingWait->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerPingWait, 15, 2, 1, 1);

        label_timeoffset = new QLabel(detailWidget);
        label_timeoffset->setObjectName(QString::fromUtf8("label_timeoffset"));

        gridLayout_3->addWidget(label_timeoffset, 16, 0, 1, 1);

        timeoffset = new QLabel(detailWidget);
        timeoffset->setObjectName(QString::fromUtf8("timeoffset"));
        timeoffset->setCursor(QCursor(Qt::IBeamCursor));
        timeoffset->setText(QString::fromUtf8("N/A"));
        timeoffset->setTextFormat(Qt::PlainText);
        timeoffset->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(timeoffset, 16, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 17, 1, 1, 1);


        gridLayout_2->addWidget(detailWidget, 1, 1, 1, 1);

        tabWidget->addTab(tab_peers, QString());
        tab_repair = new QWidget();
        tab_repair->setObjectName(QString::fromUtf8("tab_repair"));
        gridLayout_4 = new QGridLayout(tab_repair);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(12);
        label_repair_header = new QLabel(tab_repair);
        label_repair_header->setObjectName(QString::fromUtf8("label_repair_header"));
        label_repair_header->setFont(font);

        gridLayout_4->addWidget(label_repair_header, 0, 0, 1, 4);

        label_repair_helptext = new QLabel(tab_repair);
        label_repair_helptext->setObjectName(QString::fromUtf8("label_repair_helptext"));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        label_repair_helptext->setFont(font3);
        label_repair_helptext->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_helptext, 1, 0, 1, 4);

        wallet_path_label = new QLabel(tab_repair);
        wallet_path_label->setObjectName(QString::fromUtf8("wallet_path_label"));

        gridLayout_4->addWidget(wallet_path_label, 2, 0, 1, 1);

        wallet_path = new QLabel(tab_repair);
        wallet_path->setObjectName(QString::fromUtf8("wallet_path"));
        wallet_path->setCursor(QCursor(Qt::IBeamCursor));
        wallet_path->setText(QString::fromUtf8("N/A"));
        wallet_path->setTextFormat(Qt::PlainText);
        wallet_path->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_4->addWidget(wallet_path, 2, 1, 1, 3);

        verticalSpacer_repair1 = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_repair1, 3, 0, 1, 1);

        btn_salvagewallet = new QPushButton(tab_repair);
        btn_salvagewallet->setObjectName(QString::fromUtf8("btn_salvagewallet"));
        btn_salvagewallet->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_salvagewallet, 4, 0, 1, 2);

        label_repair_salvage_command = new QLabel(tab_repair);
        label_repair_salvage_command->setObjectName(QString::fromUtf8("label_repair_salvage_command"));
        label_repair_salvage_command->setText(QString::fromUtf8("-salvagewallet:"));

        gridLayout_4->addWidget(label_repair_salvage_command, 4, 2, 1, 1);

        label_repair_salvage = new QLabel(tab_repair);
        label_repair_salvage->setObjectName(QString::fromUtf8("label_repair_salvage"));
        label_repair_salvage->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_salvage, 4, 3, 1, 1);

        btn_rescan = new QPushButton(tab_repair);
        btn_rescan->setObjectName(QString::fromUtf8("btn_rescan"));
        btn_rescan->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_rescan, 5, 0, 1, 2);

        label_repair_rescan_command = new QLabel(tab_repair);
        label_repair_rescan_command->setObjectName(QString::fromUtf8("label_repair_rescan_command"));
        label_repair_rescan_command->setText(QString::fromUtf8("-rescan:"));

        gridLayout_4->addWidget(label_repair_rescan_command, 5, 2, 1, 1);

        label_repair_rescan = new QLabel(tab_repair);
        label_repair_rescan->setObjectName(QString::fromUtf8("label_repair_rescan"));
        label_repair_rescan->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_rescan, 5, 3, 1, 1);

        btn_zapwallettxes1 = new QPushButton(tab_repair);
        btn_zapwallettxes1->setObjectName(QString::fromUtf8("btn_zapwallettxes1"));
        btn_zapwallettxes1->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_zapwallettxes1, 6, 0, 1, 2);

        label_repair_zap1_command = new QLabel(tab_repair);
        label_repair_zap1_command->setObjectName(QString::fromUtf8("label_repair_zap1_command"));
        label_repair_zap1_command->setText(QString::fromUtf8("-zapwallettxes=1:"));

        gridLayout_4->addWidget(label_repair_zap1_command, 6, 2, 1, 1);

        label_repair_zap1 = new QLabel(tab_repair);
        label_repair_zap1->setObjectName(QString::fromUtf8("label_repair_zap1"));
        label_repair_zap1->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_zap1, 6, 3, 1, 1);

        btn_zapwallettxes2 = new QPushButton(tab_repair);
        btn_zapwallettxes2->setObjectName(QString::fromUtf8("btn_zapwallettxes2"));
        btn_zapwallettxes2->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_zapwallettxes2, 7, 0, 1, 2);

        label_repair_zap2_command = new QLabel(tab_repair);
        label_repair_zap2_command->setObjectName(QString::fromUtf8("label_repair_zap2_command"));
        label_repair_zap2_command->setText(QString::fromUtf8("-zapwallettxes=2:"));

        gridLayout_4->addWidget(label_repair_zap2_command, 7, 2, 1, 1);

        label_repair_zap2 = new QLabel(tab_repair);
        label_repair_zap2->setObjectName(QString::fromUtf8("label_repair_zap2"));
        label_repair_zap2->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_zap2, 7, 3, 1, 1);

        btn_upgradewallet = new QPushButton(tab_repair);
        btn_upgradewallet->setObjectName(QString::fromUtf8("btn_upgradewallet"));
        btn_upgradewallet->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_upgradewallet, 8, 0, 1, 2);

        label_repair_upgrade_command = new QLabel(tab_repair);
        label_repair_upgrade_command->setObjectName(QString::fromUtf8("label_repair_upgrade_command"));
        label_repair_upgrade_command->setText(QString::fromUtf8("-upgradewallet:"));

        gridLayout_4->addWidget(label_repair_upgrade_command, 8, 2, 1, 1);

        label_repair_upgrade = new QLabel(tab_repair);
        label_repair_upgrade->setObjectName(QString::fromUtf8("label_repair_upgrade"));
        label_repair_upgrade->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_upgrade, 8, 3, 1, 1);

        btn_reindex = new QPushButton(tab_repair);
        btn_reindex->setObjectName(QString::fromUtf8("btn_reindex"));
        btn_reindex->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_reindex, 9, 0, 1, 2);

        label_repair_reindex_command = new QLabel(tab_repair);
        label_repair_reindex_command->setObjectName(QString::fromUtf8("label_repair_reindex_command"));
        label_repair_reindex_command->setText(QString::fromUtf8("-reindex:"));

        gridLayout_4->addWidget(label_repair_reindex_command, 9, 2, 1, 1);

        label_repair_reindex = new QLabel(tab_repair);
        label_repair_reindex->setObjectName(QString::fromUtf8("label_repair_reindex"));
        label_repair_reindex->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_reindex, 9, 3, 1, 1);

        btn_resync = new QPushButton(tab_repair);
        btn_resync->setObjectName(QString::fromUtf8("btn_resync"));
        btn_resync->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_resync, 10, 0, 1, 2);

        label_repair_resync_command = new QLabel(tab_repair);
        label_repair_resync_command->setObjectName(QString::fromUtf8("label_repair_resync_command"));
        label_repair_resync_command->setText(QString::fromUtf8("-resync:"));

        gridLayout_4->addWidget(label_repair_resync_command, 10, 2, 1, 1);

        label_repair_resync = new QLabel(tab_repair);
        label_repair_resync->setObjectName(QString::fromUtf8("label_repair_resync"));
        label_repair_resync->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_resync, 10, 3, 1, 1);

        verticalSpacer_repair2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_repair2, 11, 0, 1, 1);

        tabWidget->addTab(tab_repair, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(RPCConsole);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RPCConsole);
    } // setupUi

    void retranslateUi(QDialog *RPCConsole)
    {
        RPCConsole->setWindowTitle(QCoreApplication::translate("RPCConsole", "Tools window", nullptr));
        generalHeader->setText(QCoreApplication::translate("RPCConsole", "General", nullptr));
        clientNameLabel->setText(QCoreApplication::translate("RPCConsole", "Client name", nullptr));
        clientVersionLabel->setText(QCoreApplication::translate("RPCConsole", "Client version", nullptr));
        berkeleyDBVersionLabel->setText(QCoreApplication::translate("RPCConsole", "Using BerkeleyDB version", nullptr));
        startupTimeLabel->setText(QCoreApplication::translate("RPCConsole", "Startup time", nullptr));
        dataDirLabel->setText(QCoreApplication::translate("RPCConsole", "Data Directory", nullptr));
        networkHeader->setText(QCoreApplication::translate("RPCConsole", "Network", nullptr));
        networkNameLabel->setText(QCoreApplication::translate("RPCConsole", "Name", nullptr));
        numberOfConnectionsLabel->setText(QCoreApplication::translate("RPCConsole", "Number of connections", nullptr));
        masternodeCountLabel->setText(QCoreApplication::translate("RPCConsole", "Number of Masternodes", nullptr));
        blockchainHeader->setText(QCoreApplication::translate("RPCConsole", "Block chain", nullptr));
        numberOfBlocksLabel->setText(QCoreApplication::translate("RPCConsole", "Current number of blocks", nullptr));
        lastBlockTimeLabel->setText(QCoreApplication::translate("RPCConsole", "Last block time", nullptr));
        lastBlockHashLabel->setText(QCoreApplication::translate("RPCConsole", "Last block hash", nullptr));
        debugLogFileHeader->setText(QCoreApplication::translate("RPCConsole", "Debug log file", nullptr));
#if QT_CONFIG(tooltip)
        openDebugLogfileButton->setToolTip(QCoreApplication::translate("RPCConsole", "Open the AMMOcoin debug log file from the current data directory. This can take a few seconds for large log files.", nullptr));
#endif // QT_CONFIG(tooltip)
        openDebugLogfileButton->setText(QCoreApplication::translate("RPCConsole", "&Open", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_info), QCoreApplication::translate("RPCConsole", "&Information", nullptr));
#if QT_CONFIG(tooltip)
        clearButton->setToolTip(QCoreApplication::translate("RPCConsole", "Clear console", nullptr));
#endif // QT_CONFIG(tooltip)
        clearButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_console), QCoreApplication::translate("RPCConsole", "&Console", nullptr));
        btnClearTrafficGraph->setText(QCoreApplication::translate("RPCConsole", "&Clear", nullptr));
        groupBox->setTitle(QCoreApplication::translate("RPCConsole", "Totals", nullptr));
        label_16->setText(QCoreApplication::translate("RPCConsole", "Received", nullptr));
        label_17->setText(QCoreApplication::translate("RPCConsole", "Sent", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_nettraffic), QCoreApplication::translate("RPCConsole", "&Network Traffic", nullptr));
        banHeading->setText(QCoreApplication::translate("RPCConsole", "Banned peers", nullptr));
        peerHeading->setText(QCoreApplication::translate("RPCConsole", "Select a peer to view detailed information.", nullptr));
        label_30->setText(QCoreApplication::translate("RPCConsole", "Whitelisted", nullptr));
        label_23->setText(QCoreApplication::translate("RPCConsole", "Direction", nullptr));
        label_21->setText(QCoreApplication::translate("RPCConsole", "Protocol", nullptr));
        label_28->setText(QCoreApplication::translate("RPCConsole", "Version", nullptr));
        label_4->setText(QCoreApplication::translate("RPCConsole", "Services", nullptr));
        label_29->setText(QCoreApplication::translate("RPCConsole", "Starting Block", nullptr));
        label_27->setText(QCoreApplication::translate("RPCConsole", "Synced Headers", nullptr));
        label_25->setText(QCoreApplication::translate("RPCConsole", "Synced Blocks", nullptr));
        label_24->setText(QCoreApplication::translate("RPCConsole", "Ban Score", nullptr));
        label_22->setText(QCoreApplication::translate("RPCConsole", "Connection Time", nullptr));
        label_15->setText(QCoreApplication::translate("RPCConsole", "Last Send", nullptr));
        label_19->setText(QCoreApplication::translate("RPCConsole", "Last Receive", nullptr));
        label_18->setText(QCoreApplication::translate("RPCConsole", "Bytes Sent", nullptr));
        label_20->setText(QCoreApplication::translate("RPCConsole", "Bytes Received", nullptr));
        label_26->setText(QCoreApplication::translate("RPCConsole", "Ping Time", nullptr));
#if QT_CONFIG(tooltip)
        peerPingWaitLabel->setToolTip(QCoreApplication::translate("RPCConsole", "The duration of a currently outstanding ping.", nullptr));
#endif // QT_CONFIG(tooltip)
        peerPingWaitLabel->setText(QCoreApplication::translate("RPCConsole", "Ping Wait", nullptr));
        label_timeoffset->setText(QCoreApplication::translate("RPCConsole", "Time Offset", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_peers), QCoreApplication::translate("RPCConsole", "&Peers", nullptr));
        label_repair_header->setText(QCoreApplication::translate("RPCConsole", "Wallet repair options.", nullptr));
        label_repair_helptext->setText(QCoreApplication::translate("RPCConsole", "The buttons below will restart the wallet with command-line options to repair the wallet, fix issues with corrupt blockchain files or missing/obsolete transactions.", nullptr));
        wallet_path_label->setText(QCoreApplication::translate("RPCConsole", "Wallet In Use:", nullptr));
        btn_salvagewallet->setText(QCoreApplication::translate("RPCConsole", "Salvage wallet", nullptr));
        label_repair_salvage->setText(QCoreApplication::translate("RPCConsole", "Attempt to recover private keys from a corrupt wallet.dat.", nullptr));
        btn_rescan->setText(QCoreApplication::translate("RPCConsole", "Rescan blockchain files", nullptr));
        label_repair_rescan->setText(QCoreApplication::translate("RPCConsole", "Rescan the block chain for missing wallet transactions.", nullptr));
        btn_zapwallettxes1->setText(QCoreApplication::translate("RPCConsole", "Recover transactions 1", nullptr));
        label_repair_zap1->setText(QCoreApplication::translate("RPCConsole", "Recover transactions from blockchain (keep meta-data, e.g. account owner).", nullptr));
        btn_zapwallettxes2->setText(QCoreApplication::translate("RPCConsole", "Recover transactions 2", nullptr));
        label_repair_zap2->setText(QCoreApplication::translate("RPCConsole", "Recover transactions from blockchain (drop meta-data).", nullptr));
        btn_upgradewallet->setText(QCoreApplication::translate("RPCConsole", "Upgrade wallet format", nullptr));
        label_repair_upgrade->setText(QCoreApplication::translate("RPCConsole", "Upgrade wallet to latest format on startup. (Note: this is NOT an update of the wallet itself!)", nullptr));
        btn_reindex->setText(QCoreApplication::translate("RPCConsole", "Rebuild index", nullptr));
        label_repair_reindex->setText(QCoreApplication::translate("RPCConsole", "Rebuild block chain index from current blk000??.dat files.", nullptr));
        btn_resync->setText(QCoreApplication::translate("RPCConsole", "Delete local Blockchain Folders", nullptr));
        label_repair_resync->setText(QCoreApplication::translate("RPCConsole", "Deletes all local blockchain folders so the wallet synchronizes from scratch.", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_repair), QCoreApplication::translate("RPCConsole", "&Wallet Repair", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RPCConsole: public Ui_RPCConsole {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RPCCONSOLE_H
