/********************************************************************************
** Form generated from reading UI file 'newcountry.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCOUNTRY_H
#define UI_NEWCOUNTRY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewCountry
{
public:
    QWidget *centralwidget;
    QLabel *labelInfo;
    QLineEdit *lineEditCountryName;
    QLabel *labelCountryName;
    QDialogButtonBox *buttonBox;

    void setupUi(QMainWindow *NewCountry)
    {
        if (NewCountry->objectName().isEmpty())
            NewCountry->setObjectName(QStringLiteral("NewCountry"));
        NewCountry->resize(335, 136);
        centralwidget = new QWidget(NewCountry);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setGeometry(QRect(40, 30, 291, 16));
        lineEditCountryName = new QLineEdit(centralwidget);
        lineEditCountryName->setObjectName(QStringLiteral("lineEditCountryName"));
        lineEditCountryName->setGeometry(QRect(110, 60, 113, 23));
        labelCountryName = new QLabel(centralwidget);
        labelCountryName->setObjectName(QStringLiteral("labelCountryName"));
        labelCountryName->setGeometry(QRect(40, 60, 59, 15));
        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 90, 166, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        NewCountry->setCentralWidget(centralwidget);

        retranslateUi(NewCountry);

        QMetaObject::connectSlotsByName(NewCountry);
    } // setupUi

    void retranslateUi(QMainWindow *NewCountry)
    {
        NewCountry->setWindowTitle(QApplication::translate("NewCountry", "MainWindow", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("NewCountry", "Her kan du legge inn et nytt land i databasen.", Q_NULLPTR));
        labelCountryName->setText(QApplication::translate("NewCountry", "Landnavn", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewCountry: public Ui_NewCountry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCOUNTRY_H
