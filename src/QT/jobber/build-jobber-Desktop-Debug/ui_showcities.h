/********************************************************************************
** Form generated from reading UI file 'showcities.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWCITIES_H
#define UI_SHOWCITIES_H

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

class Ui_ShowCities
{
public:
    QWidget *centralwidget;
    QLabel *labelInfo;
    QLabel *labelCityID;
    QComboBox *comboBoxCityID;
    QLabel *labelCity;
    QLineEdit *lineEditCityName;
    QLabel *labelCountryID;
    QComboBox *comboBoxCountryID;
    QLabel *labelCountryName;
    QPushButton *btnPrev;
    QPushButton *btnFirst;
    QPushButton *btnLast;
    QPushButton *btnNext;

    void setupUi(QMainWindow *ShowCities)
    {
        if (ShowCities->objectName().isEmpty())
            ShowCities->setObjectName(QStringLiteral("ShowCities"));
        ShowCities->resize(321, 206);
        centralwidget = new QWidget(ShowCities);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setGeometry(QRect(10, 10, 291, 51));
        labelInfo->setWordWrap(true);
        labelCityID = new QLabel(centralwidget);
        labelCityID->setObjectName(QStringLiteral("labelCityID"));
        labelCityID->setGeometry(QRect(40, 70, 59, 15));
        comboBoxCityID = new QComboBox(centralwidget);
        comboBoxCityID->setObjectName(QStringLiteral("comboBoxCityID"));
        comboBoxCityID->setGeometry(QRect(120, 70, 79, 23));
        labelCity = new QLabel(centralwidget);
        labelCity->setObjectName(QStringLiteral("labelCity"));
        labelCity->setGeometry(QRect(40, 100, 71, 16));
        lineEditCityName = new QLineEdit(centralwidget);
        lineEditCityName->setObjectName(QStringLiteral("lineEditCityName"));
        lineEditCityName->setGeometry(QRect(120, 100, 113, 23));
        labelCountryID = new QLabel(centralwidget);
        labelCountryID->setObjectName(QStringLiteral("labelCountryID"));
        labelCountryID->setGeometry(QRect(40, 130, 59, 15));
        comboBoxCountryID = new QComboBox(centralwidget);
        comboBoxCountryID->setObjectName(QStringLiteral("comboBoxCountryID"));
        comboBoxCountryID->setGeometry(QRect(120, 130, 79, 23));
        labelCountryName = new QLabel(centralwidget);
        labelCountryName->setObjectName(QStringLiteral("labelCountryName"));
        labelCountryName->setGeometry(QRect(210, 130, 121, 16));
        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);
        btnPrev->setGeometry(QRect(90, 170, 31, 23));
        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);
        btnFirst->setGeometry(QRect(40, 170, 31, 23));
        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));
        btnLast->setGeometry(QRect(190, 170, 31, 23));
        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setGeometry(QRect(140, 170, 31, 23));
        ShowCities->setCentralWidget(centralwidget);

        retranslateUi(ShowCities);

        QMetaObject::connectSlotsByName(ShowCities);
    } // setupUi

    void retranslateUi(QMainWindow *ShowCities)
    {
        ShowCities->setWindowTitle(QApplication::translate("ShowCities", "Vis innlagte byer og steder", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("ShowCities", "Her kan du se stedene som er lagt inn i databasen. Vil du bytte ID-en til et sted, m\303\245 dette gj\303\270res via kommandolinja.", Q_NULLPTR));
        labelCityID->setText(QApplication::translate("ShowCities", "StedID", Q_NULLPTR));
        labelCity->setText(QApplication::translate("ShowCities", "Stedsnavn", Q_NULLPTR));
        labelCountryID->setText(QApplication::translate("ShowCities", "LandID", Q_NULLPTR));
        labelCountryName->setText(QApplication::translate("ShowCities", "$countryName", Q_NULLPTR));
        btnPrev->setText(QApplication::translate("ShowCities", "<", Q_NULLPTR));
        btnFirst->setText(QApplication::translate("ShowCities", "<<", Q_NULLPTR));
        btnLast->setText(QApplication::translate("ShowCities", ">>", Q_NULLPTR));
        btnNext->setText(QApplication::translate("ShowCities", ">", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowCities: public Ui_ShowCities {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCITIES_H
