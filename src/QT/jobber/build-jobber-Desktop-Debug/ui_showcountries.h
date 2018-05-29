/********************************************************************************
** Form generated from reading UI file 'showcountries.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QLabel *labelLandID;
    QComboBox *comboBoxLandID;
    QLabel *labelCountryName;
    QLineEdit *lineEditCountryName;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QPushButton *btnSave;
    QPushButton *btnDelete;
    QLabel *labelInfo;

    void setupUi(QMainWindow *ShowCountries)
    {
        if (ShowCountries->objectName().isEmpty())
            ShowCountries->setObjectName(QStringLiteral("ShowCountries"));
        ShowCountries->resize(576, 151);
        ShowCountries->setMinimumSize(QSize(548, 151));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        ShowCountries->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        ShowCountries->setWindowIcon(icon);
        centralwidget = new QWidget(ShowCountries);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelLandID = new QLabel(centralwidget);
        labelLandID->setObjectName(QStringLiteral("labelLandID"));

        gridLayout->addWidget(labelLandID, 1, 0, 1, 1);

        comboBoxLandID = new QComboBox(centralwidget);
        comboBoxLandID->setObjectName(QStringLiteral("comboBoxLandID"));

        gridLayout->addWidget(comboBoxLandID, 1, 1, 1, 2);

        labelCountryName = new QLabel(centralwidget);
        labelCountryName->setObjectName(QStringLiteral("labelCountryName"));

        gridLayout->addWidget(labelCountryName, 2, 0, 1, 1);

        lineEditCountryName = new QLineEdit(centralwidget);
        lineEditCountryName->setObjectName(QStringLiteral("lineEditCountryName"));

        gridLayout->addWidget(lineEditCountryName, 2, 1, 1, 2);

        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);

        gridLayout->addWidget(btnFirst, 3, 0, 1, 1);

        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);

        gridLayout->addWidget(btnPrev, 3, 1, 1, 1);

        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));

        gridLayout->addWidget(btnNext, 3, 2, 1, 1);

        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));

        gridLayout->addWidget(btnLast, 3, 3, 1, 1);

        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setEnabled(false);

        gridLayout->addWidget(btnSave, 3, 4, 1, 1);

        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        gridLayout->addWidget(btnDelete, 3, 5, 1, 1);

        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setWordWrap(true);

        gridLayout->addWidget(labelInfo, 0, 0, 1, 6);

        ShowCountries->setCentralWidget(centralwidget);

        retranslateUi(ShowCountries);

        QMetaObject::connectSlotsByName(ShowCountries);
    } // setupUi

    void retranslateUi(QMainWindow *ShowCountries)
    {
        ShowCountries->setWindowTitle(QApplication::translate("ShowCountries", "Vis innlagte land", nullptr));
        labelLandID->setText(QApplication::translate("ShowCountries", "LandID*", nullptr));
        labelCountryName->setText(QApplication::translate("ShowCountries", "Landnavn*", nullptr));
        btnFirst->setText(QApplication::translate("ShowCountries", "<<", nullptr));
        btnPrev->setText(QApplication::translate("ShowCountries", "<", nullptr));
        btnNext->setText(QApplication::translate("ShowCountries", ">", nullptr));
        btnLast->setText(QApplication::translate("ShowCountries", ">>", nullptr));
        btnSave->setText(QApplication::translate("ShowCountries", "Lagre", nullptr));
        btnDelete->setText(QApplication::translate("ShowCountries", "Slett", nullptr));
        labelInfo->setText(QApplication::translate("ShowCountries", "Her kan du se de ulike statusene som er registrert i systemet. Vil du endre p\303\245 ID-en til en status, m\303\245 det gj\303\270res i kommandolinja. Alle felt m\303\245 utfylles.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowCountries: public Ui_ShowCountries {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWCOUNTRIES_H
