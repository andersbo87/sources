/********************************************************************************
** Form generated from reading UI file 'showcountries.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWCOUNTRIES_H
#define UI_SHOWCOUNTRIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowCountries
{
public:
    QWidget *centralwidget;
    QLabel *labelCountryName;
    QPushButton *btnFirst;
    QLabel *labelLandID;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QPushButton *btnPrev;
    QLineEdit *lineEditCountryName;
    QComboBox *comboBoxLandID;
    QLabel *labelInfo;

    void setupUi(QMainWindow *ShowCountries)
    {
        if (ShowCountries->objectName().isEmpty())
            ShowCountries->setObjectName(QStringLiteral("ShowCountries"));
        ShowCountries->resize(328, 197);
        centralwidget = new QWidget(ShowCountries);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelCountryName = new QLabel(centralwidget);
        labelCountryName->setObjectName(QStringLiteral("labelCountryName"));
        labelCountryName->setGeometry(QRect(30, 120, 59, 15));
        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);
        btnFirst->setGeometry(QRect(30, 150, 31, 23));
        labelLandID = new QLabel(centralwidget);
        labelLandID->setObjectName(QStringLiteral("labelLandID"));
        labelLandID->setGeometry(QRect(30, 90, 59, 15));
        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setGeometry(QRect(130, 150, 31, 23));
        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));
        btnLast->setGeometry(QRect(180, 150, 31, 23));
        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);
        btnPrev->setGeometry(QRect(80, 150, 31, 23));
        lineEditCountryName = new QLineEdit(centralwidget);
        lineEditCountryName->setObjectName(QStringLiteral("lineEditCountryName"));
        lineEditCountryName->setGeometry(QRect(100, 120, 113, 23));
        comboBoxLandID = new QComboBox(centralwidget);
        comboBoxLandID->setObjectName(QStringLiteral("comboBoxLandID"));
        comboBoxLandID->setGeometry(QRect(100, 90, 79, 23));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setGeometry(QRect(30, 20, 281, 51));
        labelInfo->setWordWrap(true);
        ShowCountries->setCentralWidget(centralwidget);

        retranslateUi(ShowCountries);

        QMetaObject::connectSlotsByName(ShowCountries);
    } // setupUi

    void retranslateUi(QMainWindow *ShowCountries)
    {
        ShowCountries->setWindowTitle(QApplication::translate("ShowCountries", "MainWindow", Q_NULLPTR));
        labelCountryName->setText(QApplication::translate("ShowCountries", "Landnavn", Q_NULLPTR));
        btnFirst->setText(QApplication::translate("ShowCountries", "<<", Q_NULLPTR));
        labelLandID->setText(QApplication::translate("ShowCountries", "LandID", Q_NULLPTR));
        btnNext->setText(QApplication::translate("ShowCountries", ">", Q_NULLPTR));
        btnLast->setText(QApplication::translate("ShowCountries", ">>", Q_NULLPTR));
        btnPrev->setText(QApplication::translate("ShowCountries", "<", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("ShowCountries", "Her kan du se de ulike statusene som er registrert i systemet. Vil du endre p\303\245 ID-en til en status, m\303\245 det gj\303\270res i kommandolinja.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowCountries: public Ui_ShowCountries {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCOUNTRIES_H
