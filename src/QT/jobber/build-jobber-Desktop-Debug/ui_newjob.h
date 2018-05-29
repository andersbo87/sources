/********************************************************************************
** Form generated from reading UI file 'newjob.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
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
#include <QtWidgets/QTextEdit>
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
    QComboBox *comboBoxSted;
    QLabel *labelStatusID;
    QComboBox *comboBoxStatusID;
    QLabel *labelSoknadsfrist;
    QLineEdit *lineEditSoknadsfrist;
    QLabel *labelMotivation;
    QTextEdit *textEditMotivation;
    QLabel *labelAsterisk;
    QDialogButtonBox *buttonBox;

    void setupUi(QMainWindow *NewJob)
    {
        if (NewJob->objectName().isEmpty())
            NewJob->setObjectName(QStringLiteral("NewJob"));
        NewJob->resize(511, 405);
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

        formLayout->setWidget(1, QFormLayout::LabelRole, labelTittel);

        lineEditTittel = new QLineEdit(centralwidget);
        lineEditTittel->setObjectName(QStringLiteral("lineEditTittel"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditTittel);

        labelBedrift = new QLabel(centralwidget);
        labelBedrift->setObjectName(QStringLiteral("labelBedrift"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelBedrift);

        lineEditBedrift = new QLineEdit(centralwidget);
        lineEditBedrift->setObjectName(QStringLiteral("lineEditBedrift"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditBedrift);

        labelStedid = new QLabel(centralwidget);
        labelStedid->setObjectName(QStringLiteral("labelStedid"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelStedid);

        comboBoxSted = new QComboBox(centralwidget);
        comboBoxSted->setObjectName(QStringLiteral("comboBoxSted"));

        formLayout->setWidget(3, QFormLayout::FieldRole, comboBoxSted);

        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelStatusID);

        comboBoxStatusID = new QComboBox(centralwidget);
        comboBoxStatusID->setObjectName(QStringLiteral("comboBoxStatusID"));

        formLayout->setWidget(4, QFormLayout::FieldRole, comboBoxStatusID);

        labelSoknadsfrist = new QLabel(centralwidget);
        labelSoknadsfrist->setObjectName(QStringLiteral("labelSoknadsfrist"));

        formLayout->setWidget(5, QFormLayout::LabelRole, labelSoknadsfrist);

        lineEditSoknadsfrist = new QLineEdit(centralwidget);
        lineEditSoknadsfrist->setObjectName(QStringLiteral("lineEditSoknadsfrist"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditSoknadsfrist);

        labelMotivation = new QLabel(centralwidget);
        labelMotivation->setObjectName(QStringLiteral("labelMotivation"));

        formLayout->setWidget(6, QFormLayout::LabelRole, labelMotivation);

        textEditMotivation = new QTextEdit(centralwidget);
        textEditMotivation->setObjectName(QStringLiteral("textEditMotivation"));

        formLayout->setWidget(6, QFormLayout::FieldRole, textEditMotivation);

        labelAsterisk = new QLabel(centralwidget);
        labelAsterisk->setObjectName(QStringLiteral("labelAsterisk"));

        formLayout->setWidget(7, QFormLayout::SpanningRole, labelAsterisk);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(8, QFormLayout::SpanningRole, buttonBox);

        NewJob->setCentralWidget(centralwidget);
        QWidget::setTabOrder(lineEditTittel, lineEditBedrift);
        QWidget::setTabOrder(lineEditBedrift, comboBoxSted);
        QWidget::setTabOrder(comboBoxSted, comboBoxStatusID);
        QWidget::setTabOrder(comboBoxStatusID, lineEditSoknadsfrist);
        QWidget::setTabOrder(lineEditSoknadsfrist, textEditMotivation);

        retranslateUi(NewJob);

        QMetaObject::connectSlotsByName(NewJob);
    } // setupUi

    void retranslateUi(QMainWindow *NewJob)
    {
        NewJob->setWindowTitle(QApplication::translate("NewJob", "Legg til en ny jobb", nullptr));
        labelInfo->setText(QApplication::translate("NewJob", "Her kan du legge inn en ny s\303\270knad i databasen. Alle felt m\303\245 fylles ut.", nullptr));
        labelTittel->setText(QApplication::translate("NewJob", "Tittel*", nullptr));
        lineEditTittel->setPlaceholderText(QApplication::translate("NewJob", "Tittelen til den nye jobben", nullptr));
        labelBedrift->setText(QApplication::translate("NewJob", "Bedrift*", nullptr));
        lineEditBedrift->setPlaceholderText(QApplication::translate("NewJob", "Hva heter bedriften?", nullptr));
        labelStedid->setText(QApplication::translate("NewJob", "Stedsnavn*", nullptr));
        labelStatusID->setText(QApplication::translate("NewJob", "Status*", nullptr));
        labelSoknadsfrist->setText(QApplication::translate("NewJob", "S\303\270knadsfrist*", nullptr));
        lineEditSoknadsfrist->setPlaceholderText(QApplication::translate("NewJob", "Dato, kan v\303\246re i hvilket format som helst.", nullptr));
        labelMotivation->setText(QApplication::translate("NewJob", "Motivasjon", nullptr));
        textEditMotivation->setPlaceholderText(QApplication::translate("NewJob", "Forklar hva som gj\303\270r deg motivert til \303\245 s\303\270ke p\303\245 denne jobben. Er det noe med bedriften som motiverer? Noe med jobben? Begge deler?", nullptr));
        labelAsterisk->setText(QApplication::translate("NewJob", "Felt merket med * m\303\245 fylles ut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewJob: public Ui_NewJob {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWJOB_H
