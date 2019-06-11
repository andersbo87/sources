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

#include "showcities.h"
#include "ui_showcities.h"

/**
 * @brief ShowCities The ShowCitis class constructor.
 * @param windowTitle The title to be used in windows, message boxes and other things.
 * @param pg A pointer to the PostgreSQL database
 * @param parent
 */
ShowCities::ShowCities(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowCities)
{
    winTitle = windowTitle;
    p = pg;
    runs = 1;
    ui->setupUi(this);
    changed = false;
    buildingList = false;
    setFixedHeight(height());
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    connect(ui->comboBoxCityID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxCityIDChanged()), Qt::UniqueConnection);
    connect(ui->comboBoxCountryID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxCountryIDChanged()), Qt::UniqueConnection);
    connect(ui->lineEditCityName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCityNameChanged()), Qt::UniqueConnection);
    connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(buttonDeleteClicked()), Qt::UniqueConnection);
    connect(ui->btnSave, SIGNAL(clicked(bool)), this, SLOT(buttonSaveClicked()), Qt::UniqueConnection);
}

/**
 * @brief ShowCities::getCityID Gets the current city ID
 * @return The city ID.
 */
int ShowCities::getCityID()
{
    return cityID;
}

/**
 * @brief ShowCities::getCountryName Gets the name of the country where the current city is located.
 * @return The country name
 */
QString ShowCities::getCountryName()
{
    return countryName;
}

/**
 * @brief ShowCities::getCountryID Gets the ID of the country where the current city is located.
 * @return The country ID.
 */
int ShowCities::getCountryID()
{
    return countryID;
}

// Metoder som angir nye verdier:
/**
 * @brief ShowCities::setCityID Sets a new city ID
 * @param newID The ID of the new city in question.
 */
void ShowCities::setCityID(int newID)
{
    if(newID > 0 && newID <= cities)
        cityID = newID;
    else
    {
        if(!buildingList)
        {
            std::ostringstream oss;
            string err = "StedID må være > 0 og <= ";
            oss << err << cities;
            oss << ". Du anga ID " << newID;
            throw invalid_argument(oss.str());
        }
    }
}

/**
 * @brief ShowCities::setCityName Sets the name of the city
 * @param newName The new city name to be used.
 */
void ShowCities::setCityName(QString newName)
{
    if(stringCheck::isNullOrWhitespace(newName) && !buildingList)
        throw invalid_argument("Stedsnavnet kan ikke være tomt, og det kan ikke bare bestå av mellomrom.");
    cityName = newName;
}

/**
 * @brief ShowCities::setCountryID Sets the ID of the country in which the city exists.
 * @param newID The new country ID
 */
void ShowCities::setCountryID(int newID)
{
    countryID = newID;
}

/**
 * @brief ShowCities::setCountryName Sets the name of the country where the current city is located.
 * @param newName The name of the country.
 */
void ShowCities::setCountryName(QString newName)
{
    if(stringCheck::isNullOrWhitespace(newName))
        throw invalid_argument("Landnavnet kan ikke være tomt. Det kan heller ikke bare bestå av mellomrom.");
    countryName = newName;
}

/**
 * @brief ShowCities::getCity Shows data about the current city based on the ID
 * @param cityID The ID of the city in question.
 */
