/********************************************************************************
** Form generated from reading UI file 'viewjobs.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewJobs
{
public:
    QWidget *centralwidget;
    QLabel *labelSoknadID;
    QComboBox *comboBoxApplicationID;
    QLabel *labelTittel;
    QLineEdit *lineEditTitle;
    QLabel *labelBedrift;
    QLineEdit *lineEditCompany;
    QLabel *labelStedID;
    QComboBox *comboBoxTownID;
    QLabel *labelStatusID;
    QComboBox *comboBoxStatusID;
    QLabel *labelSoknadsfrist;
    QLineEdit *lineEditDeadline;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QPushButton *btnSave;
    QPushButton *btnDelete;
    QLabel *labelInfo;
    QLabel *labelMotivation;
    QTextEdit *textEditMotivation;

    void setupUi(QMainWindow *ViewJobs)
    {
        if (ViewJobs->objectName().isEmpty())
            ViewJobs->setObjectName(QStringLiteral("ViewJobs"));
        ViewJobs->resize(589, 466);
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
        labelSoknadID = new QLabel(centralwidget);
        labelSoknadID->setObjectName(QStringLiteral("labelSoknadID"));
        labelSoknadID->setGeometry(QRect(9, 64, 101, 19));
        comboBoxApplicationID = new QComboBox(centralwidget);
        comboBoxApplicationID->setObjectName(QStringLiteral("comboBoxApplicationID"));
        comboBoxApplicationID->setGeometry(QRect(120, 61, 451, 26));
        labelTittel = new QLabel(centralwidget);
        labelTittel->setObjectName(QStringLiteral("labelTittel"));
        labelTittel->setGeometry(QRect(9, 96, 101, 19));
        lineEditTitle = new QLineEdit(centralwidget);
        lineEditTitle->setObjectName(QStringLiteral("lineEditTitle"));
        lineEditTitle->setGeometry(QRect(120, 93, 451, 26));
        labelBedrift = new QLabel(centralwidget);
        labelBedrift->setObjectName(QStringLiteral("labelBedrift"));
        labelBedrift->setGeometry(QRect(9, 128, 101, 19));
        lineEditCompany = new QLineEdit(centralwidget);
        lineEditCompany->setObjectName(QStringLiteral("lineEditCompany"));
        lineEditCompany->setGeometry(QRect(120, 125, 451, 25));
        labelStedID = new QLabel(centralwidget);
        labelStedID->setObjectName(QStringLiteral("labelStedID"));
        labelStedID->setGeometry(QRect(9, 159, 101, 19));
        comboBoxTownID = new QComboBox(centralwidget);
        comboBoxTownID->setObjectName(QStringLiteral("comboBoxTownID"));
        comboBoxTownID->setGeometry(QRect(120, 156, 451, 26));
        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));
        labelStatusID->setGeometry(QRect(9, 191, 101, 19));
        comboBoxStatusID = new QComboBox(centralwidget);
        comboBoxStatusID->setObjectName(QStringLiteral("comboBoxStatusID"));
        comboBoxStatusID->setGeometry(QRect(120, 188, 451, 26));
        labelSoknadsfrist = new QLabel(centralwidget);
        labelSoknadsfrist->setObjectName(QStringLiteral("labelSoknadsfrist"));
        labelSoknadsfrist->setGeometry(QRect(9, 223, 101, 19));
        lineEditDeadline = new QLineEdit(centralwidget);
        lineEditDeadline->setObjectName(QStringLiteral("lineEditDeadline"));
        lineEditDeadline->setGeometry(QRect(120, 220, 451, 25));
        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);
        btnFirst->setGeometry(QRect(4, 420, 82, 26));
        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);
        btnPrev->setGeometry(QRect(92, 420, 81, 26));
        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setGeometry(QRect(179, 420, 82, 26));
        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));
        btnLast->setGeometry(QRect(267, 420, 81, 26));
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setEnabled(false);
        btnSave->setGeometry(QRect(360, 420, 101, 26));
        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(470, 420, 101, 26));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setGeometry(QRect(15, 9, 531, 41));
        labelInfo->setScaledContents(false);
        labelInfo->setWordWrap(true);
        labelMotivation = new QLabel(centralwidget);
        labelMotivation->setObjectName(QStringLiteral("labelMotivation"));
        labelMotivation->setGeometry(QRect(10, 260, 81, 16));
        textEditMotivation = new QTextEdit(centralwidget);
        textEditMotivation->setObjectName(QStringLiteral("textEditMotivation"));
        textEditMotivation->setGeometry(QRect(120, 260, 451, 141));
        ViewJobs->setCentralWidget(centralwidget);
        QWidget::setTabOrder(comboBoxApplicationID, lineEditTitle);
        QWidget::setTabOrder(lineEditTitle, lineEditCompany);
        QWidget::setTabOrder(lineEditCompany, comboBoxTownID);
        QWidget::setTabOrder(comboBoxTownID, comboBoxStatusID);
        QWidget::setTabOrder(comboBoxStatusID, lineEditDeadline);
        QWidget::setTabOrder(lineEditDeadline, textEditMotivation);
        QWidget::setTabOrder(textEditMotivation, btnFirst);
        QWidget::setTabOrder(btnFirst, btnPrev);
        QWidget::setTabOrder(btnPrev, btnNext);
        QWidget::setTabOrder(btnNext, btnLast);
        QWidget::setTabOrder(btnLast, btnSave);
        QWidget::setTabOrder(btnSave, btnDelete);

        retranslateUi(ViewJobs);

        QMetaObject::connectSlotsByName(ViewJobs);
    } // setupUi

    void retranslateUi(QMainWindow *ViewJobs)
    {
        ViewJobs->setWindowTitle(QApplication::translate("ViewJobs", "Vis innlagte jobber", nullptr));
        labelSoknadID->setText(QApplication::translate("ViewJobs", "S\303\270knadid*", nullptr));
        labelTittel->setText(QApplication::translate("ViewJobs", "Tittel*", nullptr));
        labelBedrift->setText(QApplication::translate("ViewJobs", "Bedrift*", nullptr));
        labelStedID->setText(QApplication::translate("ViewJobs", "Stedsnavn*", nullptr));
        labelStatusID->setText(QApplication::translate("ViewJobs", "Status*", nullptr));
        labelSoknadsfrist->setText(QApplication::translate("ViewJobs", "S\303\270knadsfrist*", nullptr));
        btnFirst->setText(QApplication::translate("ViewJobs", "<<", nullptr));
        btnPrev->setText(QApplication::translate("ViewJobs", "<", nullptr));
        btnNext->setText(QApplication::translate("ViewJobs", ">", nullptr));
        btnLast->setText(QApplication::translate("ViewJobs", ">>", nullptr));
        btnSave->setText(QApplication::translate("ViewJobs", "Lagre", nullptr));
        btnDelete->setText(QApplication::translate("ViewJobs", "Slett", nullptr));
        labelInfo->setText(QApplication::translate("ViewJobs", "Her kan du se informasjon om s\303\270knadene som er registrert i databasen. Felt markert med * m\303\245 fylles ut", nullptr));
        labelMotivation->setText(QApplication::translate("ViewJobs", "Motivasjon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewJobs: public Ui_ViewJobs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWJOBS_H
