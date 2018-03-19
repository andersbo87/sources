/********************************************************************************
** Form generated from reading UI file 'newcity.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
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
#include <QtWidgets/QFormLayout>
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
    QFormLayout *formLayout;
    QLabel *labelCityName;
    QLineEdit *lineEditCityName;
    QLabel *labelCountryID;
    QComboBox *comboBox;
    QLabel *labelCountryName;
    QDialogButtonBox *buttonBox;

    void setupUi(QMainWindow *NewCity)
    {
        if (NewCity->objectName().isEmpty())
            NewCity->setObjectName(QStringLiteral("NewCity"));
        NewCity->resize(271, 132);
        NewCity->setMinimumSize(QSize(271, 132));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        NewCity->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewCity->setWindowIcon(icon);
        centralwidget = new QWidget(NewCity);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelCityName = new QLabel(centralwidget);
        labelCityName->setObjectName(QStringLiteral("labelCityName"));
        labelCityName->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelCityName);

        lineEditCityName = new QLineEdit(centralwidget);
        lineEditCityName->setObjectName(QStringLiteral("lineEditCityName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditCityName);

        labelCountryID = new QLabel(centralwidget);
        labelCountryID->setObjectName(QStringLiteral("labelCountryID"));
        labelCountryID->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelCountryID);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBox);

        labelCountryName = new QLabel(centralwidget);
        labelCountryName->setObjectName(QStringLiteral("labelCountryName"));
        labelCountryName->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));

        formLayout->setWidget(3, QFormLayout::FieldRole, labelCountryName);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::SpanningRole, buttonBox);

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
