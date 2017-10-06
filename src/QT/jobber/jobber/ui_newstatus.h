/********************************************************************************
** Form generated from reading UI file 'newstatus.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSTATUS_H
#define UI_NEWSTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewStatus
{
public:
    QWidget *centralwidget;
    QLabel *labelInfo;
    QLabel *labelStatusName;
    QLineEdit *lineEditStatusName;
    QDialogButtonBox *buttonBox;

    void setupUi(QMainWindow *NewStatus)
    {
        if (NewStatus->objectName().isEmpty())
            NewStatus->setObjectName(QStringLiteral("NewStatus"));
        NewStatus->resize(310, 155);
        centralwidget = new QWidget(NewStatus);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setGeometry(QRect(20, 30, 291, 16));
        labelStatusName = new QLabel(centralwidget);
        labelStatusName->setObjectName(QStringLiteral("labelStatusName"));
        labelStatusName->setGeometry(QRect(20, 60, 59, 15));
        lineEditStatusName = new QLineEdit(centralwidget);
        lineEditStatusName->setObjectName(QStringLiteral("lineEditStatusName"));
        lineEditStatusName->setGeometry(QRect(80, 60, 113, 23));
        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 90, 166, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        NewStatus->setCentralWidget(centralwidget);

        retranslateUi(NewStatus);

        QMetaObject::connectSlotsByName(NewStatus);
    } // setupUi

    void retranslateUi(QMainWindow *NewStatus)
    {
        NewStatus->setWindowTitle(QApplication::translate("NewStatus", "Ny status", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("NewStatus", "Her kan du legge inn en ny status i databasen.", Q_NULLPTR));
        labelStatusName->setText(QApplication::translate("NewStatus", "Status", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewStatus: public Ui_NewStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSTATUS_H
