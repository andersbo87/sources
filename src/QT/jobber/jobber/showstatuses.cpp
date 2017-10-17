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
    connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(btnDeleteClicked()));
    connect(ui->btnSave, SIGNAL(clicked(bool)), this, SLOT(btnSaveClicked()));
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
        QList<int> list = p->fillList("SELECT statusid FROM status ORDER BY statusid ASC");
        int i = 0;
        QList<int>::iterator iter = list.begin();
        i = 0;
        while(iter != list.end())
        {
            ui->comboBoxStatusID->addItem(QString::number(list.value(i)));
            i++;
            iter++;
        }
        lastID = i;
        /*while(i <= list.count())
        {
            QString s = p->getStatusName(i);
            // Tar høyde for at brukeren kan ha fjernet ett eller flere elementer midt i lista:
            if(QString::compare(s, "",Qt::CaseSensitive) != 0)
            {
                ui->comboBoxStatusID->addItem(QString::number(i),QString::number(i));
            }
            else
            {
                while(QString::compare(p->getStatusName(i), "",Qt::CaseSensitive) == 0)
                {
                     // Dersom brukeren har fjernet ett eller flere elementer i lista, slik at den for eksempel er
                     // 1, 2, 4, 5, 8, 9, øker vi telleren for hvert "tomme element". Når vi kommer til 3, øker vi telleren slik
                     // at systemet går rett til 4. Kommer vi til element 6, øker vi slik at systemet går rett til element 8.

                    i++;
                }
                ui->comboBoxStatusID->addItem(QString::number(i),QString::number(i));
            }
            i++;
        }

        int itmsIncomboBox = ui->comboBoxStatusID->count();
        fprintf(stdout, "itmsIncomboBox: %d\ni: %d\n", itmsIncomboBox, i);
        if(i-itmsIncomboBox == 1)
            lastID = itmsIncomboBox;
        else
            lastID = i;
        //lst.value(lst.last());
        // Følgende linjer burde være unødvendig, men har opplevd at siste element i databasetabellen ikke ble tatt med.
        //if(QString::compare(p->getStatusName(list.value(list.last())), "",Qt::CaseSensitive) != 0)
        //{
        //    ui->comboBoxStatusID->addItem(QString::number(list.value(list.last())), list.value(list.last()));
            //ui->comboBoxStatusID->addItem(QString::number(list.value(list.last()),QString::number(list.value(list.last()))));
        //}
        //ui->comboBoxStatusID->addItem(QString::number(list.last()));



        QList<int>::iterator iter = list.begin();
        int j=0;
        while(iter != list.end())
        {
            fprintf(stdout, "%d\n",list.value(j));
            j++;
            iter++;
        }*/

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
    ui->btnSave->setEnabled(change);
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
                QMessageBox success;
                success.setWindowTitle(winTitle);
                success.setIcon(success.Information);
                success.setText("Statusen ble oppdatert slik at den har følende verdier:\nStatusID: " + QString::number(getStatusID()) + "\nNavn: " + getStatusName());
                success.exec();
            }
        }
        setChanged(false);
    }
}

// Metoder definert under "private slots":
void ShowStatuses::btnSaveClicked()
{
    if(p->updateStatus(getStatusName(), getStatusID()))
    {
        QMessageBox msg;
        msg.setWindowTitle(winTitle);
        msg.setIcon(msg.Information);
        msg.setText("Statusen ble oppdatert slik at den har følende verdier:\nStatusID: " + QString::number(getStatusID()) + "\nNavn: " + getStatusName());
        msg.exec();
    }
    setChanged(false);
}

void ShowStatuses::btnDeleteClicked()
{
    QMessageBox confirm;
    confirm.setWindowTitle(winTitle);
    confirm.setIcon(confirm.Question);
    confirm.setStandardButtons(confirm.Yes);
    confirm.addButton(confirm.No);
    confirm.setDefaultButton(confirm.Yes);
    confirm.setText("Du er i ferd med å fjerne statusen \"" + ui->lineEdit->text() + "\". Denne handlingen kan ikke angres. Er du sikker på at du vil fortsette?");
    if(confirm.exec() == QMessageBox::Yes)
    {
        if(p->deleteStatus(getStatusID()))
        {
            QMessageBox success;
            success.setWindowTitle(winTitle);
            success.setIcon(success.Information);
            success.setText("Statusen \"" + getStatusName() + "\" ble fjernet fra databasen.");
            success.exec();
            ui->comboBoxStatusID->removeItem(ui->comboBoxStatusID->currentIndex());
            lastID = lastID -1;
            setStatusID(ui->comboBoxStatusID->currentText().toInt());
            if(ui->comboBoxStatusID->currentText().toInt() == lastID)
            {
                ui->btnNext->setEnabled(false);
                ui->btnLast->setEnabled(false);
            }
            if(getStatusID() == 1)
            {
                ui->btnFirst->setEnabled(false);
                ui->btnPrev->setEnabled(false);
            }
        }
        setChanged(false);
    }
}

void ShowStatuses::buttonFirstClicked()
{
    checkChanges();
    getStatus(1);
    ui->btnFirst->setEnabled(false);
    ui->btnLast->setEnabled(true);
    ui->btnNext->setEnabled(true);
    ui->btnPrev->setEnabled(false);
}

void ShowStatuses::buttonLastClicked()
{
    checkChanges();
    ui->comboBoxStatusID->setCurrentIndex(ui->comboBoxStatusID->count()-1);
    getStatus(ui->comboBoxStatusID->currentText().toInt());
    ui->btnFirst->setEnabled(true);
    ui->btnLast->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->btnPrev->setEnabled(true);
}

void ShowStatuses::buttonNextClicked()
{
    checkChanges();
    int currStatus = getStatusID(), counter = 1;
    while(QString::compare(p->getStatusName(currStatus + counter), "", Qt::CaseSensitive) == 0)
    {
        fprintf(stdout, "Må gå enda lenger. Teller: %d\n", counter);
        counter++;
    }
    getStatus(currStatus +counter);
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
    int counter =1;
    checkChanges();
    int currStatus = getStatusID();
    while(QString::compare(p->getStatusName(currStatus - counter), "", Qt::CaseSensitive) == 0)
    {
        fprintf(stdout, "Må gå enda lenger. Teller: %d\n", counter);
        counter++;
    }
    getStatus(currStatus-counter);
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
    else if(currID == lastID || ui->comboBoxStatusID->currentIndex() == ui->comboBoxStatusID->count()-1)
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
