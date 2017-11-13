/********************************************************************************
** Form generated from reading UI file 'connectpsql.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTPSQL_H
#define UI_CONNECTPSQL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_connectPsql
{
public:
    QFormLayout *formLayout;
    QLabel *label_4;
    QLabel *label;
    QLineEdit *lineEdit_Host;
    QLabel *label_2;
    QLineEdit *lineEdit_User;
    QLabel *label_3;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_Password;

    void setupUi(QDialog *connectPsql)
    {
        if (connectPsql->objectName().isEmpty())
            connectPsql->setObjectName(QStringLiteral("connectPsql"));
        connectPsql->resize(622, 200);
        connectPsql->setMinimumSize(QSize(528, 178));
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        connectPsql->setWindowIcon(icon);
        formLayout = new QFormLayout(connectPsql);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_4 = new QLabel(connectPsql);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setScaledContents(false);
        label_4->setWordWrap(true);

        formLayout->setWidget(0, QFormLayout::SpanningRole, label_4);

        label = new QLabel(connectPsql);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        lineEdit_Host = new QLineEdit(connectPsql);
        lineEdit_Host->setObjectName(QStringLiteral("lineEdit_Host"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_Host);

        label_2 = new QLabel(connectPsql);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        lineEdit_User = new QLineEdit(connectPsql);
        lineEdit_User->setObjectName(QStringLiteral("lineEdit_User"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_User);

        label_3 = new QLabel(connectPsql);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        buttonBox = new QDialogButtonBox(connectPsql);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::SpanningRole, buttonBox);

        lineEdit_Password = new QLineEdit(connectPsql);
        lineEdit_Password->setObjectName(QStringLiteral("lineEdit_Password"));
        lineEdit_Password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_Password);


        retranslateUi(connectPsql);
        QObject::connect(buttonBox, SIGNAL(accepted()), connectPsql, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), connectPsql, SLOT(reject()));

        QMetaObject::connectSlotsByName(connectPsql);
    } // setupUi

    void retranslateUi(QDialog *connectPsql)
    {
        connectPsql->setWindowTitle(QApplication::translate("connectPsql", "Logg inn til PostgreSQL", Q_NULLPTR));
        label_4->setText(QApplication::translate("connectPsql", "Skriv inn informasjonen som brukes under oppkoblingen. Kobler du til lokalt, bruk adressen 127.0.0.1.", Q_NULLPTR));
        label->setText(QApplication::translate("connectPsql", "IP-adresse", Q_NULLPTR));
        label_2->setText(QApplication::translate("connectPsql", "Brukernavn", Q_NULLPTR));
        label_3->setText(QApplication::translate("connectPsql", "Passord", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class connectPsql: public Ui_connectPsql {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTPSQL_H
