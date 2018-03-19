/********************************************************************************
** Form generated from reading UI file 'spesificjobs.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPESIFICJOBS_H
#define UI_SPESIFICJOBS_H

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
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpesicficJobs
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *labelInfo;
    QLabel *labelJobTitle;
    QLineEdit *lineEditJobTitle;
    QLabel *labelCompanyName;
    QLineEdit *lineEditCompanyName;
    QLabel *labelCityID;
    QComboBox *comboBoxCityName;
    QLabel *labelStatusID;
    QComboBox *comboBoxStatusName;
    QLabel *labelDeadline;
    QLineEdit *lineEditDeadline;
    QPushButton *btnSearch;
    QTableView *tableViewResults;

    void setupUi(QMainWindow *SpesicficJobs)
    {
        if (SpesicficJobs->objectName().isEmpty())
            SpesicficJobs->setObjectName(QStringLiteral("SpesicficJobs"));
        SpesicficJobs->resize(473, 434);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        SpesicficJobs->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        SpesicficJobs->setWindowIcon(icon);
        centralwidget = new QWidget(SpesicficJobs);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));

        gridLayout->addWidget(labelInfo, 0, 0, 1, 2);

        labelJobTitle = new QLabel(centralwidget);
        labelJobTitle->setObjectName(QStringLiteral("labelJobTitle"));

        gridLayout->addWidget(labelJobTitle, 1, 0, 1, 1);

        lineEditJobTitle = new QLineEdit(centralwidget);
        lineEditJobTitle->setObjectName(QStringLiteral("lineEditJobTitle"));

        gridLayout->addWidget(lineEditJobTitle, 1, 1, 1, 1);

        labelCompanyName = new QLabel(centralwidget);
        labelCompanyName->setObjectName(QStringLiteral("labelCompanyName"));

        gridLayout->addWidget(labelCompanyName, 2, 0, 1, 1);

        lineEditCompanyName = new QLineEdit(centralwidget);
        lineEditCompanyName->setObjectName(QStringLiteral("lineEditCompanyName"));

        gridLayout->addWidget(lineEditCompanyName, 2, 1, 1, 1);

        labelCityID = new QLabel(centralwidget);
        labelCityID->setObjectName(QStringLiteral("labelCityID"));

        gridLayout->addWidget(labelCityID, 3, 0, 1, 1);

        comboBoxCityName = new QComboBox(centralwidget);
        comboBoxCityName->setObjectName(QStringLiteral("comboBoxCityName"));

        gridLayout->addWidget(comboBoxCityName, 3, 1, 1, 1);

        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));

        gridLayout->addWidget(labelStatusID, 4, 0, 1, 1);

        comboBoxStatusName = new QComboBox(centralwidget);
        comboBoxStatusName->setObjectName(QStringLiteral("comboBoxStatusName"));

        gridLayout->addWidget(comboBoxStatusName, 4, 1, 1, 1);

        labelDeadline = new QLabel(centralwidget);
        labelDeadline->setObjectName(QStringLiteral("labelDeadline"));

        gridLayout->addWidget(labelDeadline, 5, 0, 1, 1);

        lineEditDeadline = new QLineEdit(centralwidget);
        lineEditDeadline->setObjectName(QStringLiteral("lineEditDeadline"));

        gridLayout->addWidget(lineEditDeadline, 5, 1, 1, 1);

        btnSearch = new QPushButton(centralwidget);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));

        gridLayout->addWidget(btnSearch, 6, 0, 1, 1);

        tableViewResults = new QTableView(centralwidget);
        tableViewResults->setObjectName(QStringLiteral("tableViewResults"));
        tableViewResults->setEnabled(true);

        gridLayout->addWidget(tableViewResults, 7, 0, 1, 2);

        SpesicficJobs->setCentralWidget(centralwidget);

        retranslateUi(SpesicficJobs);

        QMetaObject::connectSlotsByName(SpesicficJobs);
    } // setupUi

    void retranslateUi(QMainWindow *SpesicficJobs)
    {
        SpesicficJobs->setWindowTitle(QApplication::translate("SpesicficJobs", "Vis utvalgte jobber", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("SpesicficJobs", "Her kan du gj\303\270re et s\303\270k med spesifikke utvalg (dato, statusid, etc).", Q_NULLPTR));
        labelJobTitle->setText(QApplication::translate("SpesicficJobs", "Tittel", Q_NULLPTR));
        labelCompanyName->setText(QApplication::translate("SpesicficJobs", "Bedrift", Q_NULLPTR));
        labelCityID->setText(QApplication::translate("SpesicficJobs", "Stedsnavn", Q_NULLPTR));
        labelStatusID->setText(QApplication::translate("SpesicficJobs", "Status", Q_NULLPTR));
        labelDeadline->setText(QApplication::translate("SpesicficJobs", "S\303\270knadsfrist", Q_NULLPTR));
        btnSearch->setText(QApplication::translate("SpesicficJobs", "S\303\270k!", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SpesicficJobs: public Ui_SpesicficJobs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPESIFICJOBS_H
