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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_connectPsql
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_Host;
    QLineEdit *lineEdit_User;
    QLineEdit *lineEdit_Password;
    QLabel *label_4;

    void setupUi(QDialog *connectPsql)
    {
        if (connectPsql->objectName().isEmpty())
            connectPsql->setObjectName(QStringLiteral("connectPsql"));
        connectPsql->resize(400, 185);
        buttonBox = new QDialogButtonBox(connectPsql);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 140, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(connectPsql);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 50, 81, 16));
        label_2 = new QLabel(connectPsql);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 80, 71, 16));
        label_3 = new QLabel(connectPsql);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 110, 59, 14));
        lineEdit_Host = new QLineEdit(connectPsql);
        lineEdit_Host->setObjectName(QStringLiteral("lineEdit_Host"));
        lineEdit_Host->setGeometry(QRect(150, 50, 151, 22));
        lineEdit_User = new QLineEdit(connectPsql);
        lineEdit_User->setObjectName(QStringLiteral("lineEdit_User"));
        lineEdit_User->setGeometry(QRect(150, 80, 151, 22));
        lineEdit_Password = new QLineEdit(connectPsql);
        lineEdit_Password->setObjectName(QStringLiteral("lineEdit_Password"));
        lineEdit_Password->setGeometry(QRect(150, 110, 151, 22));
        lineEdit_Password->setEchoMode(QLineEdit::Password);
        label_4 = new QLabel(connectPsql);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 10, 351, 31));
        label_4->setScaledContents(false);
        label_4->setWordWrap(true);

        retranslateUi(connectPsql);
        QObject::connect(buttonBox, SIGNAL(accepted()), connectPsql, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), connectPsql, SLOT(reject()));

        QMetaObject::connectSlotsByName(connectPsql);
    } // setupUi

    void retranslateUi(QDialog *connectPsql)
    {
        connectPsql->setWindowTitle(QApplication::translate("connectPsql", "Logg inn til PostgreSQL", Q_NULLPTR));
        label->setText(QApplication::translate("connectPsql", "IP-adresse", Q_NULLPTR));
        label_2->setText(QApplication::translate("connectPsql", "Brukernavn", Q_NULLPTR));
        label_3->setText(QApplication::translate("connectPsql", "Passord", Q_NULLPTR));
        label_4->setText(QApplication::translate("connectPsql", "Skriv inn informasjonen som brukes under oppkoblingen. Kobler du til lokalt, bruk adressen 127.0.0.1.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class connectPsql: public Ui_connectPsql {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTPSQL_H
