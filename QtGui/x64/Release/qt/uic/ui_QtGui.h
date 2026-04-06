/********************************************************************************
** Form generated from reading UI file 'QtGui.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUI_H
#define UI_QTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_34;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *hostIpLabel;
    QLineEdit *hostIpInput;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *hostIpConnectBtn;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_9;
    QLabel *deviceSelectLabel;
    QComboBox *deviceSelect;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *deviceIpLabel;
    QLineEdit *deviceIpInput;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *deviceTypeLabel;
    QLineEdit *deviceTypeInput;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *deviceMacLabel;
    QLineEdit *deviceMacInput;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_7;
    QLabel *deviceFirmwareLabel;
    QLineEdit *deviceFirmwareInput;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *deviceCmdPortLabel;
    QLineEdit *deviceCmdPortInput;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_8;
    QLabel *deviceImgPortLabel;
    QLineEdit *deviceImgPortInput;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *deviceSerialLabel;
    QLineEdit *deviceSerialInput;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *deviceInfoUpdateBtn;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_21;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_12;
    QLabel *acquisitionModeLabel;
    QComboBox *acquisitionModeInput;
    QSpacerItem *horizontalSpacer_9;
    QVBoxLayout *verticalLayout_20;
    QLabel *mechanicalModeLabel;
    QComboBox *mechanicalModeInput;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_15;
    QLabel *binningModeLabel;
    QComboBox *binningModeInput;
    QSpacerItem *horizontalSpacer_11;
    QVBoxLayout *verticalLayout_16;
    QLabel *gainModeLabel;
    QComboBox *gainModeInput;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_17;
    QLabel *integrationTimeLabel;
    QLineEdit *integrationTimeInput;
    QSpacerItem *horizontalSpacer_14;
    QVBoxLayout *verticalLayout_18;
    QLabel *intervalTimeLabel;
    QLineEdit *intervalTimeInput;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_14;
    QLabel *imageQuantityLabel;
    QStackedWidget *imageQuantityStackedWidget;
    QWidget *page_1;
    QComboBox *imageQuantityComboBox;
    QWidget *page_2;
    QLineEdit *imageQuantityInput;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_13;
    QLabel *totalTimeLabel;
    QLineEdit *totalTimeInput;
    QHBoxLayout *horizontalLayout_33;
    QVBoxLayout *verticalLayout_19;
    QLabel *filePrefixLabel;
    QLineEdit *filePrefixInput;
    QSpacerItem *horizontalSpacer_15;
    QVBoxLayout *verticalLayout_11;
    QLabel *filePathNameLabel;
    QHBoxLayout *horizontalLayout_17;
    QLineEdit *filePathInput;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *chooseFilePathBtn;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *grabBtn;
    QPushButton *stopGrabBtn;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_29;
    QVBoxLayout *verticalLayout_24;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_25;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_22;
    QLabel *label_5;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_27;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_28;
    QLabel *label_9;
    QLabel *label_10;
    QSpacerItem *verticalSpacer_3;
    QFrame *line;
    QWidget *widget;
    QVBoxLayout *verticalLayout_58;
    QSpacerItem *verticalSpacer_7;
    QFrame *frame;
    QVBoxLayout *verticalLayout_23;
    QLabel *imageLabel;
    QHBoxLayout *horizontalLayout_16;
    QVBoxLayout *verticalLayout_30;
    QLabel *currentDisplayedImageLabel;
    QLabel *currentProcessingImageLabel;
    QLabel *currentProgressLabel;
    QSpacerItem *horizontalSpacer_17;
    QVBoxLayout *verticalLayout_31;
    QLabel *elapsedTimeLabel;
    QLabel *remainingTimeLabel;
    QLabel *currentStatusLabel;
    QProgressBar *progressBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiClass)
    {
        if (QtGuiClass->objectName().isEmpty())
            QtGuiClass->setObjectName("QtGuiClass");
        QtGuiClass->resize(1000, 642);
        QtGuiClass->setMinimumSize(QSize(500, 0));
        QtGuiClass->setMaximumSize(QSize(1000, 16777215));
        QtGuiClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(QtGuiClass);
        centralWidget->setObjectName("centralWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout_34 = new QHBoxLayout(centralWidget);
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_34->setObjectName("horizontalLayout_34");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMaximumSize(QSize(500, 16777215));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8("* {\n"
"	font-family: \"Arial\";\n"
"    font-size: 12px;\n"
"	background-color: #FAFAFA;\n"
"	color: #000;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #D3D3D3; /* Cor de fundo das abas */\n"
"    color: #000;\n"
"    padding: 8px 12px;\n"
"    border: 1px solid #B1B1B1;\n"
"    border-bottom: none; /*Remove a borda inferior das abas */\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #FAFAFA; /* Fundo da aba selecionada */\n"
"	color: #000;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #B1B1B1; /* Borda ao redor do conte\303\272do */\n"
"    top: -1px; /* Sobe o conte\303\272do para \"colar\" na aba */\n"
"}\n"
"\n"
"QLineEdit {\n"
"	border: 1px solid #B1B1B1;\n"
"	border-radius: 20px;\n"
"	color: #0000;\n"
"	background-color: #FAFAFA;\n"
"	padding: 2px 4px 2px 4px;\n"
"}\n"
"\n"
"QLineEdit:disabled {\n"
"    background-color: #D3D3D3; /* Fundo cinza */\n"
"    color: #A9A9A9; /* Texto desbotado */\n"
"}\n"
"\n"
"QComboBox {\n"
"	border: 1px solid #B1B1B1;\n"
"	border"
                        "-radius: 20px;\n"
