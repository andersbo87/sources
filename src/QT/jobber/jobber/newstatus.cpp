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

#include "newstatus.h"
#include "ui_newstatus.h"
#include <QPushButton>

/**
 * @brief NewStatus NewStatus class constructor
 * @param windowTitle The title to be used with message boxes (QMessageBox)
 * @param pg A pointer to the PostgreSQL database class
 * @param parent
 */
NewStatus::NewStatus(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewStatus)
{
    p = pg;
    ui->setupUi(this);
    winTitle = windowTitle;
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    setFixedHeight(height());
    close = false;
    changed = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Lagre");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()),this, SLOT(OKButtonClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->lineEditStatusName, SIGNAL(textChanged(QString)), this, SLOT(lineEditStatusNameChanged()));
}

/**
 * @brief NewStatus::canSave Checks if the changes can be saved
 * @return True if the changes can be saved and false otherwise.
 */
bool NewStatus::canSave()
{
    if(status.length() == 0)
        close = false;
    else
        close = true;
    return close;
}

/**
 * @brief NewStatus::setStatus Sets the new status name
 * @param newStatus the name of the new status
 */
void NewStatus::setStatus(QString newStatus)
{
    status = newStatus;
}
/**
 * @brief NewStatus::getStatus Gets the current status name
 * @return The status name to be returned.
 */
QString NewStatus::getStatus()
{
    return status;
}

/**
 * @brief closeEvent Code to be executed when the window closes
 * @param event This pointer points to the QCloseEvent class that contains functions to prvent the window from closing.
 */
void NewStatus::closeEvent(QCloseEvent *event)
{
    if(canSave())
    {
        event->ignore();
        if(changed)
        {
            QMessageBox msg;
            msg.setWindowTitle(winTitle);
            msg.setStandardButtons(msg.Yes);
            msg.addButton(msg.Cancel);
            msg.addButton(msg.No);
            msg.setDefaultButton(msg.Yes);
            msg.setText("De siste endringene du gjorde er ikke blitt lagret. Vil du lagre det nå?");
            int res = msg.exec();
            if(res == QMessageBox::Yes)
            {
                if(p->insertStatus(getStatus()))
                {
                    // Lukker vinduet.
                    QMessageBox msg;
                    msg.setWindowTitle(winTitle);
                    msg.setIcon(msg.Information);
                    msg.setText("Den nye statuse ble lagt inn med følgende data:\nStatus: " + getStatus());
                    msg.exec();
                    event->accept();
                }
            }
            else if(res==QMessageBox::No)
            {
                event->accept();
            }
        }
        else
        {
            if(p->insertStatus(getStatus()))
            {
                // Lukker vinduet.
                QMessageBox msg;
                msg.setWindowTitle(winTitle);
                msg.setIcon(msg.Information);
                msg.setText("Den nye statuse ble lagt inn med følgende data:\nStatus: " + getStatus());
                msg.exec();
                event->accept();
            }
        }
    }
}

void NewStatus::lineEditStatusNameChanged()
{
    setStatus(ui->lineEditStatusName->text());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
    changed = canSave();
}

void NewStatus::OKButtonClicked()
{
    if(canSave())
    {
        if(p->insertStatus(getStatus()))
        {
            // Lukker vinduet.
            QMessageBox msg;
            msg.setWindowTitle(winTitle);
            msg.setIcon(msg.Information);
            msg.setText("Den nye statuse ble lagt inn med følgende data:\nStatus: " + getStatus());
            msg.exec();
            hide();
        }
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle(winTitle);
        msg.setIcon(msg.Warning);
        msg.setText("Alle felt må fylles ut.");
        msg.exec();
    }
}

NewStatus::~NewStatus()
{
    delete ui;
}
