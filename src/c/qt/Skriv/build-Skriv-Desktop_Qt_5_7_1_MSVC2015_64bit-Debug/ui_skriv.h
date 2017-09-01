/********************************************************************************
** Form generated from reading UI file 'skriv.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKRIV_H
#define UI_SKRIV_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Skriv
{
public:
    QAction *actionLagre;
    QAction *actionLagre_som;
    QAction *action_pne;
    QAction *actionSkriv_ut;
    QAction *actionAvslutt;
    QAction *actionAngre;
    QAction *actionGj_r_om;
    QAction *actionFet;
    QAction *actionKursiv;
    QAction *actionUnderstrek;
    QAction *actionKlipp_ut;
    QAction *actionKopier;
    QAction *actionLim_inn;
    QAction *actionSkrifttype;
    QAction *actionEt_eller_annet;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QComboBox *comboBox;
    QFontComboBox *fontComboBox;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFil;
    QMenu *menuRediger;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *Skriv)
    {
        if (Skriv->objectName().isEmpty())
            Skriv->setObjectName(QStringLiteral("Skriv"));
        Skriv->resize(497, 368);
        Skriv->setLocale(QLocale(QLocale::NorwegianBokmal, QLocale::Norway));
        actionLagre = new QAction(Skriv);
        actionLagre->setObjectName(QStringLiteral("actionLagre"));
        actionLagre_som = new QAction(Skriv);
        actionLagre_som->setObjectName(QStringLiteral("actionLagre_som"));
        action_pne = new QAction(Skriv);
        action_pne->setObjectName(QStringLiteral("action_pne"));
        actionSkriv_ut = new QAction(Skriv);
        actionSkriv_ut->setObjectName(QStringLiteral("actionSkriv_ut"));
        actionAvslutt = new QAction(Skriv);
        actionAvslutt->setObjectName(QStringLiteral("actionAvslutt"));
        actionAngre = new QAction(Skriv);
        actionAngre->setObjectName(QStringLiteral("actionAngre"));
        actionGj_r_om = new QAction(Skriv);
        actionGj_r_om->setObjectName(QStringLiteral("actionGj_r_om"));
        actionFet = new QAction(Skriv);
        actionFet->setObjectName(QStringLiteral("actionFet"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        actionFet->setFont(font);
        actionKursiv = new QAction(Skriv);
        actionKursiv->setObjectName(QStringLiteral("actionKursiv"));
        QFont font1;
        font1.setItalic(true);
        actionKursiv->setFont(font1);
        actionUnderstrek = new QAction(Skriv);
        actionUnderstrek->setObjectName(QStringLiteral("actionUnderstrek"));
        QFont font2;
        font2.setUnderline(true);
        actionUnderstrek->setFont(font2);
        actionKlipp_ut = new QAction(Skriv);
        actionKlipp_ut->setObjectName(QStringLiteral("actionKlipp_ut"));
        actionKopier = new QAction(Skriv);
        actionKopier->setObjectName(QStringLiteral("actionKopier"));
        actionLim_inn = new QAction(Skriv);
        actionLim_inn->setObjectName(QStringLiteral("actionLim_inn"));
        actionSkrifttype = new QAction(Skriv);
        actionSkrifttype->setObjectName(QStringLiteral("actionSkrifttype"));
        actionEt_eller_annet = new QAction(Skriv);
        actionEt_eller_annet->setObjectName(QStringLiteral("actionEt_eller_annet"));
        centralWidget = new QWidget(Skriv);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 1, 0, 1, 2);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEditable(true);

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        fontComboBox = new QFontComboBox(centralWidget);
        fontComboBox->setObjectName(QStringLiteral("fontComboBox"));

        gridLayout->addWidget(fontComboBox, 0, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        Skriv->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Skriv);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 497, 19));
        menuFil = new QMenu(menuBar);
        menuFil->setObjectName(QStringLiteral("menuFil"));
        menuRediger = new QMenu(menuBar);
        menuRediger->setObjectName(QStringLiteral("menuRediger"));
        Skriv->setMenuBar(menuBar);
        statusBar = new QStatusBar(Skriv);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Skriv->setStatusBar(statusBar);
        mainToolBar = new QToolBar(Skriv);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Skriv->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFil->menuAction());
        menuBar->addAction(menuRediger->menuAction());
        menuFil->addAction(actionLagre);
        menuFil->addAction(actionLagre_som);
        menuFil->addAction(action_pne);
        menuFil->addAction(actionSkriv_ut);
        menuFil->addAction(actionAvslutt);
        menuRediger->addAction(actionAngre);
        menuRediger->addAction(actionGj_r_om);
        menuRediger->addAction(actionFet);
        menuRediger->addAction(actionKursiv);
        menuRediger->addAction(actionUnderstrek);
        menuRediger->addAction(actionKlipp_ut);
        menuRediger->addAction(actionKopier);
        menuRediger->addAction(actionLim_inn);
        mainToolBar->addAction(actionAngre);
        mainToolBar->addAction(actionGj_r_om);
        mainToolBar->addAction(actionFet);
        mainToolBar->addAction(actionKursiv);
        mainToolBar->addAction(actionUnderstrek);
        mainToolBar->addAction(actionKlipp_ut);
        mainToolBar->addAction(actionKopier);
        mainToolBar->addAction(actionLim_inn);

        retranslateUi(Skriv);
        QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), comboBox, SLOT(setCurrentIndex(int)));
        QObject::connect(Skriv, SIGNAL(windowShown()), Skriv, SLOT(show()));

        QMetaObject::connectSlotsByName(Skriv);
    } // setupUi

    void retranslateUi(QMainWindow *Skriv)
    {
        Skriv->setWindowTitle(QApplication::translate("Skriv", "Skriv", Q_NULLPTR));
        actionLagre->setText(QApplication::translate("Skriv", "Lagre", Q_NULLPTR));
        actionLagre->setShortcut(QApplication::translate("Skriv", "Ctrl+S", Q_NULLPTR));
        actionLagre_som->setText(QApplication::translate("Skriv", "Lagre som", Q_NULLPTR));
        actionLagre_som->setShortcut(QApplication::translate("Skriv", "Ctrl+Shift+S", Q_NULLPTR));
        action_pne->setText(QApplication::translate("Skriv", "\303\205pne", Q_NULLPTR));
        action_pne->setShortcut(QApplication::translate("Skriv", "Ctrl+O", Q_NULLPTR));
        actionSkriv_ut->setText(QApplication::translate("Skriv", "Skriv ut", Q_NULLPTR));
        actionSkriv_ut->setShortcut(QApplication::translate("Skriv", "Ctrl+P", Q_NULLPTR));
        actionAvslutt->setText(QApplication::translate("Skriv", "Avslutt", Q_NULLPTR));
        actionAngre->setText(QApplication::translate("Skriv", "Angre", Q_NULLPTR));
        actionAngre->setShortcut(QApplication::translate("Skriv", "Ctrl+Z", Q_NULLPTR));
        actionGj_r_om->setText(QApplication::translate("Skriv", "Gj\303\270r om", Q_NULLPTR));
        actionGj_r_om->setShortcut(QApplication::translate("Skriv", "Ctrl+Y", Q_NULLPTR));
        actionFet->setText(QApplication::translate("Skriv", "Fet", Q_NULLPTR));
        actionFet->setShortcut(QApplication::translate("Skriv", "Ctrl+B", Q_NULLPTR));
        actionKursiv->setText(QApplication::translate("Skriv", "Kursiv", Q_NULLPTR));
        actionKursiv->setShortcut(QApplication::translate("Skriv", "Ctrl+I", Q_NULLPTR));
        actionUnderstrek->setText(QApplication::translate("Skriv", "Understrek", Q_NULLPTR));
        actionUnderstrek->setShortcut(QApplication::translate("Skriv", "Ctrl+U", Q_NULLPTR));
        actionKlipp_ut->setText(QApplication::translate("Skriv", "Klipp ut", Q_NULLPTR));
        actionKlipp_ut->setShortcut(QApplication::translate("Skriv", "Ctrl+X", Q_NULLPTR));
        actionKopier->setText(QApplication::translate("Skriv", "Kopier", Q_NULLPTR));
        actionKopier->setShortcut(QApplication::translate("Skriv", "Ctrl+C", Q_NULLPTR));
        actionLim_inn->setText(QApplication::translate("Skriv", "Lim inn", Q_NULLPTR));
        actionLim_inn->setShortcut(QApplication::translate("Skriv", "Ctrl+V", Q_NULLPTR));
        actionSkrifttype->setText(QApplication::translate("Skriv", "Skrifttype", Q_NULLPTR));
        actionEt_eller_annet->setText(QApplication::translate("Skriv", "Et-eller-annet", Q_NULLPTR));
        label->setText(QApplication::translate("Skriv", "TextLabel", Q_NULLPTR));
        menuFil->setTitle(QApplication::translate("Skriv", "Fil", Q_NULLPTR));
        menuRediger->setTitle(QApplication::translate("Skriv", "Rediger", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Skriv: public Ui_Skriv {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKRIV_H