"	color: #000;\n"
"	backgroundColor: #FAFAFA;\n"
"	padding: 2px 4px 2px 4px;\n"
"}\n"
"\n"
"QComboBox:disabled {\n"
"    background-color: #D3D3D3; /* Fundo cinza */\n"
"    color: #A9A9A9; /* Texto desbotado */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    width: 20px;\n"
"	border: none;\n"
"	background-color: #FAFAFA;\n"
"}\n"
"\n"
"QComboBox::drop-down:disabled {\n"
"	background-color: #D3D3D3; /* Fundo cinza */\n"
"    color: #A9A9A9; /* Texto desbotado */\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: url(:/Assets/assets/select_arrow.png);\n"
"	width: 10px;\n"
"}\n"
"\n"
"QPushButton {\n"
"	padding: 3px 9px;\n"
"	border-radius: 3px;\n"
"	background-color: #888585;\n"
"	color: #FFF;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #7A7A7A;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #D3D3D3; /* Fundo cinza */\n"
"    color: #A9A9A9; /* Texto desbotado */\n"
"    border: 1px solid #CCCCCC;\n"
"    opacity: 0.6; /* Diminui a opacidade */\n"
"}\n"
""));
        tab_1 = new QWidget();
        tab_1->setObjectName("tab_1");
        verticalLayout_10 = new QVBoxLayout(tab_1);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(-1, 25, -1, 10);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, -1, 0, 0);
        hostIpLabel = new QLabel(tab_1);
        hostIpLabel->setObjectName("hostIpLabel");
        hostIpLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        hostIpLabel->setMargin(0);

        verticalLayout->addWidget(hostIpLabel);

        hostIpInput = new QLineEdit(tab_1);
        hostIpInput->setObjectName("hostIpInput");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(hostIpInput->sizePolicy().hasHeightForWidth());
        hostIpInput->setSizePolicy(sizePolicy2);
        hostIpInput->setMinimumSize(QSize(200, 0));
        hostIpInput->setMaximumSize(QSize(200, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        hostIpInput->setFont(font);
        hostIpInput->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        hostIpInput->setAutoFillBackground(false);
        hostIpInput->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(hostIpInput);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout_10->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 34);
        hostIpConnectBtn = new QPushButton(tab_1);
        hostIpConnectBtn->setObjectName("hostIpConnectBtn");

        horizontalLayout_2->addWidget(hostIpConnectBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_10->addLayout(horizontalLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(-1, -1, 0, 0);
        deviceSelectLabel = new QLabel(tab_1);
        deviceSelectLabel->setObjectName("deviceSelectLabel");
        sizePolicy2.setHeightForWidth(deviceSelectLabel->sizePolicy().hasHeightForWidth());
        deviceSelectLabel->setSizePolicy(sizePolicy2);
        deviceSelectLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        deviceSelectLabel->setMargin(0);

        verticalLayout_9->addWidget(deviceSelectLabel);

        deviceSelect = new QComboBox(tab_1);
        deviceSelect->setObjectName("deviceSelect");
        deviceSelect->setEnabled(false);
        deviceSelect->setMinimumSize(QSize(200, 0));
        deviceSelect->setMaximumSize(QSize(200, 16777215));

        verticalLayout_9->addWidget(deviceSelect);


        horizontalLayout_8->addLayout(verticalLayout_9);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        verticalLayout_10->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, -1, 0, -1);
        deviceIpLabel = new QLabel(tab_1);
        deviceIpLabel->setObjectName("deviceIpLabel");

        verticalLayout_2->addWidget(deviceIpLabel);

        deviceIpInput = new QLineEdit(tab_1);
        deviceIpInput->setObjectName("deviceIpInput");
        deviceIpInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(deviceIpInput->sizePolicy().hasHeightForWidth());
        deviceIpInput->setSizePolicy(sizePolicy2);
        deviceIpInput->setMinimumSize(QSize(200, 0));
        deviceIpInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_2->addWidget(deviceIpInput);


        horizontalLayout_7->addLayout(verticalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, -1, -1, -1);
        deviceTypeLabel = new QLabel(tab_1);
        deviceTypeLabel->setObjectName("deviceTypeLabel");

        verticalLayout_6->addWidget(deviceTypeLabel);

        deviceTypeInput = new QLineEdit(tab_1);
        deviceTypeInput->setObjectName("deviceTypeInput");
        deviceTypeInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(deviceTypeInput->sizePolicy().hasHeightForWidth());
        deviceTypeInput->setSizePolicy(sizePolicy2);
        deviceTypeInput->setMinimumSize(QSize(200, 0));
        deviceTypeInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_6->addWidget(deviceTypeInput);


        horizontalLayout_7->addLayout(verticalLayout_6);


        verticalLayout_10->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, -1, 0, 0);
        deviceMacLabel = new QLabel(tab_1);
        deviceMacLabel->setObjectName("deviceMacLabel");

        verticalLayout_3->addWidget(deviceMacLabel);

        deviceMacInput = new QLineEdit(tab_1);
        deviceMacInput->setObjectName("deviceMacInput");
        deviceMacInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(deviceMacInput->sizePolicy().hasHeightForWidth());
        deviceMacInput->setSizePolicy(sizePolicy2);
        deviceMacInput->setMinimumSize(QSize(200, 0));
        deviceMacInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_3->addWidget(deviceMacInput);


        horizontalLayout_6->addLayout(verticalLayout_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, -1, -1, 0);
        deviceFirmwareLabel = new QLabel(tab_1);
        deviceFirmwareLabel->setObjectName("deviceFirmwareLabel");

        verticalLayout_7->addWidget(deviceFirmwareLabel);

        deviceFirmwareInput = new QLineEdit(tab_1);
        deviceFirmwareInput->setObjectName("deviceFirmwareInput");
        deviceFirmwareInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(deviceFirmwareInput->sizePolicy().hasHeightForWidth());
        deviceFirmwareInput->setSizePolicy(sizePolicy2);
        deviceFirmwareInput->setMinimumSize(QSize(200, 0));
        deviceFirmwareInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_7->addWidget(deviceFirmwareInput);


        horizontalLayout_6->addLayout(verticalLayout_7);


        verticalLayout_10->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(-1, -1, 0, 0);
        deviceCmdPortLabel = new QLabel(tab_1);
        deviceCmdPortLabel->setObjectName("deviceCmdPortLabel");

        verticalLayout_4->addWidget(deviceCmdPortLabel);

        deviceCmdPortInput = new QLineEdit(tab_1);
        deviceCmdPortInput->setObjectName("deviceCmdPortInput");
        deviceCmdPortInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(deviceCmdPortInput->sizePolicy().hasHeightForWidth());
        deviceCmdPortInput->setSizePolicy(sizePolicy2);
        deviceCmdPortInput->setMinimumSize(QSize(200, 0));
        deviceCmdPortInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_4->addWidget(deviceCmdPortInput);


        horizontalLayout_5->addLayout(verticalLayout_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, -1, -1, 0);
        deviceImgPortLabel = new QLabel(tab_1);
        deviceImgPortLabel->setObjectName("deviceImgPortLabel");

        verticalLayout_8->addWidget(deviceImgPortLabel);

        deviceImgPortInput = new QLineEdit(tab_1);
        deviceImgPortInput->setObjectName("deviceImgPortInput");
        deviceImgPortInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(deviceImgPortInput->sizePolicy().hasHeightForWidth());
        deviceImgPortInput->setSizePolicy(sizePolicy2);
        deviceImgPortInput->setMinimumSize(QSize(200, 0));
        deviceImgPortInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_8->addWidget(deviceImgPortInput);


        horizontalLayout_5->addLayout(verticalLayout_8);


        verticalLayout_10->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(-1, -1, 0, 0);
        deviceSerialLabel = new QLabel(tab_1);
        deviceSerialLabel->setObjectName("deviceSerialLabel");

        verticalLayout_5->addWidget(deviceSerialLabel);

        deviceSerialInput = new QLineEdit(tab_1);
        deviceSerialInput->setObjectName("deviceSerialInput");
        deviceSerialInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(deviceSerialInput->sizePolicy().hasHeightForWidth());
        deviceSerialInput->setSizePolicy(sizePolicy2);
        deviceSerialInput->setMinimumSize(QSize(200, 0));
        deviceSerialInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_5->addWidget(deviceSerialInput);


        horizontalLayout_4->addLayout(verticalLayout_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_10->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, -1, -1, 25);
        deviceInfoUpdateBtn = new QPushButton(tab_1);
        deviceInfoUpdateBtn->setObjectName("deviceInfoUpdateBtn");
        deviceInfoUpdateBtn->setEnabled(false);

        horizontalLayout->addWidget(deviceInfoUpdateBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_10->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 95, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_10->addItem(verticalSpacer);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_21 = new QVBoxLayout(tab_2);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName("verticalLayout_21");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(-1, 25, -1, 10);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_12->setContentsMargins(-1, -1, 0, 0);
        acquisitionModeLabel = new QLabel(tab_2);
        acquisitionModeLabel->setObjectName("acquisitionModeLabel");
        sizePolicy2.setHeightForWidth(acquisitionModeLabel->sizePolicy().hasHeightForWidth());
        acquisitionModeLabel->setSizePolicy(sizePolicy2);
        acquisitionModeLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        acquisitionModeLabel->setMargin(0);

        verticalLayout_12->addWidget(acquisitionModeLabel);

        acquisitionModeInput = new QComboBox(tab_2);
        acquisitionModeInput->addItem(QString());
        acquisitionModeInput->addItem(QString());
        acquisitionModeInput->setObjectName("acquisitionModeInput");
        acquisitionModeInput->setEnabled(false);
        acquisitionModeInput->setMinimumSize(QSize(200, 0));
        acquisitionModeInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_12->addWidget(acquisitionModeInput);


        horizontalLayout_9->addLayout(verticalLayout_12);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName("verticalLayout_20");
        verticalLayout_20->setContentsMargins(-1, -1, 0, 0);
        mechanicalModeLabel = new QLabel(tab_2);
        mechanicalModeLabel->setObjectName("mechanicalModeLabel");
        sizePolicy2.setHeightForWidth(mechanicalModeLabel->sizePolicy().hasHeightForWidth());
        mechanicalModeLabel->setSizePolicy(sizePolicy2);
        mechanicalModeLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        mechanicalModeLabel->setMargin(0);

        verticalLayout_20->addWidget(mechanicalModeLabel);

        mechanicalModeInput = new QComboBox(tab_2);
        mechanicalModeInput->addItem(QString());
        mechanicalModeInput->addItem(QString());
        mechanicalModeInput->setObjectName("mechanicalModeInput");
        mechanicalModeInput->setEnabled(false);
        mechanicalModeInput->setMinimumSize(QSize(200, 0));
        mechanicalModeInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_20->addWidget(mechanicalModeInput);


        horizontalLayout_9->addLayout(verticalLayout_20);


        verticalLayout_21->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName("verticalLayout_15");
        verticalLayout_15->setContentsMargins(-1, -1, 0, 0);
        binningModeLabel = new QLabel(tab_2);
        binningModeLabel->setObjectName("binningModeLabel");
        sizePolicy2.setHeightForWidth(binningModeLabel->sizePolicy().hasHeightForWidth());
        binningModeLabel->setSizePolicy(sizePolicy2);
        binningModeLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        binningModeLabel->setMargin(0);

        verticalLayout_15->addWidget(binningModeLabel);

        binningModeInput = new QComboBox(tab_2);
        binningModeInput->addItem(QString());
        binningModeInput->addItem(QString());
        binningModeInput->setObjectName("binningModeInput");
        binningModeInput->setEnabled(false);
        binningModeInput->setMinimumSize(QSize(200, 0));
        binningModeInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_15->addWidget(binningModeInput);


        horizontalLayout_11->addLayout(verticalLayout_15);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName("verticalLayout_16");
        verticalLayout_16->setContentsMargins(-1, -1, 0, 0);
        gainModeLabel = new QLabel(tab_2);
        gainModeLabel->setObjectName("gainModeLabel");
        sizePolicy2.setHeightForWidth(gainModeLabel->sizePolicy().hasHeightForWidth());
        gainModeLabel->setSizePolicy(sizePolicy2);
        gainModeLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        gainModeLabel->setMargin(0);

        verticalLayout_16->addWidget(gainModeLabel);

        gainModeInput = new QComboBox(tab_2);
        gainModeInput->addItem(QString());
        gainModeInput->addItem(QString());
        gainModeInput->setObjectName("gainModeInput");
        gainModeInput->setEnabled(false);
        gainModeInput->setMinimumSize(QSize(200, 0));
        gainModeInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_16->addWidget(gainModeInput);


        horizontalLayout_11->addLayout(verticalLayout_16);


        verticalLayout_21->addLayout(horizontalLayout_11);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName("verticalLayout_17");
        verticalLayout_17->setContentsMargins(0, -1, -1, 0);
        integrationTimeLabel = new QLabel(tab_2);
        integrationTimeLabel->setObjectName("integrationTimeLabel");

        verticalLayout_17->addWidget(integrationTimeLabel);

        integrationTimeInput = new QLineEdit(tab_2);
        integrationTimeInput->setObjectName("integrationTimeInput");
        integrationTimeInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(integrationTimeInput->sizePolicy().hasHeightForWidth());
        integrationTimeInput->setSizePolicy(sizePolicy2);
        integrationTimeInput->setMinimumSize(QSize(200, 0));
        integrationTimeInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_17->addWidget(integrationTimeInput);


        horizontalLayout_15->addLayout(verticalLayout_17);

        horizontalSpacer_14 = new QSpacerItem(18, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName("verticalLayout_18");
        verticalLayout_18->setContentsMargins(0, -1, -1, 0);
        intervalTimeLabel = new QLabel(tab_2);
        intervalTimeLabel->setObjectName("intervalTimeLabel");

        verticalLayout_18->addWidget(intervalTimeLabel);

        intervalTimeInput = new QLineEdit(tab_2);
        intervalTimeInput->setObjectName("intervalTimeInput");
        intervalTimeInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(intervalTimeInput->sizePolicy().hasHeightForWidth());
        intervalTimeInput->setSizePolicy(sizePolicy2);
        intervalTimeInput->setMinimumSize(QSize(200, 0));
        intervalTimeInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_18->addWidget(intervalTimeInput);


        horizontalLayout_15->addLayout(verticalLayout_18);


        verticalLayout_21->addLayout(horizontalLayout_15);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName("verticalLayout_14");
        verticalLayout_14->setContentsMargins(-1, -1, 0, 0);
        imageQuantityLabel = new QLabel(tab_2);
        imageQuantityLabel->setObjectName("imageQuantityLabel");
        sizePolicy2.setHeightForWidth(imageQuantityLabel->sizePolicy().hasHeightForWidth());
        imageQuantityLabel->setSizePolicy(sizePolicy2);
        imageQuantityLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        imageQuantityLabel->setMargin(0);

        verticalLayout_14->addWidget(imageQuantityLabel);

        imageQuantityStackedWidget = new QStackedWidget(tab_2);
        imageQuantityStackedWidget->setObjectName("imageQuantityStackedWidget");
        imageQuantityStackedWidget->setEnabled(false);
        imageQuantityStackedWidget->setMinimumSize(QSize(200, 0));
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        imageQuantityComboBox = new QComboBox(page_1);
        imageQuantityComboBox->setObjectName("imageQuantityComboBox");
        imageQuantityComboBox->setEnabled(false);
        imageQuantityComboBox->setGeometry(QRect(0, 0, 200, 22));
        imageQuantityComboBox->setMinimumSize(QSize(200, 0));
        imageQuantityComboBox->setMaximumSize(QSize(200, 16777215));
        imageQuantityStackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        imageQuantityInput = new QLineEdit(page_2);
        imageQuantityInput->setObjectName("imageQuantityInput");
        imageQuantityInput->setEnabled(false);
        imageQuantityInput->setGeometry(QRect(0, 0, 200, 22));
        sizePolicy2.setHeightForWidth(imageQuantityInput->sizePolicy().hasHeightForWidth());
        imageQuantityInput->setSizePolicy(sizePolicy2);
        imageQuantityInput->setMinimumSize(QSize(200, 0));
        imageQuantityInput->setMaximumSize(QSize(200, 16777215));
        imageQuantityStackedWidget->addWidget(page_2);

        verticalLayout_14->addWidget(imageQuantityStackedWidget);


        horizontalLayout_10->addLayout(verticalLayout_14);

        horizontalSpacer_10 = new QSpacerItem(18, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalLayout_13->setContentsMargins(-1, -1, 0, 0);
        totalTimeLabel = new QLabel(tab_2);
        totalTimeLabel->setObjectName("totalTimeLabel");
        sizePolicy2.setHeightForWidth(totalTimeLabel->sizePolicy().hasHeightForWidth());
        totalTimeLabel->setSizePolicy(sizePolicy2);
        totalTimeLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        totalTimeLabel->setMargin(0);

        verticalLayout_13->addWidget(totalTimeLabel);

        totalTimeInput = new QLineEdit(tab_2);
        totalTimeInput->setObjectName("totalTimeInput");
        totalTimeInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(totalTimeInput->sizePolicy().hasHeightForWidth());
        totalTimeInput->setSizePolicy(sizePolicy2);
        totalTimeInput->setMinimumSize(QSize(200, 0));
        totalTimeInput->setMaximumSize(QSize(200, 16777215));
        totalTimeInput->setReadOnly(true);

        verticalLayout_13->addWidget(totalTimeInput);


        horizontalLayout_10->addLayout(verticalLayout_13);


        verticalLayout_21->addLayout(horizontalLayout_10);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName("horizontalLayout_33");
        horizontalLayout_33->setContentsMargins(-1, -1, -1, 10);
        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName("verticalLayout_19");
        verticalLayout_19->setContentsMargins(0, -1, -1, 0);
        filePrefixLabel = new QLabel(tab_2);
        filePrefixLabel->setObjectName("filePrefixLabel");

        verticalLayout_19->addWidget(filePrefixLabel);

        filePrefixInput = new QLineEdit(tab_2);
        filePrefixInput->setObjectName("filePrefixInput");
        filePrefixInput->setEnabled(false);
        sizePolicy2.setHeightForWidth(filePrefixInput->sizePolicy().hasHeightForWidth());
        filePrefixInput->setSizePolicy(sizePolicy2);
        filePrefixInput->setMinimumSize(QSize(200, 0));
        filePrefixInput->setMaximumSize(QSize(200, 16777215));

        verticalLayout_19->addWidget(filePrefixInput);


        horizontalLayout_33->addLayout(verticalLayout_19);

        horizontalSpacer_15 = new QSpacerItem(18, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_15);


        verticalLayout_21->addLayout(horizontalLayout_33);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName("verticalLayout_11");
        verticalLayout_11->setContentsMargins(-1, -1, -1, 10);
        filePathNameLabel = new QLabel(tab_2);
        filePathNameLabel->setObjectName("filePathNameLabel");

        verticalLayout_11->addWidget(filePathNameLabel);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        filePathInput = new QLineEdit(tab_2);
        filePathInput->setObjectName("filePathInput");
        filePathInput->setEnabled(false);
        sizePolicy1.setHeightForWidth(filePathInput->sizePolicy().hasHeightForWidth());
        filePathInput->setSizePolicy(sizePolicy1);
        filePathInput->setMinimumSize(QSize(400, 0));
        filePathInput->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_17->addWidget(filePathInput);

        horizontalSpacer_16 = new QSpacerItem(13, 17, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_16);

        chooseFilePathBtn = new QPushButton(tab_2);
        chooseFilePathBtn->setObjectName("chooseFilePathBtn");
        chooseFilePathBtn->setEnabled(false);

        horizontalLayout_17->addWidget(chooseFilePathBtn);


        verticalLayout_11->addLayout(horizontalLayout_17);


        verticalLayout_21->addLayout(verticalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(-1, -1, -1, 25);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        grabBtn = new QPushButton(tab_2);
        grabBtn->setObjectName("grabBtn");
        grabBtn->setEnabled(false);

        horizontalLayout_12->addWidget(grabBtn);

        stopGrabBtn = new QPushButton(tab_2);
        stopGrabBtn->setObjectName("stopGrabBtn");
        stopGrabBtn->setEnabled(false);

        horizontalLayout_12->addWidget(stopGrabBtn);


        horizontalLayout_13->addLayout(horizontalLayout_12);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);


        verticalLayout_21->addLayout(horizontalLayout_13);

        verticalSpacer_2 = new QSpacerItem(20, 127, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_21->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        verticalLayout_29 = new QVBoxLayout(tab_4);
        verticalLayout_29->setSpacing(6);
        verticalLayout_29->setContentsMargins(11, 11, 11, 11);
        verticalLayout_29->setObjectName("verticalLayout_29");
        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setObjectName("verticalLayout_24");
        verticalLayout_24->setContentsMargins(-1, 25, -1, 30);
        label = new QLabel(tab_4);
        label->setObjectName("label");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setBold(true);
        label->setFont(font1);

        verticalLayout_24->addWidget(label);

        label_2 = new QLabel(tab_4);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        label_2->setWordWrap(true);

        verticalLayout_24->addWidget(label_2);


        verticalLayout_29->addLayout(verticalLayout_24);

        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setSpacing(6);
        verticalLayout_25->setObjectName("verticalLayout_25");
        verticalLayout_25->setContentsMargins(-1, -1, -1, 30);
        label_3 = new QLabel(tab_4);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        verticalLayout_25->addWidget(label_3);

        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setObjectName("verticalLayout_22");
        label_5 = new QLabel(tab_4);
        label_5->setObjectName("label_5");

        verticalLayout_22->addWidget(label_5);

        label_4 = new QLabel(tab_4);
        label_4->setObjectName("label_4");

        verticalLayout_22->addWidget(label_4);


        verticalLayout_25->addLayout(verticalLayout_22);


        verticalLayout_29->addLayout(verticalLayout_25);

        verticalLayout_27 = new QVBoxLayout();
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setObjectName("verticalLayout_27");
        verticalLayout_27->setContentsMargins(-1, -1, -1, 30);
        label_8 = new QLabel(tab_4);
        label_8->setObjectName("label_8");
        label_8->setFont(font1);

        verticalLayout_27->addWidget(label_8);

        verticalLayout_28 = new QVBoxLayout();
        verticalLayout_28->setSpacing(6);
        verticalLayout_28->setObjectName("verticalLayout_28");
        label_9 = new QLabel(tab_4);
        label_9->setObjectName("label_9");

        verticalLayout_28->addWidget(label_9);

        label_10 = new QLabel(tab_4);
        label_10->setObjectName("label_10");

        verticalLayout_28->addWidget(label_10);


        verticalLayout_27->addLayout(verticalLayout_28);


        verticalLayout_29->addLayout(verticalLayout_27);

        verticalSpacer_3 = new QSpacerItem(20, 259, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_29->addItem(verticalSpacer_3);

        tabWidget->addTab(tab_4, QString());

        horizontalLayout_34->addWidget(tabWidget);

        line = new QFrame(centralWidget);
        line->setObjectName("line");
        line->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"}\n"
"\n"
"QFrame[frameShape=\"5\"] { /* VLine */\n"
"    border-left: 1px solid palette(shadow);\n"
"    border-right: 1px solid palette(light);\n"
"}"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_34->addWidget(line);

        widget = new QWidget(centralWidget);
        widget->setObjectName("widget");
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(250, 250, 250, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(0, 0, 0, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        widget->setPalette(palette);
        verticalLayout_58 = new QVBoxLayout(widget);
        verticalLayout_58->setSpacing(6);
        verticalLayout_58->setContentsMargins(11, 11, 11, 11);
        verticalLayout_58->setObjectName("verticalLayout_58");
        verticalLayout_58->setContentsMargins(0, -1, -1, -1);
        verticalSpacer_7 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_58->addItem(verticalSpacer_7);

        frame = new QFrame(widget);
        frame->setObjectName("frame");
        frame->setEnabled(true);
        frame->setMinimumSize(QSize(450, 0));
        frame->setStyleSheet(QString::fromUtf8("* {\n"
"	font-family: \"Arial\";\n"
"    font-size: 12px;\n"
"	background-color: #FAFAFA;\n"
"	color: #000;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #D3D3D3; /* Cor de fundo das abas */\n"
"    color: #000;\n"
"    padding: 8px 12px;\n"
"    border: 1px solid #B1B1B1;\n"
"    border-bottom: none; /*Remove a borda inferior das abas */\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #FAFAFA; /* Fundo da aba selecionada */\n"
"	color: #000;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #B1B1B1; /* Borda ao redor do conte\303\272do */\n"
"    top: -1px; /* Sobe o conte\303\272do para \"colar\" na aba */\n"
"}\n"
"\n"
"QLineEdit {\n"
"	border: 1px solid #B1B1B1;\n"
"	border-radius: 20px;\n"
"	color: #0000;\n"
"	background-color: #FAFAFA;\n"
"	padding: 2px 4px 2px 4px;\n"
"}\n"
"\n"
"QLineEdit:disabled {\n"
"    background-color: #D3D3D3; /* Fundo cinza */\n"
"    color: #A9A9A9; /* Texto desbotado */\n"
"}\n"
"\n"
"QComboBox {\n"
"	border: 1px solid #B1B1B1;\n"
"	border"
                        "-radius: 20px;\n"
"	color: #000;\n"
"	backgroundColor: #FAFAFA;\n"
"	padding: 2px 4px 2px 4px;\n"
"}\n"
"\n"
"QComboBox:disabled {\n"
"    background-color: #D3D3D3; /* Fundo cinza */\n"
"    color: #A9A9A9; /* Texto desbotado */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    width: 20px;\n"
"	border: none;\n"
"	background-color: #FAFAFA;\n"
"}\n"
"\n"
"QComboBox::drop-down:disabled {\n"
"	background-color: #D3D3D3; /* Fundo cinza */\n"
"    color: #A9A9A9; /* Texto desbotado */\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: url(:/Assets/assets/select_arrow.png);\n"
"	width: 10px;\n"
"}\n"
"\n"
"QPushButton {\n"
"	padding: 3px 9px;\n"
"	border-radius: 3px;\n"
"	background-color: #888585;\n"
"	color: #FFF;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #7A7A7A;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #D3D3D3; /* Fundo cinza */\n"
"    color: #A9A9A9; /* Texto desbotado */\n"
"    border: 1px solid #CCCCCC;\n"
"    opacity: 0.6; /* Diminui a opacidade */\n"
"}\n"
""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_23 = new QVBoxLayout(frame);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName("verticalLayout_23");
        imageLabel = new QLabel(frame);
        imageLabel->setObjectName("imageLabel");
        sizePolicy.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy);
        imageLabel->setMinimumSize(QSize(140, 120));
        imageLabel->setScaledContents(false);
        imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_23->addWidget(imageLabel);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalLayout_16->setContentsMargins(-1, 25, -1, 10);
        verticalLayout_30 = new QVBoxLayout();
        verticalLayout_30->setSpacing(6);
        verticalLayout_30->setObjectName("verticalLayout_30");
        currentDisplayedImageLabel = new QLabel(frame);
        currentDisplayedImageLabel->setObjectName("currentDisplayedImageLabel");

        verticalLayout_30->addWidget(currentDisplayedImageLabel);

        currentProcessingImageLabel = new QLabel(frame);
        currentProcessingImageLabel->setObjectName("currentProcessingImageLabel");

        verticalLayout_30->addWidget(currentProcessingImageLabel);

        currentProgressLabel = new QLabel(frame);
        currentProgressLabel->setObjectName("currentProgressLabel");

        verticalLayout_30->addWidget(currentProgressLabel);


        horizontalLayout_16->addLayout(verticalLayout_30);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_17);

        verticalLayout_31 = new QVBoxLayout();
        verticalLayout_31->setSpacing(6);
        verticalLayout_31->setObjectName("verticalLayout_31");
        elapsedTimeLabel = new QLabel(frame);
        elapsedTimeLabel->setObjectName("elapsedTimeLabel");

        verticalLayout_31->addWidget(elapsedTimeLabel);

        remainingTimeLabel = new QLabel(frame);
        remainingTimeLabel->setObjectName("remainingTimeLabel");

        verticalLayout_31->addWidget(remainingTimeLabel);

        currentStatusLabel = new QLabel(frame);
        currentStatusLabel->setObjectName("currentStatusLabel");

        verticalLayout_31->addWidget(currentStatusLabel);


        horizontalLayout_16->addLayout(verticalLayout_31);


        verticalLayout_23->addLayout(horizontalLayout_16);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName("progressBar");
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    border: 2px solid #444;\n"
"    border-radius: 5px;\n"
"    text-align: center; /* centraliza o texto */\n"
"    color: white;\n"
"    background-color: #222;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #00c853; /* verde */\n"
"    border-radius: 3px;\n"
"}"));
        progressBar->setValue(24);

        verticalLayout_23->addWidget(progressBar);


        verticalLayout_58->addWidget(frame);


        horizontalLayout_34->addWidget(widget);

        QtGuiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtGuiClass);
        statusBar->setObjectName("statusBar");
        QtGuiClass->setStatusBar(statusBar);

        retranslateUi(QtGuiClass);

        tabWidget->setCurrentIndex(1);
        imageQuantityStackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QtGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiClass)
    {
        QtGuiClass->setWindowTitle(QCoreApplication::translate("QtGuiClass", "QtGui", nullptr));
        hostIpLabel->setText(QCoreApplication::translate("QtGuiClass", "Endere\303\247o de IP do Host", nullptr));
        hostIpInput->setPlaceholderText(QCoreApplication::translate("QtGuiClass", "192.168.1.100", nullptr));
        hostIpConnectBtn->setText(QCoreApplication::translate("QtGuiClass", "Conectar", nullptr));
        deviceSelectLabel->setText(QCoreApplication::translate("QtGuiClass", "Selecionar dispositivo", nullptr));
        deviceSelect->setPlaceholderText(QString());
        deviceIpLabel->setText(QCoreApplication::translate("QtGuiClass", "Endere\303\247o de IP do dispositivo", nullptr));
        deviceTypeLabel->setText(QCoreApplication::translate("QtGuiClass", "Tipo de dispositivo", nullptr));
        deviceMacLabel->setText(QCoreApplication::translate("QtGuiClass", "Endere\303\247o MAC", nullptr));
        deviceFirmwareLabel->setText(QCoreApplication::translate("QtGuiClass", "Vers\303\243o do Firmware", nullptr));
        deviceCmdPortLabel->setText(QCoreApplication::translate("QtGuiClass", "Porta de comando", nullptr));
        deviceImgPortLabel->setText(QCoreApplication::translate("QtGuiClass", "Porta de imagem", nullptr));
        deviceSerialLabel->setText(QCoreApplication::translate("QtGuiClass", "N\303\272mero Serial", nullptr));
        deviceInfoUpdateBtn->setText(QCoreApplication::translate("QtGuiClass", "Atualizar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("QtGuiClass", "Conex\303\243o e dispositivos", nullptr));
        acquisitionModeLabel->setText(QCoreApplication::translate("QtGuiClass", "Modo de aquisi\303\247\303\243o", nullptr));
        acquisitionModeInput->setItemText(0, QCoreApplication::translate("QtGuiClass", "Radiografia", nullptr));
        acquisitionModeInput->setItemText(1, QCoreApplication::translate("QtGuiClass", "Tomografia", nullptr));

        acquisitionModeInput->setPlaceholderText(QString());
        mechanicalModeLabel->setText(QCoreApplication::translate("QtGuiClass", "Modo de conex\303\243o mec\303\242nica", nullptr));
        mechanicalModeInput->setItemText(0, QCoreApplication::translate("QtGuiClass", "Arduino", nullptr));
        mechanicalModeInput->setItemText(1, QCoreApplication::translate("QtGuiClass", "Raspberry PI", nullptr));

        mechanicalModeInput->setPlaceholderText(QString());
        binningModeLabel->setText(QCoreApplication::translate("QtGuiClass", "Modo de binning", nullptr));
        binningModeInput->setItemText(0, QCoreApplication::translate("QtGuiClass", "Normal", nullptr));
        binningModeInput->setItemText(1, QCoreApplication::translate("QtGuiClass", "2x2", nullptr));

        binningModeInput->setPlaceholderText(QString());
        gainModeLabel->setText(QCoreApplication::translate("QtGuiClass", "Modo de ganho", nullptr));
        gainModeInput->setItemText(0, QCoreApplication::translate("QtGuiClass", "Baixo", nullptr));
        gainModeInput->setItemText(1, QCoreApplication::translate("QtGuiClass", "Alto", nullptr));

        gainModeInput->setPlaceholderText(QString());
        integrationTimeLabel->setText(QCoreApplication::translate("QtGuiClass", "Tempo de integra\303\247\303\243o (us)", nullptr));
        intervalTimeLabel->setText(QCoreApplication::translate("QtGuiClass", "Tempo de intervalo (ms)", nullptr));
        imageQuantityLabel->setText(QCoreApplication::translate("QtGuiClass", "Quantidade de imagens", nullptr));
        imageQuantityComboBox->setPlaceholderText(QString());
        totalTimeLabel->setText(QCoreApplication::translate("QtGuiClass", "Tempo total esperado", nullptr));
        filePrefixLabel->setText(QCoreApplication::translate("QtGuiClass", "Prefixo dos arquivos", nullptr));
        filePathNameLabel->setText(QCoreApplication::translate("QtGuiClass", "Local de salvamento", nullptr));
        chooseFilePathBtn->setText(QCoreApplication::translate("QtGuiClass", "Procurar", nullptr));
        grabBtn->setText(QCoreApplication::translate("QtGuiClass", "Capturar", nullptr));
        stopGrabBtn->setText(QCoreApplication::translate("QtGuiClass", "Parar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("QtGuiClass", "Opera\303\247\303\243o", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("QtGuiClass", "Ajuda", nullptr));
        label->setText(QCoreApplication::translate("QtGuiClass", "Sobre o projeto:", nullptr));
        label_2->setText(QCoreApplication::translate("QtGuiClass", "Este software foi desenvolvido como parte de um projeto de pesquisa de Inicia\303\247\303\243o Cientifica na Universidade Estadual de Santa Cruz (UESC). O projeto teve como objetivo projetar e desenvolver um software para automatizar as opera\303\247\303\265es do detector de raios-x flat-panel 1412i.", nullptr));
        label_3->setText(QCoreApplication::translate("QtGuiClass", "Equipe:", nullptr));
        label_5->setText(QCoreApplication::translate("QtGuiClass", "\342\200\242 Matheus Santos Silva", nullptr));
        label_4->setText(QCoreApplication::translate("QtGuiClass", "\342\200\242 Dany Sanchez Dominguez", nullptr));
        label_8->setText(QCoreApplication::translate("QtGuiClass", "Contato:", nullptr));
        label_9->setText(QCoreApplication::translate("QtGuiClass", "\342\200\242 mssilva.cic@uesc.br", nullptr));
        label_10->setText(QCoreApplication::translate("QtGuiClass", "\342\200\242 dsdominguez@uesc.br", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("QtGuiClass", "Sobre", nullptr));
        imageLabel->setText(QCoreApplication::translate("QtGuiClass", "QLABEL AQUI", nullptr));
        currentDisplayedImageLabel->setText(QCoreApplication::translate("QtGuiClass", "Exibindo: ---", nullptr));
        currentProcessingImageLabel->setText(QCoreApplication::translate("QtGuiClass", "Processando: ---", nullptr));
        currentProgressLabel->setText(QCoreApplication::translate("QtGuiClass", "Progresso: ---", nullptr));
        elapsedTimeLabel->setText(QCoreApplication::translate("QtGuiClass", "Tempo decorrido: ---", nullptr));
        remainingTimeLabel->setText(QCoreApplication::translate("QtGuiClass", "Tempo restante: ---", nullptr));
        currentStatusLabel->setText(QCoreApplication::translate("QtGuiClass", "Status: ---", nullptr));
        progressBar->setFormat(QCoreApplication::translate("QtGuiClass", "%v/%m (%p%)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiClass: public Ui_QtGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUI_H
