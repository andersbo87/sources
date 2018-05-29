/********************************************************************************
** Form generated from reading UI file 'newcountry.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
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
#include <QtWidgets/QFormLayout>
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
    QFormLayout *formLayout;
    QLabel *labelInfo;
    QLabel *labelCountryName;
    QLineEdit *lineEditCountryName;
    QDialogButtonBox *buttonBox;

    void setupUi(QMainWindow *NewCountry)
    {
        if (NewCountry->objectName().isEmpty())
            NewCountry->setObjectName(QStringLiteral("NewCountry"));
        NewCountry->resize(335, 96);
        NewCountry->setMinimumSize(QSize(335, 96));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        NewCountry->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewCountry->setWindowIcon(icon);
        centralwidget = new QWidget(NewCountry);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, labelInfo);

        labelCountryName = new QLabel(centralwidget);
        labelCountryName->setObjectName(QStringLiteral("labelCountryName"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelCountryName);

        lineEditCountryName = new QLineEdit(centralwidget);
        lineEditCountryName->setObjectName(QStringLiteral("lineEditCountryName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditCountryName);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(2, QFormLayout::SpanningRole, buttonBox);

        NewCountry->setCentralWidget(centralwidget);

        retranslateUi(NewCountry);

        QMetaObject::connectSlotsByName(NewCountry);
    } // setupUi

    void retranslateUi(QMainWindow *NewCountry)
    {
        NewCountry->setWindowTitle(QApplication::translate("NewCountry", "MainWindow", nullptr));
        labelInfo->setText(QApplication::translate("NewCountry", "Her kan du legge inn et nytt land i databasen.", nullptr));
        labelCountryName->setText(QApplication::translate("NewCountry", "Landnavn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewCountry: public Ui_NewCountry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCOUNTRY_H
