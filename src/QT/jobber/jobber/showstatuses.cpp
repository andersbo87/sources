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

#include "showstatuses.h"
#include "ui_showstatuses.h"

/**
 * @brief ShowStatuses::ShowStatuses The ShowStatuses class constructor
 * @param windowTitle The title to be used with message boxes (QMessageBox)
 * @param pg A pointer to the PostgreSQL database class.
 * @param parent
 */
ShowStatuses::ShowStatuses(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowStatuses)
{
    p = pg;
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    winTitle = windowTitle;
    ui->setupUi(this);
    setFixedHeight(height());
    connect(ui->btnFirst, SIGNAL(clicked(bool)), this, SLOT(buttonFirstClicked()));
    connect(ui->btnLast, SIGNAL(clicked(bool)), this, SLOT(buttonLastClicked()));
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(buttonNextClicked()));
    connect(ui->btnPrev, SIGNAL(clicked(bool)), this, SLOT(buttonPreviousClicked()));
    connect(ui->comboBoxStatusID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxStatusIDChanged()));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineEditStatusnameChanged()));
    getStatuses();
    getStatus(1);
    changed = false;
    statusIDchanged = false;
}

// Metoder som henter verdier
/**
 * @brief ShowStatuses::getStatusID Gets the identification number of the current status.
 * @return The ID of the current status.
 */
int ShowStatuses::getStatusID()
{
    return statusID;
}

/**
 * @brief ShowStatuses::getStatusName Gets the name of the current status
 * @return The current status name
 */
QString ShowStatuses::getStatusName()
{
    return statusName;
}

// Metoder som setter verdier
/**
 * @brief ShowStatuses::setStatusID Changes the current status ID
 * @param newID The new status ID
 */
void ShowStatuses::setStatusID(int newID)
{
    statusID = newID;
}

/**
 * @brief ShowStatuses::setStatusName Changes the name of the current status.
 * @param newName The new status name.
 */
void ShowStatuses::setStatusName(QString newName)
{
    statusName = newName;
}

// Andre offentlige metoder
/**
 * @brief ShowStatuses::getStatus Fetches information from the database about the current status and fills the combobox and textbox with appropriate data.
 * @param statusID The identification number of the status in question.
 */
void ShowStatuses::getStatus(int statusID)
{
    try
    {
        ui->comboBoxStatusID->setCurrentText(QString::number(statusID));
        ui->lineEdit->setText(p->getStatusName(statusID));
        setStatusID(statusID);
        setStatusName(ui->lineEdit->text());
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText(e.what());
        msg.exec();
    }
}

/**
 * @brief ShowStatuses::getStatuses Builds a list of all status IDs in the database. This list is then added to the comboBoxStatusID
 */
void ShowStatuses::getStatuses()
{
    try
    {
        QLinkedList<int> list = p->fillList("SELECT statusid FROM status ORDER BY statusid ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBoxStatusID->addItem(QString::number(i+1));
            i++;
        }
        lastID = i;
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText(e.what());
        msg.exec();
    }
}

ShowStatuses::~ShowStatuses()
{
    delete ui;
}
// Private metoder
void ShowStatuses::closeEvent(QCloseEvent *event)
{
    if(isChanged())
    {
        event->ignore();
        QMessageBox msg;
        msg.setWindowTitle(winTitle);
        msg.setIcon(msg.Question);
        msg.setStandardButtons(msg.Yes);
        msg.addButton(msg.No);
        msg.setDefaultButton(msg.Yes);
        msg.setText("Du har noen ulagrede endringer. Vil du lagre disse?");
        int res = msg.exec();
        if(msg.exec() == QMessageBox::Yes)
        {
            if(p->updateStatus(getStatusName(), getStatusID()))
            {
                QMessageBox msg2;
                msg2.setWindowTitle(winTitle);
                msg2.setIcon(msg2.Information);
                msg2.setText("Statusen ble oppdatert slik at den har følende verdier:\nStatusID: " + QString::number(getStatusID()) + "\nNavn: " + getStatusName());
                msg2.exec();
            }
            event->accept();
        }
        else if(res == QMessageBox::No)
        {
            event->accept();
        }
    }
}

/**
 * @brief ShowStatuses::isChanged Checks if there are unsaved changes in the current status record.
 * @return True if there are unsaved changes and false otherwise.
 */
bool ShowStatuses::isChanged()
{
    return changed;
}

/**
 * @brief ShowStatuses::setChanged Use this method once a change have been saved to the database or if the user is modifying some data.
 * @param change True if there have been one or more changes and false if the changes have been saved.
 */
void ShowStatuses::setChanged(bool change)
{
    changed = change;
}

/**
 * @brief ShowStatuses::checkChanges Checks if there are any unsaved changes.
 */
void ShowStatuses::checkChanges()
{
    if(isChanged())
    {
        QMessageBox msg;
        msg.setWindowTitle(winTitle);
        msg.setIcon(msg.Question);
        msg.setStandardButtons(msg.Yes);
        msg.addButton(msg.No);
        msg.setDefaultButton(msg.Yes);
        msg.setText("Du har noen ulagrede endringer. Vil du lagre disse?");
        if(msg.exec() == QMessageBox::Yes)
        {
            if(p->updateStatus(getStatusName(), getStatusID()))
            {
                QMessageBox msg2;
                msg2.setWindowTitle(winTitle);
                msg2.setIcon(msg2.Information);
                msg2.setText("Statusen ble oppdatert slik at den har følende verdier:\nStatusID: " + QString::number(getStatusID()) + "\nNavn: " + getStatusName());
                msg2.exec();
            }
        }
        setChanged(false);
    }
}

// Metoder definert under "private slots":
void ShowStatuses::buttonFirstClicked()
{
    checkChanges();
    getStatus(1);
    ui->btnFirst->setEnabled(false);
    ui->btnLast->setEnabled(false);
    ui->btnNext->setEnabled(true);
    ui->btnPrev->setEnabled(true);
}

void ShowStatuses::buttonLastClicked()
{
    checkChanges();
    getStatus(lastID);
    ui->btnFirst->setEnabled(true);
    ui->btnLast->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->btnPrev->setEnabled(true);
}

void ShowStatuses::buttonNextClicked()
{
    checkChanges();
    int currStatus = getStatusID();
    getStatus(currStatus +1);
    ui->btnFirst->setEnabled(true);
    ui->btnPrev->setEnabled(true);
    if(currStatus +1 == lastID)
    {
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
    }
}

void ShowStatuses::buttonPreviousClicked()
{
    checkChanges();
    int currStatus = getStatusID();
    getStatus(currStatus -1);
    ui->btnLast->setEnabled(true);
    ui->btnNext->setEnabled(true);
    if(currStatus-1 == 1)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnPrev->setEnabled(false);
    }
}

void ShowStatuses::comboboxStatusIDChanged()
{
    int currID = ui->comboBoxStatusID->currentText().toInt();
    checkChanges();
    statusIDchanged = true;
    getStatus(currID);
    statusIDchanged = false;
    if(currID == 1)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        ui->btnPrev->setEnabled(false);

    }
    else if(currID == lastID)
    {
        ui->btnFirst->setEnabled(true);
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
        ui->btnPrev->setEnabled(true);
    }
    else
    {
        ui->btnFirst->setEnabled(true);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        ui->btnPrev->setEnabled(true);
    }
}

void ShowStatuses::lineEditStatusnameChanged()
{
    setStatusName(ui->lineEdit->text());
    if(!statusIDchanged)
        setChanged(true);
}
