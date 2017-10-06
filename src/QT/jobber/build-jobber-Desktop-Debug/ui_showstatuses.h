/********************************************************************************
** Form generated from reading UI file 'showstatuses.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSTATUSES_H
#define UI_SHOWSTATUSES_H

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

class Ui_ShowStatuses
{
public:
    QWidget *centralwidget;
    QPushButton *btnNext;
    QPushButton *btnFirst;
    QPushButton *btnLast;
    QPushButton *btnPrev;
    QLabel *labelInfo;
    QLabel *labelStatusID;
    QComboBox *comboBoxStatusID;
    QLabel *labelStatus;
    QLineEdit *lineEdit;

    void setupUi(QMainWindow *ShowStatuses)
    {
        if (ShowStatuses->objectName().isEmpty())
            ShowStatuses->setObjectName(QStringLiteral("ShowStatuses"));
        ShowStatuses->resize(332, 197);
        centralwidget = new QWidget(ShowStatuses);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setGeometry(QRect(140, 150, 31, 23));
        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);
        btnFirst->setGeometry(QRect(40, 150, 31, 23));
        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));
        btnLast->setGeometry(QRect(190, 150, 31, 23));
        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);
        btnPrev->setGeometry(QRect(90, 150, 31, 23));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setGeometry(QRect(40, 20, 281, 51));
        labelInfo->setWordWrap(true);
        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));
        labelStatusID->setGeometry(QRect(40, 90, 59, 15));
        comboBoxStatusID = new QComboBox(centralwidget);
        comboBoxStatusID->setObjectName(QStringLiteral("comboBoxStatusID"));
        comboBoxStatusID->setGeometry(QRect(110, 90, 79, 23));
        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        labelStatus->setGeometry(QRect(40, 120, 59, 15));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 120, 113, 23));
        ShowStatuses->setCentralWidget(centralwidget);

        retranslateUi(ShowStatuses);

        QMetaObject::connectSlotsByName(ShowStatuses);
    } // setupUi

    void retranslateUi(QMainWindow *ShowStatuses)
    {
        ShowStatuses->setWindowTitle(QApplication::translate("ShowStatuses", "Vis innlagte statuser", Q_NULLPTR));
        btnNext->setText(QApplication::translate("ShowStatuses", ">", Q_NULLPTR));
        btnFirst->setText(QApplication::translate("ShowStatuses", "<<", Q_NULLPTR));
        btnLast->setText(QApplication::translate("ShowStatuses", ">>", Q_NULLPTR));
        btnPrev->setText(QApplication::translate("ShowStatuses", "<", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("ShowStatuses", "Her kan du se de ulike statusene som er registrert i systemet. Vil du endre p\303\245 ID-en til en status, m\303\245 det gj\303\270res i kommandolinja.", Q_NULLPTR));
        labelStatusID->setText(QApplication::translate("ShowStatuses", "StatusID", Q_NULLPTR));
        labelStatus->setText(QApplication::translate("ShowStatuses", "Status", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowStatuses: public Ui_ShowStatuses {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSTATUSES_H
