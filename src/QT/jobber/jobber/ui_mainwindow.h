/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btn_newJob;
    QPushButton *btn_ShowJobs;
    QPushButton *btn_NewCity;
    QPushButton *btn_NewStatus;
    QPushButton *btn_ShowCities;
    QPushButton *btn_ShowStatuses;
    QPushButton *btn_NewCountry;
    QPushButton *btn_showCountries;
    QPushButton *btnSpecificJobs;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(238, 211);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btn_newJob = new QPushButton(centralWidget);
        btn_newJob->setObjectName(QStringLiteral("btn_newJob"));
        btn_newJob->setGeometry(QRect(20, 10, 91, 22));
        btn_ShowJobs = new QPushButton(centralWidget);
        btn_ShowJobs->setObjectName(QStringLiteral("btn_ShowJobs"));
        btn_ShowJobs->setGeometry(QRect(131, 10, 91, 23));
        btn_NewCity = new QPushButton(centralWidget);
        btn_NewCity->setObjectName(QStringLiteral("btn_NewCity"));
        btn_NewCity->setGeometry(QRect(20, 70, 91, 23));
        btn_NewStatus = new QPushButton(centralWidget);
        btn_NewStatus->setObjectName(QStringLiteral("btn_NewStatus"));
        btn_NewStatus->setGeometry(QRect(20, 100, 91, 23));
        btn_ShowCities = new QPushButton(centralWidget);
        btn_ShowCities->setObjectName(QStringLiteral("btn_ShowCities"));
        btn_ShowCities->setGeometry(QRect(130, 70, 91, 23));
        btn_ShowStatuses = new QPushButton(centralWidget);
        btn_ShowStatuses->setObjectName(QStringLiteral("btn_ShowStatuses"));
        btn_ShowStatuses->setGeometry(QRect(130, 100, 91, 23));
        btn_NewCountry = new QPushButton(centralWidget);
        btn_NewCountry->setObjectName(QStringLiteral("btn_NewCountry"));
        btn_NewCountry->setGeometry(QRect(20, 40, 91, 23));
        btn_showCountries = new QPushButton(centralWidget);
        btn_showCountries->setObjectName(QStringLiteral("btn_showCountries"));
        btn_showCountries->setGeometry(QRect(130, 40, 91, 23));
        btnSpecificJobs = new QPushButton(centralWidget);
        btnSpecificJobs->setObjectName(QStringLiteral("btnSpecificJobs"));
        btnSpecificJobs->setGeometry(QRect(40, 130, 141, 23));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Jobber", Q_NULLPTR));
        btn_newJob->setText(QApplication::translate("MainWindow", "Ny jobb", Q_NULLPTR));
        btn_ShowJobs->setText(QApplication::translate("MainWindow", "Jobber", Q_NULLPTR));
        btn_NewCity->setText(QApplication::translate("MainWindow", "Nytt sted", Q_NULLPTR));
        btn_NewStatus->setText(QApplication::translate("MainWindow", "Ny status", Q_NULLPTR));
        btn_ShowCities->setText(QApplication::translate("MainWindow", "Steder", Q_NULLPTR));
        btn_ShowStatuses->setText(QApplication::translate("MainWindow", "Statuser", Q_NULLPTR));
        btn_NewCountry->setText(QApplication::translate("MainWindow", "Nytt land", Q_NULLPTR));
        btn_showCountries->setText(QApplication::translate("MainWindow", "Land", Q_NULLPTR));
        btnSpecificJobs->setText(QApplication::translate("MainWindow", "Utvalgte jobber", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
