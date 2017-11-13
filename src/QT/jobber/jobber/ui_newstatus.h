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
#include <QtWidgets/QFormLayout>
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
    QFormLayout *formLayout;
    QLabel *labelInfo;
    QLabel *labelStatusName;
    QLineEdit *lineEditStatusName;
    QDialogButtonBox *buttonBox;

    void setupUi(QMainWindow *NewStatus)
    {
        if (NewStatus->objectName().isEmpty())
            NewStatus->setObjectName(QStringLiteral("NewStatus"));
        NewStatus->resize(352, 100);
        NewStatus->setMinimumSize(QSize(352, 100));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        NewStatus->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewStatus->setWindowIcon(icon);
        centralwidget = new QWidget(NewStatus);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, labelInfo);

        labelStatusName = new QLabel(centralwidget);
        labelStatusName->setObjectName(QStringLiteral("labelStatusName"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelStatusName);

        lineEditStatusName = new QLineEdit(centralwidget);
        lineEditStatusName->setObjectName(QStringLiteral("lineEditStatusName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditStatusName);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(2, QFormLayout::SpanningRole, buttonBox);

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
