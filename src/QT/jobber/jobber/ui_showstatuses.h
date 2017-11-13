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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QLabel *labelStatusID;
    QLabel *labelStatus;
    QPushButton *btnFirst;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QPushButton *btnSave;
    QPushButton *btnDelete;
    QComboBox *comboBoxStatusID;
    QLineEdit *lineEdit;
    QLabel *labelInfo;

    void setupUi(QMainWindow *ShowStatuses)
    {
        if (ShowStatuses->objectName().isEmpty())
            ShowStatuses->setObjectName(QStringLiteral("ShowStatuses"));
        ShowStatuses->resize(387, 178);
        ShowStatuses->setMinimumSize(QSize(377, 150));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        ShowStatuses->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("jobber.png"), QSize(), QIcon::Normal, QIcon::Off);
        ShowStatuses->setWindowIcon(icon);
        centralwidget = new QWidget(ShowStatuses);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelStatusID = new QLabel(centralwidget);
        labelStatusID->setObjectName(QStringLiteral("labelStatusID"));

        gridLayout->addWidget(labelStatusID, 1, 0, 1, 1);

        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));

        gridLayout->addWidget(labelStatus, 2, 0, 1, 1);

        btnFirst = new QPushButton(centralwidget);
        btnFirst->setObjectName(QStringLiteral("btnFirst"));
        btnFirst->setEnabled(false);

        gridLayout->addWidget(btnFirst, 3, 0, 1, 1);

        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName(QStringLiteral("btnPrev"));
        btnPrev->setEnabled(false);

        gridLayout->addWidget(btnPrev, 3, 1, 1, 1);

        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QStringLiteral("btnNext"));

        gridLayout->addWidget(btnNext, 3, 2, 1, 1);

        btnLast = new QPushButton(centralwidget);
        btnLast->setObjectName(QStringLiteral("btnLast"));

        gridLayout->addWidget(btnLast, 3, 3, 1, 1);

        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setEnabled(false);

        gridLayout->addWidget(btnSave, 3, 4, 1, 1);

        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        gridLayout->addWidget(btnDelete, 3, 5, 1, 1);

        comboBoxStatusID = new QComboBox(centralwidget);
        comboBoxStatusID->setObjectName(QStringLiteral("comboBoxStatusID"));

        gridLayout->addWidget(comboBoxStatusID, 1, 1, 1, 3);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 2, 1, 1, 3);

        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));
        labelInfo->setWordWrap(true);

        gridLayout->addWidget(labelInfo, 0, 0, 1, 6);

        ShowStatuses->setCentralWidget(centralwidget);

        retranslateUi(ShowStatuses);

        QMetaObject::connectSlotsByName(ShowStatuses);
    } // setupUi

    void retranslateUi(QMainWindow *ShowStatuses)
    {
        ShowStatuses->setWindowTitle(QApplication::translate("ShowStatuses", "Vis innlagte statuser", Q_NULLPTR));
        labelStatusID->setText(QApplication::translate("ShowStatuses", "StatusID", Q_NULLPTR));
        labelStatus->setText(QApplication::translate("ShowStatuses", "Status", Q_NULLPTR));
        btnFirst->setText(QApplication::translate("ShowStatuses", "<<", Q_NULLPTR));
        btnPrev->setText(QApplication::translate("ShowStatuses", "<", Q_NULLPTR));
        btnNext->setText(QApplication::translate("ShowStatuses", ">", Q_NULLPTR));
        btnLast->setText(QApplication::translate("ShowStatuses", ">>", Q_NULLPTR));
        btnSave->setText(QApplication::translate("ShowStatuses", "Lagre", Q_NULLPTR));
        btnDelete->setText(QApplication::translate("ShowStatuses", "Slett", Q_NULLPTR));
        labelInfo->setText(QApplication::translate("ShowStatuses", "Her kan du se de ulike statusene som er registrert i systemet. Vil du endre p\303\245 ID-en til en status, m\303\245 det gj\303\270res i kommandolinja.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowStatuses: public Ui_ShowStatuses {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSTATUSES_H
