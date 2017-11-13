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
#include <QtWidgets/QFormLayout>
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
    QFormLayout *formLayout;
    QLabel *labelInfo;
    QLabel *labelTittel;
    QLineEdit *lineEditTittel;
    QLabel *labelBedrift;
    QLineEdit *lineEditBedrift;
    QLabel *labelStedid;
    QComboBox *comboBoxStedID;
    QLabel *labelCityValue;
    QLabel *labelStatusID;
    QComboBox *comboBoxStatusID;
    QLabel *labelStatusValue;
    QLabel *labelSoknadsfrist;
    QLineEdit *lineEditSoknadsfrist;
    QDialogButtonBox *buttonBox;
    QLabel *labelCity;
    QLabel *labelStatus;

    void setupUi(QMainWindow *NewJob)
    {
        if (NewJob->objectName().isEmpty())
            NewJob->setObjectName(QStringLiteral("NewJob"));
        NewJob->resize(511, 285);
        NewJob->setMinimumSize(QSize(511, 285));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        NewJob->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewJob->setWindowIcon(icon);
        centralwidget = new QWidget(NewJob);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setWordWrap(true);

        formLayout->setWidget(0, QFormLayout::SpanningRole, labelInfo);

        labelTittel = new QLabel(centralwidget);
        labelTittel->setObjectName(QStringLiteral("labelTittel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelTittel);

        lineEditTittel = new QLineEdit(centralwidget);
        lineEditTittel->setObjectName(QStringLiteral("lineEditTittel"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditTittel);

        labelBedrift = new QLabel(centralwidget);
        labelBedrift->setObjectName(QStringLiteral("labelBedrift"));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelBedrift);

        lineEditBedrift = new QLineEdit(centralwidget);
        lineEditBedrift->setObjectName(QStringLiteral("lineEditBedrift"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditBedrift);

        labelStedid = new QLabel(centralwidget);
        labelStedid->setObjectName(QStringLiteral("labelStedid"));

        formLayout->setWidget(6, QFormLayout::LabelRole, labelStedid);

        comboBoxStedID = new QComboBox(centralwidget);
        comboBoxStedID->setObjectName(QStringLiteral("comboBoxStedID"));

        formLayout->setWidget(6, QFormLayout::FieldRole, comboBoxStedID);

        labelCityValue = new QLabel(centralwidget);
        labelCityValue->setObjectName(QStringLiteral("labelCityValue"));

        formLayout->setWidget(7, QFormLayout::FieldRole, labelCityValue);

        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));

        formLayout->setWidget(8, QFormLayout::LabelRole, labelStatusID);

        comboBoxStatusID = new QComboBox(centralwidget);
        comboBoxStatusID->setObjectName(QStringLiteral("comboBoxStatusID"));

        formLayout->setWidget(8, QFormLayout::FieldRole, comboBoxStatusID);

        labelStatusValue = new QLabel(centralwidget);
        labelStatusValue->setObjectName(QStringLiteral("labelStatusValue"));

        formLayout->setWidget(9, QFormLayout::FieldRole, labelStatusValue);

        labelSoknadsfrist = new QLabel(centralwidget);
        labelSoknadsfrist->setObjectName(QStringLiteral("labelSoknadsfrist"));

        formLayout->setWidget(10, QFormLayout::LabelRole, labelSoknadsfrist);

        lineEditSoknadsfrist = new QLineEdit(centralwidget);
        lineEditSoknadsfrist->setObjectName(QStringLiteral("lineEditSoknadsfrist"));

        formLayout->setWidget(10, QFormLayout::FieldRole, lineEditSoknadsfrist);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(12, QFormLayout::SpanningRole, buttonBox);

        labelCity = new QLabel(centralwidget);
        labelCity->setObjectName(QStringLiteral("labelCity"));

        formLayout->setWidget(7, QFormLayout::LabelRole, labelCity);

        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));

        formLayout->setWidget(9, QFormLayout::LabelRole, labelStatus);

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
        NewJob->setWindowTitle(QApplication::translate("NewJob", "Legg til en ny jobb", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("NewJob", "Her kan du legge inn en ny s\303\270knad i databasen. Alle felt m\303\245 fylles ut.", Q_NULLPTR));
        labelTittel->setText(QApplication::translate("NewJob", "Tittel", Q_NULLPTR));
        lineEditTittel->setPlaceholderText(QApplication::translate("NewJob", "Tittelen til den nye jobben", Q_NULLPTR));
        labelBedrift->setText(QApplication::translate("NewJob", "Bedrift", Q_NULLPTR));
        lineEditBedrift->setPlaceholderText(QApplication::translate("NewJob", "Hva heter bedriften?", Q_NULLPTR));
        labelStedid->setText(QApplication::translate("NewJob", "Stedid", Q_NULLPTR));
        labelCityValue->setText(QString());
        labelStatusID->setText(QApplication::translate("NewJob", "StatusID", Q_NULLPTR));
        labelStatusValue->setText(QString());
        labelSoknadsfrist->setText(QApplication::translate("NewJob", "S\303\270knadsfrist", Q_NULLPTR));
        lineEditSoknadsfrist->setPlaceholderText(QApplication::translate("NewJob", "Dato, kan v\303\246re i hvilket format som helst.", Q_NULLPTR));
        labelCity->setText(QApplication::translate("NewJob", "Stedsnavn", Q_NULLPTR));
        labelStatus->setText(QApplication::translate("NewJob", "Status", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewJob: public Ui_NewJob {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWJOB_H
