/********************************************************************************
** Form generated from reading UI file 'viewjobs.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWJOBS_H
#define UI_VIEWJOBS_H

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

class Ui_ViewJobs
{
public:
    QWidget *centralwidget;
    QComboBox *comboBoxTownID;
    QLabel *labelSoknadsfrist;
    QLabel *labelStatusID;
    QLabel *labelSoknadID;
    QLabel *labelSted;
    QLineEdit *lineEditTitle;
    QLabel *labelInfo;
    QLabel *labelStedID;
    QLineEdit *lineEditDeadline;
    QLabel *labelStatus;
    QLabel *labelTittel;
    QPushButton *btnLast;
    QLabel *labelBedrift;
    QComboBox *comboBoxApplicationID;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QComboBox *comboBoxStatusID;
    QPushButton *btnNext;
    QLineEdit *lineEditCompany;

    void setupUi(QMainWindow *ViewJobs)
    {
        if (ViewJobs->objectName().isEmpty())
            ViewJobs->setObjectName(QStringLiteral("ViewJobs"));
        ViewJobs->resize(423, 288);
        centralwidget = new QWidget(ViewJobs);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        comboBoxTownID = new QComboBox(centralwidget);
        comboBoxTownID->setObjectName(QStringLiteral("comboBoxTownID"));
        comboBoxTownID->setGeometry(QRect(100, 150, 111, 22));
        labelSoknadsfrist = new QLabel(centralwidget);
        labelSoknadsfrist->setObjectName(QStringLiteral("labelSoknadsfrist"));
        labelSoknadsfrist->setGeometry(QRect(10, 210, 81, 16));
        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));
        labelStatusID->setGeometry(QRect(10, 180, 81, 16));
        labelSoknadID = new QLabel(centralwidget);
        labelSoknadID->setObjectName(QStringLiteral("labelSoknadID"));
        labelSoknadID->setGeometry(QRect(10, 60, 81, 16));
        labelSted = new QLabel(centralwidget);
        labelSted->setObjectName(QStringLiteral("labelSted"));
        labelSted->setGeometry(QRect(230, 150, 161, 16));
        lineEditTitle = new QLineEdit(centralwidget);
        lineEditTitle->setObjectName(QStringLiteral("lineEditTitle"));
        lineEditTitle->setGeometry(QRect(100, 90, 291, 22));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setGeometry(QRect(10, 20, 301, 31));
        labelInfo->setScaledContents(false);
        labelInfo->setWordWrap(true);
        labelStedID = new QLabel(centralwidget);
        labelStedID->setObjectName(QStringLiteral("labelStedID"));
        labelStedID->setGeometry(QRect(10, 150, 81, 16));
        lineEditDeadline = new QLineEdit(centralwidget);
        lineEditDeadline->setObjectName(QStringLiteral("lineEditDeadline"));
        lineEditDeadline->setGeometry(QRect(100, 210, 291, 22));
        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        labelStatus->setGeometry(QRect(230, 180, 161, 16));
        labelTittel = new QLabel(centralwidget);
        labelTittel->setObjectName(QStringLiteral("labelTittel"));
        labelTittel->setGeometry(QRect(10, 90, 81, 16));
        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));
        btnLast->setGeometry(QRect(160, 240, 31, 23));
        labelBedrift = new QLabel(centralwidget);
        labelBedrift->setObjectName(QStringLiteral("labelBedrift"));
        labelBedrift->setGeometry(QRect(10, 120, 81, 16));
        comboBoxApplicationID = new QComboBox(centralwidget);
        comboBoxApplicationID->setObjectName(QStringLiteral("comboBoxApplicationID"));
        comboBoxApplicationID->setGeometry(QRect(100, 60, 291, 22));
        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);
        btnFirst->setGeometry(QRect(10, 240, 31, 23));
        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);
        btnPrev->setGeometry(QRect(60, 240, 31, 23));
        comboBoxStatusID = new QComboBox(centralwidget);
        comboBoxStatusID->setObjectName(QStringLiteral("comboBoxStatusID"));
        comboBoxStatusID->setGeometry(QRect(100, 180, 111, 22));
        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setGeometry(QRect(110, 240, 31, 23));
        lineEditCompany = new QLineEdit(centralwidget);
        lineEditCompany->setObjectName(QStringLiteral("lineEditCompany"));
        lineEditCompany->setGeometry(QRect(100, 120, 291, 22));
        ViewJobs->setCentralWidget(centralwidget);

        retranslateUi(ViewJobs);

        QMetaObject::connectSlotsByName(ViewJobs);
    } // setupUi

    void retranslateUi(QMainWindow *ViewJobs)
    {
        ViewJobs->setWindowTitle(QApplication::translate("ViewJobs", "Vis innlagte jobber", Q_NULLPTR));
        labelSoknadsfrist->setText(QApplication::translate("ViewJobs", "S\303\270knadsfrist", Q_NULLPTR));
        labelStatusID->setText(QApplication::translate("ViewJobs", "StatusID", Q_NULLPTR));
        labelSoknadID->setText(QApplication::translate("ViewJobs", "S\303\270knadid", Q_NULLPTR));
        labelSted->setText(QString());
        labelInfo->setText(QApplication::translate("ViewJobs", "Her kan du se informasjon om s\303\270knadene som er registrert i databasen.", Q_NULLPTR));
        labelStedID->setText(QApplication::translate("ViewJobs", "StedID", Q_NULLPTR));
        labelStatus->setText(QString());
        labelTittel->setText(QApplication::translate("ViewJobs", "Tittel", Q_NULLPTR));
        btnLast->setText(QApplication::translate("ViewJobs", ">>", Q_NULLPTR));
        labelBedrift->setText(QApplication::translate("ViewJobs", "Bedrift", Q_NULLPTR));
        btnFirst->setText(QApplication::translate("ViewJobs", "<<", Q_NULLPTR));
        btnPrev->setText(QApplication::translate("ViewJobs", "<", Q_NULLPTR));
        btnNext->setText(QApplication::translate("ViewJobs", ">", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ViewJobs: public Ui_ViewJobs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWJOBS_H
