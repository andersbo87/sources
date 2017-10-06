/********************************************************************************
** Form generated from reading UI file 'newcity.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCITY_H
#define UI_NEWCITY_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewCity
{
public:
    QWidget *centralwidget;
    QLabel *labelCityName;
    QLabel *labelCountryID;
    QLabel *labelCountryName;
    QLineEdit *lineEditCityName;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QMainWindow *NewCity)
    {
        if (NewCity->objectName().isEmpty())
            NewCity->setObjectName(QStringLiteral("NewCity"));
        NewCity->resize(309, 132);
        centralwidget = new QWidget(NewCity);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelCityName = new QLabel(centralwidget);
        labelCityName->setObjectName(QStringLiteral("labelCityName"));
        labelCityName->setGeometry(QRect(20, 30, 91, 16));
        labelCityName->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));
        labelCountryID = new QLabel(centralwidget);
        labelCountryID->setObjectName(QStringLiteral("labelCountryID"));
        labelCountryID->setGeometry(QRect(20, 60, 91, 16));
        labelCountryID->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));
        labelCountryName = new QLabel(centralwidget);
        labelCountryName->setObjectName(QStringLiteral("labelCountryName"));
        labelCountryName->setGeometry(QRect(180, 60, 121, 16));
        labelCountryName->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));
        lineEditCityName = new QLineEdit(centralwidget);
        lineEditCityName->setObjectName(QStringLiteral("lineEditCityName"));
        lineEditCityName->setGeometry(QRect(130, 30, 161, 23));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(130, 60, 41, 23));
        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 90, 166, 23));
        buttonBox->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        NewCity->setCentralWidget(centralwidget);

        retranslateUi(NewCity);

        QMetaObject::connectSlotsByName(NewCity);
    } // setupUi

    void retranslateUi(QMainWindow *NewCity)
    {
        NewCity->setWindowTitle(QApplication::translate("NewCity", "Legg til nytt sted", Q_NULLPTR));
        labelCityName->setText(QApplication::translate("NewCity", "Stedsnavn", Q_NULLPTR));
        labelCountryID->setText(QApplication::translate("NewCity", "Landnummer", Q_NULLPTR));
        labelCountryName->setText(QApplication::translate("NewCity", "$land", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewCity: public Ui_NewCity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCITY_H
