/*
Copyright (c) 2017, Anders Bolt-Evensen
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ANDERS BOLT-EVENSEN BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "connectpsql.h"
#include "ui_connectpsql.h"
#include "mainwindow.h"
#include <QMessageBox>

/**
 * @brief connectPsql::connectPsql Class constructor
 * @param windowTitle The title to be used in message boxes, etc.
 * @param parent
 */
connectPsql::connectPsql(QString windowTitle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectPsql)
{
    winTitle = windowTitle;
    p = new psql(winTitle); // Ikke verdens beste idé å gjøre denne "offentlig", men for enkelthetens skyld, i og med at jeg er ny…
    ui->setupUi(this);
    setFixedHeight(height());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Koble til");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()), Qt::UniqueConnection);
    connect(ui->lineEdit_User, SIGNAL(textChanged(QString)), this, SLOT(userTextChanged()));
    connect(ui->lineEdit_Host, SIGNAL(textChanged(QString)), this, SLOT(hostTextChanged()));
    connect(ui->lineEdit_Password, SIGNAL(textChanged(QString)), this, SLOT(passwordTextChanged()));
    connect(ui->lineEdit_Port, SIGNAL(textChanged(QString)), this, SLOT(portTextChanged()));
    QFile file(QDir::homePath() + "/.config/jobber/jobber.conf");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0, "Feil", QDir::homePath() + "/.config/jobber/jobber.config: " + file.errorString());
    }

    QTextStream in (&file);
    while(!in.atEnd()){
        QString line = in.readLine();
        if(line.startsWith("#"))
            ui->lineEdit_Port->setText("5432"); // Setting 5432 as default
        else {
            string src = line.toStdString();
            string tgt = "";
            for(char c : src) {
                if(std::isdigit(c)) tgt +=c;
            }
            line = QString::fromStdString(tgt);
            ui->lineEdit_Port->setText(line);
        }
    }

    //ui->lineEdit_Port->setText("5432");
    ui->lineEdit_Host->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit_Host->setFocus();
    this->setMinimumSize(400,185);
}

void connectPsql::accept()
{
    if(p->connectDatabase())
    {
        QDialog::accept(); // Sets the state of the dialog box to accepted
    }
    else
    {
        QMessageBox msg;
        msg.setIcon(msg.Information);
        msg.setWindowTitle(winTitle);
        if(QString::compare(p->getError(), "FATAL:  database \"jobber\" does not exist\n") == 0) {
            msg.setText("Databasen finnes ikke. Vil du opprette den?");
            msg.setStandardButtons(msg.Yes);
            msg.addButton(msg.No);
            msg.setDefaultButton(msg.Yes);
            if(msg.exec() == QMessageBox::Yes) {
	        QString mkdb = "PGPASSWORD=\"" + p->getPassword() + "\" createdb -h " + p->getHost() + " -p " + QString::number(p->getPort()) + " -U " + p->getUsername() + " jobber";
                int psqlRes = system(mkdb.toStdString().c_str());
                if (psqlRes != 0) {
                    msg.setIcon(msg.Warning);
                    msg.setText("Noe gikk galt under oppretting av databasen. Feilkode: " + QString::number(psqlRes));
                    msg.exec();
                    return;
                }
                if(p->connectDatabase()){
                    qDebug("connectDatabase successful.");
                    QDialog::accept(); // Sets the state of the dialog box to accepted
                    return; // Stops execution of this method. Because the accepted state has been set, this dialog will close.
                }
                else {
                    return; // Do nothing.
                }
            }
            else
                return; // Do nothing.
        }
        msg.setText("Oppkoblingen til databasen mislyktes. Feilmelding: " + p->getError());
        msg.exec();
    }
}

void connectPsql::portTextChanged()
{
    try {
       if(ui->lineEdit_Port->text().length() > 0)
       {
           p->setPort(ui->lineEdit_Port->text().toInt());
       }
    }
    catch (std::exception&) {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle(winTitle);
        msg.setText("Vennligst angi et heltall");
        msg.exec();
    }
}

/**
 * @brief connectPsql::userTextChanged: Sets the new username
 */
void connectPsql::userTextChanged()
{
    //userName = ui->plainTextEdit->toPlainText();
    p->setUsername(ui->lineEdit_User->text());
}

/**
 * @brief connectPsql::passwordTextChanged: Sets the new password
 */
void connectPsql::passwordTextChanged()
{
    p->setPassword(ui->lineEdit_Password->text());
}

/**
 * @brief connectPsql::hostTextChanged: Sets the new host (server's IP address).
 */
void connectPsql::hostTextChanged()
{
    p->setHost(ui->lineEdit_Host->text());
}
connectPsql::~connectPsql()
{
    delete ui;
}
