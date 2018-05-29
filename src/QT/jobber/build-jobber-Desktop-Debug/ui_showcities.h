/********************************************************************************
** Form generated from reading UI file 'showcities.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QPushButton *btnSave;
    QLabel *labelCityID;
    QComboBox *comboBoxCityID;
    QLabel *labelCity;
    QLabel *labelCountryID;
    QComboBox *comboBoxCountryID;
    QLabel *labelCountryName;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QPushButton *btnDelete;
    QLineEdit *lineEditCityName;
    QLabel *labelInfo;

    void setupUi(QMainWindow *ShowCities)
    {
        if (ShowCities->objectName().isEmpty())
            ShowCities->setObjectName(QStringLiteral("ShowCities"));
        ShowCities->resize(535, 194);
        ShowCities->setMinimumSize(QSize(493, 174));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        ShowCities->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        ShowCities->setWindowIcon(icon);
        centralwidget = new QWidget(ShowCities);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setEnabled(false);

        gridLayout->addWidget(btnSave, 4, 5, 1, 1);

        labelCityID = new QLabel(centralwidget);
        labelCityID->setObjectName(QStringLiteral("labelCityID"));

        gridLayout->addWidget(labelCityID, 1, 0, 1, 2);

        comboBoxCityID = new QComboBox(centralwidget);
        comboBoxCityID->setObjectName(QStringLiteral("comboBoxCityID"));

        gridLayout->addWidget(comboBoxCityID, 1, 2, 1, 2);

        labelCity = new QLabel(centralwidget);
        labelCity->setObjectName(QStringLiteral("labelCity"));

        gridLayout->addWidget(labelCity, 2, 0, 1, 2);

        labelCountryID = new QLabel(centralwidget);
        labelCountryID->setObjectName(QStringLiteral("labelCountryID"));

        gridLayout->addWidget(labelCountryID, 3, 0, 1, 2);

        comboBoxCountryID = new QComboBox(centralwidget);
        comboBoxCountryID->setObjectName(QStringLiteral("comboBoxCountryID"));

        gridLayout->addWidget(comboBoxCountryID, 3, 2, 1, 2);

        labelCountryName = new QLabel(centralwidget);
        labelCountryName->setObjectName(QStringLiteral("labelCountryName"));

        gridLayout->addWidget(labelCountryName, 3, 4, 1, 1);

        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);

        gridLayout->addWidget(btnFirst, 4, 0, 1, 1);

        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);

        gridLayout->addWidget(btnPrev, 4, 1, 1, 1);

        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));

        gridLayout->addWidget(btnNext, 4, 2, 1, 1);

        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));

        gridLayout->addWidget(btnLast, 4, 3, 1, 2);

        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        gridLayout->addWidget(btnDelete, 4, 6, 1, 1);

        lineEditCityName = new QLineEdit(centralwidget);
        lineEditCityName->setObjectName(QStringLiteral("lineEditCityName"));

        gridLayout->addWidget(lineEditCityName, 2, 2, 1, 4);

        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setWordWrap(true);

        gridLayout->addWidget(labelInfo, 0, 0, 1, 7);

        ShowCities->setCentralWidget(centralwidget);

        retranslateUi(ShowCities);

        QMetaObject::connectSlotsByName(ShowCities);
    } // setupUi

    void retranslateUi(QMainWindow *ShowCities)
    {
        ShowCities->setWindowTitle(QApplication::translate("ShowCities", "Vis innlagte byer og steder", nullptr));
        btnSave->setText(QApplication::translate("ShowCities", "Lagre", nullptr));
        labelCityID->setText(QApplication::translate("ShowCities", "StedID*", nullptr));
        labelCity->setText(QApplication::translate("ShowCities", "Stedsnavn*", nullptr));
        labelCountryID->setText(QApplication::translate("ShowCities", "LandID*", nullptr));
        labelCountryName->setText(QApplication::translate("ShowCities", "$countryName", nullptr));
        btnFirst->setText(QApplication::translate("ShowCities", "<<", nullptr));
        btnPrev->setText(QApplication::translate("ShowCities", "<", nullptr));
        btnNext->setText(QApplication::translate("ShowCities", ">", nullptr));
        btnLast->setText(QApplication::translate("ShowCities", ">>", nullptr));
        btnDelete->setText(QApplication::translate("ShowCities", "Slett", nullptr));
        labelInfo->setText(QApplication::translate("ShowCities", "Her kan du se stedene som er lagt inn i databasen. Vil du bytte ID-en til et sted, m\303\245 dette gj\303\270res via kommandolinja. Alle felt m\303\245 utfylles", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowCities: public Ui_ShowCities {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCITIES_H
