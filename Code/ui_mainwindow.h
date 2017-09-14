/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue May 17 16:21:56 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <phonon/seekslider.h>
#include <phonon/volumeslider.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QRadioButton *Pulse;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *Play;
    QPushButton *Stop;
    QLineEdit *path;
    QPushButton *setaudiosource;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *setryhtmvariable;
    QPushButton *pushButton_3;
    QSpinBox *meanvariable;
    QSpinBox *variancevariable;
    QWidget *tab_2;
    QPushButton *pushButton;
    QLabel *label_7;
    QProgressBar *progressBar;
    QLineEdit *BPMlineedit;
    QWidget *tab_3;
    QPushButton *Metrostate;
    QSpinBox *BPM;
    QSpinBox *Measure;
    QPushButton *ModifyMetronome;
    QLabel *label_2;
    QLabel *label_3;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::SeekSlider *seekSlider;
    QLineEdit *Tag;
    QLineEdit *Bigtemp;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(599, 523);
        MainWindow->setMouseTracking(true);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setAcceptDrops(true);
        MainWindow->setWindowOpacity(1);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Pulse = new QRadioButton(centralWidget);
        Pulse->setObjectName(QString::fromUtf8("Pulse"));
        Pulse->setGeometry(QRect(560, 0, 20, 22));
        QFont font;
        font.setPointSize(72);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        Pulse->setFont(font);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 240, 541, 201));
        tabWidget->setIconSize(QSize(15, 15));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        Play = new QPushButton(tab);
        Play->setObjectName(QString::fromUtf8("Play"));
        Play->setGeometry(QRect(20, 20, 121, 121));
        QFont font1;
        font1.setFamily(QString::fromUtf8("FreeSerif"));
        font1.setPointSize(36);
        font1.setItalic(true);
        Play->setFont(font1);
        Stop = new QPushButton(tab);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(150, 20, 121, 121));
        Stop->setFont(font1);
        path = new QLineEdit(tab);
        path->setObjectName(QString::fromUtf8("path"));
        path->setGeometry(QRect(290, 80, 241, 27));
        setaudiosource = new QPushButton(tab);
        setaudiosource->setObjectName(QString::fromUtf8("setaudiosource"));
        setaudiosource->setGeometry(QRect(290, 110, 241, 27));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(320, 20, 66, 21));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(300, 50, 66, 21));
        setryhtmvariable = new QPushButton(tab);
        setryhtmvariable->setObjectName(QString::fromUtf8("setryhtmvariable"));
        setryhtmvariable->setGeometry(QRect(440, 16, 91, 61));
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(450, -120, 81, 31));
        meanvariable = new QSpinBox(tab);
        meanvariable->setObjectName(QString::fromUtf8("meanvariable"));
        meanvariable->setGeometry(QRect(380, 20, 60, 27));
        meanvariable->setMinimum(1);
        meanvariable->setMaximum(100);
        meanvariable->setValue(8);
        variancevariable = new QSpinBox(tab);
        variancevariable->setObjectName(QString::fromUtf8("variancevariable"));
        variancevariable->setGeometry(QRect(380, 50, 60, 27));
        variancevariable->setMinimum(50);
        variancevariable->setMaximum(500);
        variancevariable->setValue(150);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 20, 121, 121));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(240, 50, 101, 17));
        progressBar = new QProgressBar(tab_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(190, 100, 321, 23));
        progressBar->setMinimum(0);
        progressBar->setValue(0);
        BPMlineedit = new QLineEdit(tab_2);
        BPMlineedit->setObjectName(QString::fromUtf8("BPMlineedit"));
        BPMlineedit->setGeometry(QRect(340, 40, 111, 51));
        BPMlineedit->setReadOnly(true);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        Metrostate = new QPushButton(tab_3);
        Metrostate->setObjectName(QString::fromUtf8("Metrostate"));
        Metrostate->setGeometry(QRect(20, 20, 121, 121));
        BPM = new QSpinBox(tab_3);
        BPM->setObjectName(QString::fromUtf8("BPM"));
        BPM->setGeometry(QRect(440, 50, 71, 27));
        BPM->setMinimum(1);
        BPM->setMaximum(300);
        Measure = new QSpinBox(tab_3);
        Measure->setObjectName(QString::fromUtf8("Measure"));
        Measure->setGeometry(QRect(440, 90, 71, 27));
        Measure->setMinimum(1);
        Measure->setMaximum(13);
        ModifyMetronome = new QPushButton(tab_3);
        ModifyMetronome->setObjectName(QString::fromUtf8("ModifyMetronome"));
        ModifyMetronome->setGeometry(QRect(160, 20, 121, 121));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(330, 50, 101, 31));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(360, 90, 91, 31));
        tabWidget->addTab(tab_3, QString());
        volumeSlider = new Phonon::VolumeSlider(centralWidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setEnabled(true);
        volumeSlider->setGeometry(QRect(560, 240, 20, 201));
        volumeSlider->setLayoutDirection(Qt::LeftToRight);
        volumeSlider->setAutoFillBackground(false);
        volumeSlider->setOrientation(Qt::Vertical);
        volumeSlider->setMuteVisible(true);
        seekSlider = new Phonon::SeekSlider(centralWidget);
        seekSlider->setObjectName(QString::fromUtf8("seekSlider"));
        seekSlider->setGeometry(QRect(20, 216, 561, 20));
        Tag = new QLineEdit(centralWidget);
        Tag->setObjectName(QString::fromUtf8("Tag"));
        Tag->setGeometry(QRect(190, 236, 361, 31));
        Tag->setReadOnly(true);
        Bigtemp = new QLineEdit(centralWidget);
        Bigtemp->setObjectName(QString::fromUtf8("Bigtemp"));
        Bigtemp->setGeometry(QRect(560, 0, 21, 21));
        QPalette palette;
        QBrush brush(QColor(255, 85, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        Bigtemp->setPalette(palette);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial Black"));
        font2.setPointSize(72);
        font2.setBold(false);
        font2.setItalic(true);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        Bigtemp->setFont(font2);
        MainWindow->setCentralWidget(centralWidget);
        Bigtemp->raise();
        Pulse->raise();
        tabWidget->raise();
        volumeSlider->raise();
        seekSlider->raise();
        Tag->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 599, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        Pulse->setText(QString());
        Play->setText(QApplication::translate("MainWindow", " \342\226\272", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("MainWindow", "| |", 0, QApplication::UnicodeUTF8));
        setaudiosource->setText(QApplication::translate("MainWindow", "Set audio source", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Mean :", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Variance :", 0, QApplication::UnicodeUTF8));
        setryhtmvariable->setText(QApplication::translate("MainWindow", "Set live BPM", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Stream", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Find precise BPM", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Precise BPM :", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "BPM", 0, QApplication::UnicodeUTF8));
        Metrostate->setText(QApplication::translate("MainWindow", "Start \n"
"Metronome", 0, QApplication::UnicodeUTF8));
        ModifyMetronome->setText(QApplication::translate("MainWindow", "Modify \n"
"Metronome", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", " Wanted BPM :", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Measure :", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Metro", 0, QApplication::UnicodeUTF8));
        Bigtemp->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
