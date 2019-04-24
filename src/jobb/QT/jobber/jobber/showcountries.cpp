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

#include "showcountries.h"
#include "ui_showcountries.h"

/**
 * @brief ShowCountries The ShowCountries class constructor
 * @param windowTitle The title to be used with message boxes (QMessageBox)
 * @param pg A pointer to the PostgreSQL database class.
 * @param parent
 */
ShowCountries::ShowCountries(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowCountries)
{
    ui->setupUi(this);
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    setFixedHeight(height());
    p = pg;
    winTitle = windowTitle;
    changed = false;
    connect(ui->btnFirst, SIGNAL(clicked(bool)), this, SLOT(buttonFirstClicked()), Qt::UniqueConnection);
    connect(ui->btnLast, SIGNAL(clicked(bool)), this, SLOT(buttonLastClicked()), Qt::UniqueConnection);
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(buttonNextClicked()), Qt::UniqueConnection);
    connect(ui->btnPrev, SIGNAL(clicked(bool)), this, SLOT(buttonPreviousClicked()), Qt::UniqueConnection);
    connect(ui->comboBoxLandID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxCountryIDChanged()));
    connect(ui->lineEditCountryName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCountrynameChanged()));
    connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(btnDeleteClicked()), Qt::UniqueConnection);
    connect(ui->btnSave, SIGNAL(clicked(bool)), this, SLOT(btnSaveClicked()), Qt::UniqueConnection);

}

// Metoder som henter verdier:
/**
 * @brief ShowCountries::getCountryID Gets the ID of the current country
 * @return The identification number to be returned
 */
int ShowCountries::getCountryID()
{
    return countryID;
}

/**
 * @brief ShowCountries::getCountryName Gets the name of the current country
 * @return The name of the country
 */
QString ShowCountries::getCountryName()
{
    return countryName;
}

// Metoder som setter verdier:
/**
 * @brief ShowCountries::setCountryID Sets the current identification number of a country.
 * @param newID The new country ID
 */
void ShowCountries::setCountryID(int newID)
{
    if(newID > 0)
        countryID = newID;
    else
    {
        throw invalid_argument("LandID må være > 0.");
    }
}

/**
 * @brief ShowCountries::setCountryName Sets a new name of the current country
 * @param newName The new name of the country
 */
void ShowCountries::setCountryName(QString newName)
{
    if(stringCheck::isNullOrWhitespace(newName))
        throw invalid_argument("Landnavnet kan ikke være tomt eller bare bestå av mellomrom.");
    countryName = newName;
}

// Andre offentlige metoder:
/**
 * @brief ShowCountries::getCountry Fetches information about the current country and fills the combobox and textbox with the new information.
 * @param countryID The ID of the country in question.
 */
