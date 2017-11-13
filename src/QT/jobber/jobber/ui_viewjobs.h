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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout_2;
    QLabel *labelSoknadID;
    QComboBox *comboBoxApplicationID;
    QLabel *labelTittel;
    QLineEdit *lineEditTitle;
    QLabel *labelBedrift;
    QLineEdit *lineEditCompany;
    QLabel *labelStedID;
    QComboBox *comboBoxTownID;
    QLabel *labelCityValue;
    QLabel *labelStatusID;
    QComboBox *comboBoxStatusID;
    QLabel *labelStatusValue;
    QLabel *labelSoknadsfrist;
    QLineEdit *lineEditDeadline;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QPushButton *btnSave;
    QPushButton *btnDelete;
    QLabel *labelInfo;

    void setupUi(QMainWindow *ViewJobs)
    {
        if (ViewJobs->objectName().isEmpty())
            ViewJobs->setObjectName(QStringLiteral("ViewJobs"));
        ViewJobs->resize(589, 252);
        ViewJobs->setMinimumSize(QSize(589, 252));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        ViewJobs->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        ViewJobs->setWindowIcon(icon);
        centralwidget = new QWidget(ViewJobs);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labelSoknadID = new QLabel(centralwidget);
        labelSoknadID->setObjectName(QStringLiteral("labelSoknadID"));

        gridLayout_2->addWidget(labelSoknadID, 1, 0, 1, 2);

        comboBoxApplicationID = new QComboBox(centralwidget);
        comboBoxApplicationID->setObjectName(QStringLiteral("comboBoxApplicationID"));

        gridLayout_2->addWidget(comboBoxApplicationID, 1, 2, 1, 4);

        labelTittel = new QLabel(centralwidget);
        labelTittel->setObjectName(QStringLiteral("labelTittel"));

        gridLayout_2->addWidget(labelTittel, 2, 0, 1, 2);

        lineEditTitle = new QLineEdit(centralwidget);
        lineEditTitle->setObjectName(QStringLiteral("lineEditTitle"));

        gridLayout_2->addWidget(lineEditTitle, 2, 2, 1, 4);

        labelBedrift = new QLabel(centralwidget);
        labelBedrift->setObjectName(QStringLiteral("labelBedrift"));

        gridLayout_2->addWidget(labelBedrift, 3, 0, 1, 2);

        lineEditCompany = new QLineEdit(centralwidget);
        lineEditCompany->setObjectName(QStringLiteral("lineEditCompany"));

        gridLayout_2->addWidget(lineEditCompany, 3, 2, 1, 4);

        labelStedID = new QLabel(centralwidget);
        labelStedID->setObjectName(QStringLiteral("labelStedID"));

        gridLayout_2->addWidget(labelStedID, 4, 0, 1, 2);

        comboBoxTownID = new QComboBox(centralwidget);
        comboBoxTownID->setObjectName(QStringLiteral("comboBoxTownID"));

        gridLayout_2->addWidget(comboBoxTownID, 4, 2, 1, 3);

        labelCityValue = new QLabel(centralwidget);
        labelCityValue->setObjectName(QStringLiteral("labelCityValue"));

        gridLayout_2->addWidget(labelCityValue, 4, 5, 1, 1);

        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));

        gridLayout_2->addWidget(labelStatusID, 5, 0, 1, 2);

        comboBoxStatusID = new QComboBox(centralwidget);
        comboBoxStatusID->setObjectName(QStringLiteral("comboBoxStatusID"));

        gridLayout_2->addWidget(comboBoxStatusID, 5, 2, 1, 3);

        labelStatusValue = new QLabel(centralwidget);
        labelStatusValue->setObjectName(QStringLiteral("labelStatusValue"));

        gridLayout_2->addWidget(labelStatusValue, 5, 5, 1, 1);

        labelSoknadsfrist = new QLabel(centralwidget);
        labelSoknadsfrist->setObjectName(QStringLiteral("labelSoknadsfrist"));

        gridLayout_2->addWidget(labelSoknadsfrist, 6, 0, 1, 2);

        lineEditDeadline = new QLineEdit(centralwidget);
        lineEditDeadline->setObjectName(QStringLiteral("lineEditDeadline"));

        gridLayout_2->addWidget(lineEditDeadline, 6, 2, 1, 4);

        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);

        gridLayout_2->addWidget(btnFirst, 7, 0, 1, 1);

        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);

        gridLayout_2->addWidget(btnPrev, 7, 1, 1, 1);

        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));

        gridLayout_2->addWidget(btnNext, 7, 2, 1, 1);

        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));

        gridLayout_2->addWidget(btnLast, 7, 3, 1, 1);

        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setEnabled(false);

        gridLayout_2->addWidget(btnSave, 7, 4, 1, 2);

        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        gridLayout_2->addWidget(btnDelete, 7, 6, 1, 1);

        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setScaledContents(false);
        labelInfo->setWordWrap(true);

        gridLayout_2->addWidget(labelInfo, 0, 0, 1, 7);

        ViewJobs->setCentralWidget(centralwidget);

        retranslateUi(ViewJobs);

        QMetaObject::connectSlotsByName(ViewJobs);
    } // setupUi

    void retranslateUi(QMainWindow *ViewJobs)
    {
        ViewJobs->setWindowTitle(QApplication::translate("ViewJobs", "Vis innlagte jobber", Q_NULLPTR));
        labelSoknadID->setText(QApplication::translate("ViewJobs", "S\303\270knadid", Q_NULLPTR));
        labelTittel->setText(QApplication::translate("ViewJobs", "Tittel", Q_NULLPTR));
        labelBedrift->setText(QApplication::translate("ViewJobs", "Bedrift", Q_NULLPTR));
        labelStedID->setText(QApplication::translate("ViewJobs", "StedID", Q_NULLPTR));
        labelCityValue->setText(QString());
        labelStatusID->setText(QApplication::translate("ViewJobs", "StatusID", Q_NULLPTR));
        labelStatusValue->setText(QString());
        labelSoknadsfrist->setText(QApplication::translate("ViewJobs", "S\303\270knadsfrist", Q_NULLPTR));
        btnFirst->setText(QApplication::translate("ViewJobs", "<<", Q_NULLPTR));
        btnPrev->setText(QApplication::translate("ViewJobs", "<", Q_NULLPTR));
        btnNext->setText(QApplication::translate("ViewJobs", ">", Q_NULLPTR));
        btnLast->setText(QApplication::translate("ViewJobs", ">>", Q_NULLPTR));
        btnSave->setText(QApplication::translate("ViewJobs", "Lagre endringer", Q_NULLPTR));
        btnDelete->setText(QApplication::translate("ViewJobs", "Slett", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("ViewJobs", "Her kan du se informasjon om s\303\270knadene som er registrert i databasen.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ViewJobs: public Ui_ViewJobs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWJOBS_H
