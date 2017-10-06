/********************************************************************************
** Form generated from reading UI file 'newjob.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWJOB_H
#define UI_NEWJOB_H

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

class Ui_NewJob
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEditTittel;
    QLabel *labelBedrift;
    QComboBox *comboBoxStatusID;
    QLabel *labelSted;
    QLineEdit *lineEditSoknadsfrist;
    QLabel *labelInfo;
    QLabel *labelTittel;
    QComboBox *comboBoxStedID;
    QDialogButtonBox *buttonBox;
    QLabel *labelStatusID;
    QLabel *labelStedid;
    QLabel *labelSoknadsfrist;
    QLabel *labelStatus;
    QLineEdit *lineEditBedrift;

    void setupUi(QMainWindow *NewJob)
    {
        if (NewJob->objectName().isEmpty())
            NewJob->setObjectName(QStringLiteral("NewJob"));
        NewJob->resize(409, 285);
        centralwidget = new QWidget(NewJob);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lineEditTittel = new QLineEdit(centralwidget);
        lineEditTittel->setObjectName(QStringLiteral("lineEditTittel"));
        lineEditTittel->setGeometry(QRect(110, 70, 291, 22));
        labelBedrift = new QLabel(centralwidget);
        labelBedrift->setObjectName(QStringLiteral("labelBedrift"));
        labelBedrift->setGeometry(QRect(10, 100, 59, 14));
        comboBoxStatusID = new QComboBox(centralwidget);
        comboBoxStatusID->setObjectName(QStringLiteral("comboBoxStatusID"));
        comboBoxStatusID->setGeometry(QRect(110, 160, 111, 22));
        labelSted = new QLabel(centralwidget);
        labelSted->setObjectName(QStringLiteral("labelSted"));
        labelSted->setGeometry(QRect(240, 130, 161, 16));
        lineEditSoknadsfrist = new QLineEdit(centralwidget);
        lineEditSoknadsfrist->setObjectName(QStringLiteral("lineEditSoknadsfrist"));
        lineEditSoknadsfrist->setGeometry(QRect(110, 190, 291, 22));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setGeometry(QRect(10, 20, 381, 41));
        labelInfo->setWordWrap(true);
        labelTittel = new QLabel(centralwidget);
        labelTittel->setObjectName(QStringLiteral("labelTittel"));
        labelTittel->setGeometry(QRect(10, 70, 59, 14));
        comboBoxStedID = new QComboBox(centralwidget);
        comboBoxStedID->setObjectName(QStringLiteral("comboBoxStedID"));
        comboBoxStedID->setGeometry(QRect(110, 130, 111, 22));
        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 230, 166, 22));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));
        labelStatusID->setGeometry(QRect(10, 160, 59, 14));
        labelStedid = new QLabel(centralwidget);
        labelStedid->setObjectName(QStringLiteral("labelStedid"));
        labelStedid->setGeometry(QRect(10, 130, 59, 14));
        labelSoknadsfrist = new QLabel(centralwidget);
        labelSoknadsfrist->setObjectName(QStringLiteral("labelSoknadsfrist"));
        labelSoknadsfrist->setGeometry(QRect(10, 190, 81, 16));
        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        labelStatus->setGeometry(QRect(240, 160, 161, 16));
        lineEditBedrift = new QLineEdit(centralwidget);
        lineEditBedrift->setObjectName(QStringLiteral("lineEditBedrift"));
        lineEditBedrift->setGeometry(QRect(110, 100, 291, 22));
        NewJob->setCentralWidget(centralwidget);
        QWidget::setTabOrder(lineEditTittel, lineEditBedrift);
        QWidget::setTabOrder(lineEditBedrift, comboBoxStedID);
        QWidget::setTabOrder(comboBoxStedID, comboBoxStatusID);
        QWidget::setTabOrder(comboBoxStatusID, lineEditSoknadsfrist);

        retranslateUi(NewJob);

        QMetaObject::connectSlotsByName(NewJob);
    } // setupUi

    void retranslateUi(QMainWindow *NewJob)
    {
        NewJob->setWindowTitle(QApplication::translate("NewJob", "MainWindow", Q_NULLPTR));
        lineEditTittel->setPlaceholderText(QApplication::translate("NewJob", "Tittelen til den nye jobben", Q_NULLPTR));
        labelBedrift->setText(QApplication::translate("NewJob", "Bedrift", Q_NULLPTR));
        labelSted->setText(QString());
        lineEditSoknadsfrist->setPlaceholderText(QApplication::translate("NewJob", "Dato, kan v\303\246re i hvilket format som helst.", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("NewJob", "Her kan du legge inn en ny s\303\270knad i databasen. Alle felt m\303\245 fylles ut.", Q_NULLPTR));
        labelTittel->setText(QApplication::translate("NewJob", "Tittel", Q_NULLPTR));
        labelStatusID->setText(QApplication::translate("NewJob", "StatusID", Q_NULLPTR));
        labelStedid->setText(QApplication::translate("NewJob", "Stedid", Q_NULLPTR));
        labelSoknadsfrist->setText(QApplication::translate("NewJob", "S\303\270knadsfrist", Q_NULLPTR));
        labelStatus->setText(QString());
        lineEditBedrift->setPlaceholderText(QApplication::translate("NewJob", "Hva heter bedriften?", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewJob: public Ui_NewJob {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWJOB_H