void ShowCities::getCity(int cityID)
{
    try
    {
        //ui->comboBoxCityID->setCurrentText(QString::number(cityID));
        ui->comboBoxCityID->setCurrentText(p->getCityName(cityID));
        int actualId = p->getCityID(ui->comboBoxCityID->currentText().toStdString());
        if(actualId == cityID) {
            ui->lineEditCityName->setText(p->getCityName(cityID));
            ui->comboBoxCountryID->setCurrentText(QString::number(p->getCountryID(cityID)));
            ui->labelCountryName->setText(p->getCountryName(ui->comboBoxCountryID->currentText().toInt()));
            setCityID(cityID);
            setCountryID(ui->comboBoxCountryID->currentText().toInt());
            setCityName(ui->lineEditCityName->text());
            setCountryName(ui->labelCountryName->text());
        }
        else {
            cityID++;
            getCity(cityID);
        }
    }
    catch(invalid_argument iaex)
    {
        if(runs > 1){
            QMessageBox msg;
            msg.setIcon(msg.Warning);
            msg.setWindowTitle(winTitle);
            msg.setText(iaex.what());
            msg.exec();
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

/**
 * @brief ShowCities::getCountryIDs Builds a list of countries based on existing data in the database.
 * That data will be used to fill the comboBoxCountryID.
 */
void ShowCities::getCountryIDs()
{
    try
    {
        QList<QString> list;
        list = p->fillList("SELECT landid FROM land ORDER BY landid ASC");
        for(int i=0; i < list.count(); i++)
        {
            ui->comboBoxCountryID->addItem(QString::number(i+1));
            countries++;
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

/**
 * @brief ShowCities::getCities Builds a list to be used in the combobox of city IDs based on registered cities in the database.
 */
void ShowCities::getCities()
{
    try
    {
        QList<QString> list = p->fillList("SELECT stedsnavn FROM sted ORDER BY stedsnavn ASC");
        int i = 0;
        if(list.count() == 0)
        {
            QMessageBox msg;
            msg.setWindowTitle(windowTitle());
            msg.setIcon(msg.Warning);
            msg.setText("Du har ikke lagt inn noen steder ennå.");
            msg.exec();
            this->close();
        }
        else
        {
            QList<QString>::iterator iter = list.begin();
            while(iter != list.end())
            {
                ui->comboBoxCityID->addItem(list.value(i));
                iter++;
                i++;
            }
            lastID = i;
            cities = i;
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

bool ShowCities::isChanged()
{
    return changed;
}

void ShowCities::setChanged(bool change)
{
    ui->btnSave->setEnabled(change);
    changed = change;
}

/**
 * @brief ShowCities::getCityName Gets the name of the current city
 * @return The name of the city
 */
QString ShowCities::getCityName()
{
    return cityName;
}

void ShowCities::checkChanges()
{
    if(isChanged() && !buildingList)
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
            if(p->updateCity(oldCityName,getCityName(),getCountryID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(winTitle);
                msg2.setText("Stedet ble oppdatert og har følgende verdier:\nStedsnavn: " + getCityName() + "\nLandID: " + QString::number(getCountryID()));
                msg2.exec();
                buildComboboxCityList();
            }
            else
            {
                QMessageBox msg;
                msg.setIcon(msg.Warning);
                msg.setWindowTitle(winTitle);
                msg.setText("Noe har gått galt: " + p->getError());
                msg.exec();
            }
        }
        setChanged(false);
    }
}

void ShowCities::buttonDeleteClicked()
{
    QMessageBox confirm;
    confirm.setWindowTitle(winTitle);
    confirm.setIcon(confirm.Question);
    confirm.setStandardButtons(confirm.Yes);
    confirm.addButton(confirm.No);
    confirm.setDefaultButton(confirm.Yes);
    confirm.setText("Du er i ferd med å fjerne " + getCityName() + " fra databasen. Dette kan ikke angres. Vil du fortsette?");
    if(confirm.exec() == QMessageBox::Yes)
    {
        if(p->deleteCity(getCityID()))
        {
            QMessageBox success;
            success.setWindowTitle(winTitle);
            success.setIcon(success.Information);
            success.setText("Byen " + getCityName() + " ble fjernet fra databasen.");
            success.exec();
            ui->comboBoxCityID->removeItem(ui->comboBoxCityID->currentIndex());
            setCityID(ui->comboBoxCityID->currentText().toInt());
            lastID = lastID -1;
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

void ShowCities::buildComboboxCityList()
{
    buildingList = true;
    if(ui->comboBoxCityID->count() >=1)
    {
        for(int i = ui->comboBoxCityID->count(); i >= 0; i--){
            ui->comboBoxCityID->removeItem(i);
        }
    }
    getCities();
    buildingList = false;
}

void ShowCities::buttonSaveClicked()
{
    if(p->updateCity(ui->comboBoxCityID->currentText(), getCityName(), getCountryID()))
    {
        QMessageBox success;
        success.setWindowTitle(winTitle);
        success.setIcon(success.Information);
        success.setText("Stedet ble oppdatert og har følgende verdier:\nStedsnavn: " + getCityName() + "\nLandID: " + QString::number(getCountryID()));
        success.exec();
        setChanged(false);
        /*ui->comboBoxCityID->removeItem(ui->comboBoxCityID->currentIndex()-1);
        ui->comboBoxCityID->addItem(ui->lineEditCityName->text());*/
        buildComboboxCityList();
    }
    else
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText("Noe har gått galt: " + p->getError());
        msg.exec();
    }
}

bool ShowCities::canSave()
{
    bool res = true;
    if(stringCheck::isNullOrWhitespace(ui->lineEditCityName->text()))
        res = false;
    return res;
}

void ShowCities::lineEditCityNameChanged()
{
    try
    {
        setCityName(ui->lineEditCityName->text());
        if(!cityIDchanged)
            setChanged(canSave());
    }
    catch(invalid_argument)
    {
        setChanged(false);
    }
}

void ShowCities::comboboxCityIDChanged()
{
    int currID = p->getCityID(ui->comboBoxCityID->currentText().toStdString());
    checkChanges();
    cityIDchanged = true;
    getCity(currID);
    cityIDchanged = false;
}

void ShowCities::comboboxCountryIDChanged()
{
    try
    {
        setCountryID(ui->comboBoxCountryID->currentText().toInt());
        ui->labelCountryName->setText(p->getCountryName(getCountryID()));
        if(!cityIDchanged)
            setChanged(canSave());
    }
    catch(invalid_argument)
    {
        setChanged(false);
    }
}
void ShowCities::windowLoaded()
{
    try{
        getCities();
        getCountryIDs();
        ui->labelCountryName->setText(p->getCountryName(ui->comboBoxCountryID->currentText().toInt()));
        int countryID = ui->comboBoxCountryID->currentText().toInt();
        setCountryID(countryID);
        runs++;
        setChanged(false);
        cityIDchanged = false;
    }
    catch(QException qe)
    {
        QMessageBox qm;
        qm.setIcon(qm.Warning);
        qm.setText(qe.what());
        qm.setWindowTitle(winTitle);
        qm.exec();
    }
}

void ShowCities::showEvent(QShowEvent *)
{
    QTimer::singleShot(50, this, SLOT(windowLoaded()));
}
void ShowCities::closeEvent(QCloseEvent *event)
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
            if(p->updateCity(ui->comboBoxCityID->currentText(),getCityName(),getCountryID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(winTitle);
                msg2.setText("Stedet ble oppdatert og har følgende verdier:\nStedsnavn: " + getCityName() + "\nLandID: " + QString::number(getCountryID()));
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

ShowCities::~ShowCities()
{
    delete ui;
}