void ShowCountries::getCountry(int countryID)
{
    try
    {
        ui->comboBoxLandID->setCurrentText(QString::number(countryID));
        ui->lineEditCountryName->setText(p->getCountryName(countryID));
        setCountryID(countryID);
        setCountryName(ui->lineEditCountryName->text());
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
 * @brief ShowCountries::getCountries Builds a QLinkedList of integers. This list is then added to the combobox.
 */
void ShowCountries::getCountries()
{
    try
    {
        QList<QString> list = p->fillList("SELECT landid FROM land ORDER BY landid ASC");
        if(list.count() == 0)
        {
            QMessageBox msg;
            msg.setWindowTitle(windowTitle());
            msg.setIcon(msg.Warning);
            msg.setText("Du har ikke lagt inn noen søknader ennå.");
            msg.exec();
            this->close();
        }
        else
        {
            int i = 0;
            QList<QString>::iterator iter;
            for(iter = list.begin(); iter != list.end(); iter++)
            {
                //ui->comboBoxLandID->addItem(QString::number(list.value(i)));
                ui->comboBoxLandID->addItem(list.value(i));
                i++;
            }
            countries = i;
        }
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


// Private methods
/**
 * @brief ShowCountries::isChanged Checks if there are unsaved changes in the current record.
 * @return True if ther have been one or more changes and false otherwise.
 */
bool ShowCountries::isChanged()
{
    return changed;
}

/**
 * @brief ShowCountries::setChanged Use this method once a change have been saved to the database or if the user is modifying some data.
 * @param change True if there have been one or more changes and false if the changes have been saved.
 */
void ShowCountries::setChanged(bool change)
{
    ui->btnSave->setEnabled(change);
    changed = change;
}

/**
 * @brief ShowCountries::checkChanges Checks if there are unsaved changes.
 */
void ShowCountries::checkChanges()
{
    if(isChanged())
    {
        // Spør om endringer skal lagres.
        QMessageBox msg;
        msg.setWindowTitle(winTitle);
        msg.setIcon(msg.Question);
        msg.setStandardButtons(msg.Yes);
        msg.addButton(msg.No);
        msg.setDefaultButton(msg.Yes);
        msg.setText("Du har gjort noen endringer. Vil du lagre disse?");
        if(msg.exec() == QMessageBox::Yes)
        {
            // Oppdaterer endringene i databasen.
            if(p->updateCountry(getCountryName(), getCountryID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(winTitle);
                msg2.setText("Landet ble oppdatert og har følgende verdier:\nLandid: " + QString::number(getCountryID()) + "\nLandnavn: " + getCountryName());
                msg2.exec();
            }
        }
        else
        {
            QMessageBox msg;
            msg.setIcon(msg.Warning);
            msg.setWindowTitle(winTitle);
            msg.setText("Noe har gått galt: " + p->getError());
            msg.exec();
        }
        setChanged(false);
    }
}


// Metoder som er definert under "private slots:"
void ShowCountries::btnDeleteClicked()
{
    QMessageBox confirm;
    confirm.setWindowTitle(winTitle);
    confirm.setIcon(confirm.Question);
    confirm.setStandardButtons(confirm.Yes);
    confirm.addButton(confirm.No);
    confirm.setDefaultButton(confirm.Yes);
    confirm.setText("Du er i ferd med å fjerne landet " + getCountryName() + " fra databasen. Dette kan ikke angres. Vil du fortsette?");
    if(confirm.exec() == QMessageBox::Yes)
    {
        if(p->deleteCountry(getCountryID()))
        {
            QMessageBox success;
            success.setWindowTitle(winTitle);
            success.setIcon(success.Information);
            success.setText("Landet " + getCountryName() + " ble fjernet fra databasen.");
            success.exec();
            ui->comboBoxLandID->removeItem(ui->comboBoxLandID->currentIndex());
            lastID = lastID -1;
            setCountryID(ui->comboBoxLandID->currentText().toInt());
            if(ui->comboBoxLandID->currentText().toInt() == lastID)
            {
                ui->btnNext->setEnabled(false);
                ui->btnLast->setEnabled(false);
            }
            if(getCountryID() == 1)
            {
                ui->btnFirst->setEnabled(false);
                ui->btnPrev->setEnabled(false);
            }
        }
        else
        {
            QMessageBox msg;
            msg.setIcon(msg.Warning);
            msg.setWindowTitle(winTitle);
            msg.setText("Noe har gått galt: " + p->getError());
            msg.exec();
        }
        setChanged(false);
    }
}

void ShowCountries::btnSaveClicked()
{
    if(p->updateCountry(getCountryName(), getCountryID()))
    {
        QMessageBox success;
        success.setWindowTitle(winTitle);
        success.setIcon(success.Information);
        success.setText("Landet ble oppdatert og har følgende verdier:\nLandid: " + QString::number(getCountryID()) + "\nLandnavn: " + getCountryName());
        success.exec();
    }
    else
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText("Noe har gått galt: " + p->getError());
        msg.exec();
    }
    setChanged(false);
}

void ShowCountries::buttonFirstClicked()
{
    try
    {
        checkChanges();
        getCountry(1);
        ui->btnFirst->setEnabled(false);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        ui->btnPrev->setEnabled(false);
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

void ShowCountries::buttonLastClicked()
{
    try
    {
        checkChanges();
        ui->comboBoxLandID->setCurrentIndex(ui->comboBoxLandID->count()-1);
        getCountry(ui->comboBoxLandID->currentText().toInt());
        ui->btnFirst->setEnabled(true);
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
        ui->btnPrev->setEnabled(true);
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

void ShowCountries::buttonNextClicked()
{
    try
    {
        checkChanges();
        int currentCountry = getCountryID(), counter = 1;
        while(QString::compare(p->getCountryName(currentCountry + counter), "", Qt::CaseSensitive) == 0)
        {
            counter++;
        }
        getCountry(currentCountry + counter);
        ui->btnFirst->setEnabled(true);
        ui->btnPrev->setEnabled(true);
        if(currentCountry + 1 == lastID)
        {
            ui->btnLast->setEnabled(false);
            ui->btnNext->setEnabled(false);
        }
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

void ShowCountries::buttonPreviousClicked()
{
    try
    {
        checkChanges();
        int currentCountry = getCountryID(), counter = 1;
        while(QString::compare(p->getCountryName(currentCountry - counter), "", Qt::CaseSensitive) == 0)
        {
            counter++;
        }
        getCountry(currentCountry - counter);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        if(currentCountry - 1 == 1)
        {
            ui->btnFirst->setEnabled(false);
            ui->btnPrev->setEnabled(false);
        }
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

void ShowCountries::comboboxCountryIDChanged()
{
    int currID = ui->comboBoxLandID->currentText().toInt();
    // Get the first item and store that in a variable:
    int firstItem = 1;
    while(ui->comboBoxLandID->findText(QString::number(firstItem)) == -1){
        firstItem++;
    }
    checkChanges();
    countryIDchanged = true;
    getCountry(currID);
    countryIDchanged = false;
    if(currID == firstItem)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        ui->btnPrev->setEnabled(false);

    }
    else if(currID == lastID || ui->comboBoxLandID->currentIndex() == ui->comboBoxLandID->count()-1)
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

void ShowCountries::lineEditCountrynameChanged()
{
    try
    {
        setCountryName(ui->lineEditCountryName->text());
        if(!countryIDchanged)
            setChanged(true);
    }
    catch(invalid_argument)
    {
        setChanged(false);
    }
}

void ShowCountries::windowLoaded()
{
    getCountries();
    getCountry(1);
    countryIDchanged = false;
    changed = false;
}

void ShowCountries::showEvent(QShowEvent *)
{
    QTimer::singleShot(50, this, SLOT(windowLoaded()));
}

void ShowCountries::closeEvent(QCloseEvent *event)
{
    if(isChanged())
    {
        event->ignore();
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
            // Oppdaterer endringene i databasen.
            if(p->updateCountry(getCountryName(), getCountryID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(winTitle);
                msg2.setText("Landet ble oppdatert og har følgende verdier:\nLandid: " + QString::number(getCountryID()) + "\nLandnavn: " + getCountryName());
                msg2.exec();
            }
            else
            {
                QMessageBox msg;
                msg.setIcon(msg.Warning);
                msg.setWindowTitle(winTitle);
                msg.setText("Noe har gått galt: " + p->getError());
                msg.exec();
            }
            event->accept();
        }
        else if(res == QMessageBox::No)
        {
            event->accept();
        }
    }
}
ShowCountries::~ShowCountries()
{
    delete ui;
}
