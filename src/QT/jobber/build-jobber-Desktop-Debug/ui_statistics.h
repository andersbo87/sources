/********************************************************************************
** Form generated from reading UI file 'statistics.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICS_H
#define UI_STATISTICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_statistics
{
public:
    QFormLayout *formLayout;
    QLabel *labelInfo;
    QLabel *labelTotal;
    QLabel *labelTotalValue;
    QLabel *labelRegistered;
    QLabel *labelRegisteredValue;
    QLabel *labelSent;
    QLabel *labelSentValue;
    QLabel *labelInterview;
    QLabel *labelInterviewValue;
    QLabel *labelDeclined;
    QLabel *labelDeclinedValue;
    QLabel *labelWrittenButNotSent;
    QLabel *labelWrittenButNotSentValue;
    QLabel *labelAccepted;
    QLabel *labelAcceptedValue;
    QPushButton *btnUpdate;
    QLabel *labelAnswered;
    QLabel *labelAnsweredValue;
    QLabel *labelDeclinedAfterInterview;
    QLabel *labelDeclinedAfterInterviewValue;

    void setupUi(QDialog *statistics)
    {
        if (statistics->objectName().isEmpty())
            statistics->setObjectName(QStringLiteral("statistics"));
        statistics->resize(432, 340);
        formLayout = new QFormLayout(statistics);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelInfo = new QLabel(statistics);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        labelInfo->setFont(font);
        labelInfo->setWordWrap(true);

        formLayout->setWidget(0, QFormLayout::SpanningRole, labelInfo);

        labelTotal = new QLabel(statistics);
        labelTotal->setObjectName(QStringLiteral("labelTotal"));
        labelTotal->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, labelTotal);

        labelTotalValue = new QLabel(statistics);
        labelTotalValue->setObjectName(QStringLiteral("labelTotalValue"));
        labelTotalValue->setFont(font);

        formLayout->setWidget(1, QFormLayout::FieldRole, labelTotalValue);

        labelRegistered = new QLabel(statistics);
        labelRegistered->setObjectName(QStringLiteral("labelRegistered"));
        labelRegistered->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, labelRegistered);

        labelRegisteredValue = new QLabel(statistics);
        labelRegisteredValue->setObjectName(QStringLiteral("labelRegisteredValue"));
        labelRegisteredValue->setFont(font);

        formLayout->setWidget(2, QFormLayout::FieldRole, labelRegisteredValue);

        labelSent = new QLabel(statistics);
        labelSent->setObjectName(QStringLiteral("labelSent"));
        labelSent->setFont(font);

        formLayout->setWidget(4, QFormLayout::LabelRole, labelSent);

        labelSentValue = new QLabel(statistics);
        labelSentValue->setObjectName(QStringLiteral("labelSentValue"));
        labelSentValue->setFont(font);

        formLayout->setWidget(4, QFormLayout::FieldRole, labelSentValue);

        labelInterview = new QLabel(statistics);
        labelInterview->setObjectName(QStringLiteral("labelInterview"));
        labelInterview->setFont(font);

        formLayout->setWidget(6, QFormLayout::LabelRole, labelInterview);

        labelInterviewValue = new QLabel(statistics);
        labelInterviewValue->setObjectName(QStringLiteral("labelInterviewValue"));
        labelInterviewValue->setFont(font);

        formLayout->setWidget(6, QFormLayout::FieldRole, labelInterviewValue);

        labelDeclined = new QLabel(statistics);
        labelDeclined->setObjectName(QStringLiteral("labelDeclined"));
        labelDeclined->setFont(font);

        formLayout->setWidget(7, QFormLayout::LabelRole, labelDeclined);

        labelDeclinedValue = new QLabel(statistics);
        labelDeclinedValue->setObjectName(QStringLiteral("labelDeclinedValue"));
        labelDeclinedValue->setFont(font);

        formLayout->setWidget(7, QFormLayout::FieldRole, labelDeclinedValue);

        labelWrittenButNotSent = new QLabel(statistics);
        labelWrittenButNotSent->setObjectName(QStringLiteral("labelWrittenButNotSent"));
        labelWrittenButNotSent->setFont(font);

        formLayout->setWidget(9, QFormLayout::LabelRole, labelWrittenButNotSent);

        labelWrittenButNotSentValue = new QLabel(statistics);
        labelWrittenButNotSentValue->setObjectName(QStringLiteral("labelWrittenButNotSentValue"));
        labelWrittenButNotSentValue->setFont(font);

        formLayout->setWidget(9, QFormLayout::FieldRole, labelWrittenButNotSentValue);

        labelAccepted = new QLabel(statistics);
        labelAccepted->setObjectName(QStringLiteral("labelAccepted"));
        labelAccepted->setFont(font);

        formLayout->setWidget(10, QFormLayout::LabelRole, labelAccepted);

        labelAcceptedValue = new QLabel(statistics);
        labelAcceptedValue->setObjectName(QStringLiteral("labelAcceptedValue"));
        labelAcceptedValue->setFont(font);

        formLayout->setWidget(10, QFormLayout::FieldRole, labelAcceptedValue);

        btnUpdate = new QPushButton(statistics);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));
        btnUpdate->setFont(font);

        formLayout->setWidget(11, QFormLayout::LabelRole, btnUpdate);

        labelAnswered = new QLabel(statistics);
        labelAnswered->setObjectName(QStringLiteral("labelAnswered"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        labelAnswered->setFont(font1);

        formLayout->setWidget(5, QFormLayout::LabelRole, labelAnswered);

        labelAnsweredValue = new QLabel(statistics);
        labelAnsweredValue->setObjectName(QStringLiteral("labelAnsweredValue"));
        labelAnsweredValue->setFont(font);

        formLayout->setWidget(5, QFormLayout::FieldRole, labelAnsweredValue);

        labelDeclinedAfterInterview = new QLabel(statistics);
        labelDeclinedAfterInterview->setObjectName(QStringLiteral("labelDeclinedAfterInterview"));
        labelDeclinedAfterInterview->setFont(font);

        formLayout->setWidget(8, QFormLayout::LabelRole, labelDeclinedAfterInterview);

        labelDeclinedAfterInterviewValue = new QLabel(statistics);
        labelDeclinedAfterInterviewValue->setObjectName(QStringLiteral("labelDeclinedAfterInterviewValue"));
        labelDeclinedAfterInterviewValue->setFont(font);

        formLayout->setWidget(8, QFormLayout::FieldRole, labelDeclinedAfterInterviewValue);


        retranslateUi(statistics);

        QMetaObject::connectSlotsByName(statistics);
    } // setupUi

    void retranslateUi(QDialog *statistics)
    {
        statistics->setWindowTitle(QApplication::translate("statistics", "Statistikk over data", nullptr));
        labelInfo->setText(QApplication::translate("statistics", "Her kan du se enkel statistikk over registrerte data, inkludert antall sendte s\303\270knader, avviste s\303\270knader, etc.", nullptr));
        labelTotal->setText(QApplication::translate("statistics", "Totalt antall s\303\270knader", nullptr));
        labelTotalValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
        labelRegistered->setText(QApplication::translate("statistics", "Antall registrerte s\303\270knader", nullptr));
        labelRegisteredValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
        labelSent->setText(QApplication::translate("statistics", "Antall sendte (ubesvarte) s\303\270knader", nullptr));
        labelSentValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
        labelInterview->setText(QApplication::translate("statistics", "Antall s\303\270knader som har f\303\270rt til intervju", nullptr));
        labelInterviewValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
        labelDeclined->setText(QApplication::translate("statistics", "Antall avviste s\303\270knader", nullptr));
        labelDeclinedValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
        labelWrittenButNotSent->setText(QApplication::translate("statistics", "Antall s\303\270knader som er skrevet men ikke sendt", nullptr));
        labelWrittenButNotSentValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
        labelAccepted->setText(QApplication::translate("statistics", "Antall godtatte s\303\270knader", nullptr));
        labelAcceptedValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
        btnUpdate->setText(QApplication::translate("statistics", "Oppdater", nullptr));
        labelAnswered->setText(QApplication::translate("statistics", "Antall besvarte s\303\270knader", nullptr));
        labelAnsweredValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
        labelDeclinedAfterInterview->setText(QApplication::translate("statistics", "Avvist etter intervju", nullptr));
        labelDeclinedAfterInterviewValue->setText(QApplication::translate("statistics", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class statistics: public Ui_statistics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICS_H
