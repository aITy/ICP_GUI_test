/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu 2. May 13:03:01 2013
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_SaveAs;
    QAction *action_Close;
    QAction *action_LocalLabel;
    QAction *action_NetLabel;
    QAction *action_NewNetGame;
    QAction *action_NewLocalGame;
    QAction *action_DisconnectGame;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_Tools;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox;
    QGroupBox *groupBox_3;
    QFrame *frame_Game;
    QTabWidget *tabWidget_Games;
    QFrame *frame_Moves;
    QGroupBox *groupBox_Moves;
    QLineEdit *lineEdit_Moves;
    QMenuBar *menuBar;
    QMenu *menuSoubor;
    QMenu *menuHra;
    QMenu *action_help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1060, 740);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        action_SaveAs = new QAction(MainWindow);
        action_SaveAs->setObjectName(QString::fromUtf8("action_SaveAs"));
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        action_LocalLabel = new QAction(MainWindow);
        action_LocalLabel->setObjectName(QString::fromUtf8("action_LocalLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        action_LocalLabel->setFont(font);
        action_NetLabel = new QAction(MainWindow);
        action_NetLabel->setObjectName(QString::fromUtf8("action_NetLabel"));
        action_NetLabel->setFont(font);
        action_NewNetGame = new QAction(MainWindow);
        action_NewNetGame->setObjectName(QString::fromUtf8("action_NewNetGame"));
        action_NewLocalGame = new QAction(MainWindow);
        action_NewLocalGame->setObjectName(QString::fromUtf8("action_NewLocalGame"));
        action_DisconnectGame = new QAction(MainWindow);
        action_DisconnectGame->setObjectName(QString::fromUtf8("action_DisconnectGame"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMaximumSize(QSize(16777215, 750));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(19, 19, 1011, 661));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame_Tools = new QFrame(horizontalLayoutWidget);
        frame_Tools->setObjectName(QString::fromUtf8("frame_Tools"));
        frame_Tools->setMaximumSize(QSize(150, 650));
        frame_Tools->setFrameShape(QFrame::StyledPanel);
        frame_Tools->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(frame_Tools);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 151, 631));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 215));

        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 215));

        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(verticalLayoutWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 215));

        verticalLayout->addWidget(groupBox_3);


        horizontalLayout->addWidget(frame_Tools);

        frame_Game = new QFrame(horizontalLayoutWidget);
        frame_Game->setObjectName(QString::fromUtf8("frame_Game"));
        frame_Game->setMaximumSize(QSize(650, 650));
        frame_Game->setFrameShape(QFrame::StyledPanel);
        frame_Game->setFrameShadow(QFrame::Raised);
        tabWidget_Games = new QTabWidget(frame_Game);
        tabWidget_Games->setObjectName(QString::fromUtf8("tabWidget_Games"));
        tabWidget_Games->setGeometry(QRect(0, 0, 651, 650));
        tabWidget_Games->setMinimumSize(QSize(650, 650));
        tabWidget_Games->setMaximumSize(QSize(651, 630));

        horizontalLayout->addWidget(frame_Game);

        frame_Moves = new QFrame(horizontalLayoutWidget);
        frame_Moves->setObjectName(QString::fromUtf8("frame_Moves"));
        frame_Moves->setMaximumSize(QSize(210, 16777215));
        frame_Moves->setFrameShape(QFrame::StyledPanel);
        frame_Moves->setFrameShadow(QFrame::Raised);
        groupBox_Moves = new QGroupBox(frame_Moves);
        groupBox_Moves->setObjectName(QString::fromUtf8("groupBox_Moves"));
        groupBox_Moves->setGeometry(QRect(0, 0, 211, 650));
        groupBox_Moves->setMinimumSize(QSize(0, 650));
        groupBox_Moves->setMaximumSize(QSize(16777215, 650));
        lineEdit_Moves = new QLineEdit(groupBox_Moves);
        lineEdit_Moves->setObjectName(QString::fromUtf8("lineEdit_Moves"));
        lineEdit_Moves->setEnabled(false);
        lineEdit_Moves->setGeometry(QRect(10, 20, 191, 631));

        horizontalLayout->addWidget(frame_Moves);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1060, 22));
        menuSoubor = new QMenu(menuBar);
        menuSoubor->setObjectName(QString::fromUtf8("menuSoubor"));
        menuHra = new QMenu(menuBar);
        menuHra->setObjectName(QString::fromUtf8("menuHra"));
        action_help = new QMenu(menuBar);
        action_help->setObjectName(QString::fromUtf8("action_help"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSoubor->menuAction());
        menuBar->addAction(menuHra->menuAction());
        menuBar->addAction(action_help->menuAction());
        menuSoubor->addAction(action_Open);
        menuSoubor->addAction(action_Save);
        menuSoubor->addAction(action_SaveAs);
        menuSoubor->addAction(action_Close);
        menuHra->addAction(action_LocalLabel);
        menuHra->addAction(action_NewLocalGame);
        menuHra->addSeparator();
        menuHra->addAction(action_NetLabel);
        menuHra->addAction(action_NewNetGame);
        menuHra->addAction(action_DisconnectGame);
        menuHra->addSeparator();

        retranslateUi(MainWindow);

        tabWidget_Games->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "Otev\305\231\303\255t", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", "Ulo\305\276it", 0, QApplication::UnicodeUTF8));
        action_SaveAs->setText(QApplication::translate("MainWindow", "Ulo\305\276it jako", 0, QApplication::UnicodeUTF8));
        action_Close->setText(QApplication::translate("MainWindow", "Zav\305\231it", 0, QApplication::UnicodeUTF8));
        action_LocalLabel->setText(QApplication::translate("MainWindow", "Lok\303\241ln\303\255", 0, QApplication::UnicodeUTF8));
        action_NetLabel->setText(QApplication::translate("MainWindow", "S\303\255\305\245ov\303\241", 0, QApplication::UnicodeUTF8));
        action_NewNetGame->setText(QApplication::translate("MainWindow", "Nov\303\241 hra proti CPU", 0, QApplication::UnicodeUTF8));
        action_NewLocalGame->setText(QApplication::translate("MainWindow", "Nov\303\241 hra proti hr\303\241\304\215i", 0, QApplication::UnicodeUTF8));
        action_DisconnectGame->setText(QApplication::translate("MainWindow", "Odpojit aktu\303\241ln\303\255 hru", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Game tools", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Replay tools", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "others ... ?", 0, QApplication::UnicodeUTF8));
        groupBox_Moves->setTitle(QApplication::translate("MainWindow", "Moves", 0, QApplication::UnicodeUTF8));
        menuSoubor->setTitle(QApplication::translate("MainWindow", "Soubor", 0, QApplication::UnicodeUTF8));
        menuHra->setTitle(QApplication::translate("MainWindow", "Hra", 0, QApplication::UnicodeUTF8));
        action_help->setTitle(QApplication::translate("MainWindow", "N\303\241pov\304\233da", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
