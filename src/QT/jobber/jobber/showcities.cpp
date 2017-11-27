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

ShowCities::ShowCities(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowCities)
{
    winTitle = windowTitle;
    p = pg;
    ui->setupUi(this);
    setFixedHeight(height());
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    connect(ui->btnFirst, SIGNAL(clicked(bool)), this, SLOT(buttonFirstClicked()), Qt::UniqueConnection);
    connect(ui->btnLast, SIGNAL(clicked(bool)), this, SLOT(buttonLastClicked()), Qt::UniqueConnection);
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(buttonNextClicked()), Qt::UniqueConnection);
    connect(ui->btnPrev, SIGNAL(clicked(bool)), this, SLOT(buttonPreviousClicked()), Qt::UniqueConnection);
    connect(ui->comboBoxCityID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxCityIDChanged()), Qt::UniqueConnection);
    connect(ui->comboBoxCountryID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxCountryIDChanged()), Qt::UniqueConnection);
    connect(ui->lineEditCityName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCityNameChanged()), Qt::UniqueConnection);
    connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(buttonDeleteClicked()), Qt::UniqueConnection);
    connect(ui->btnSave, SIGNAL(clicked(bool)), this, SLOT(buttonSaveClicked()), Qt::UniqueConnection);
    getCities();
    getCountryIDs();
    getCity(1);
    cityIDchanged = false;
    changed = false;
}

int ShowCities::getCityID()
{
    return cityID;
}

QString ShowCities::getCountryName()
{
    return countryName;
}

int ShowCities::getCountryID()
{
    return countryID;
}

// Metoder som angir nye verdier:
void ShowCities::setCityID(int newID)
{
    cityID = newID;
}

void ShowCities::setCityName(QString newName)
{
    cityName = newName;
}

void ShowCities::setCountryID(int newID)
{
    countryID = newID;
}

void ShowCities::getCity(int cityID)
{
    try
    {
        ui->comboBoxCityID->setCurrentText(QString::number(cityID));
        ui->lineEditCityName->setText(p->getCityName(cityID));
        ui->comboBoxCountryID->setCurrentText(QString::number(p->getCountryID(cityID)));
        setCityID(cityID);
        setCountryID(ui->comboBoxCountryID->currentText().toInt());
        setCityName(ui->lineEditCityName->text());
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

void ShowCities::getCountryIDs()
{
    try
    {
        QList<int> list;
        list = p->fillList("SELECT landid FROM land ORDER BY landid ASC");
        for(int i=0; i < list.count(); i++)
        {
            ui->comboBoxCountryID->addItem(QString::number(i+1));
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

void ShowCities::getCities()
{
    try
    {
        QList<int> list = p->fillList("SELECT stedid FROM sted ORDER BY stedid ASC");
        int i = 0;
        for(QList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
        {
            ui->comboBoxCityID->addItem(QString::number(list.value(i)));
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

bool ShowCities::isChanged()
{
    return changed;
}

void ShowCities::setChanged(bool change)
{
    changed = change;
}

QString ShowCities::getCityName()
{
    return cityName;
}

void ShowCities::checkChanges()
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
            if(p->updateCity(getCityName(),getCountryID(),getCityID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(winTitle);
                msg2.setText("Stedet ble oppdatert og har følgende verdier:\nStedid: " + QString::number(getCityID()) + "\nStedsnavn: " + getCityName() + "\nLandID: " + QString::number(getCountryID()));
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
            if(ui->comboBoxCityID->currentText().toInt() == lastID)
            {
                ui->btnNext->setEnabled(false);
                ui->btnLast->setEnabled(false);
            }
            if(getCityID() == 1)
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

void ShowCities::buttonSaveClicked()
{
    if(p->updateCity(getCityName(), getCountryID(), getCityID()))
    {
        QMessageBox success;
        success.setWindowTitle(winTitle);
        success.setIcon(success.Information);
        success.setText("Stedet ble oppdatert og har følgende verdier:\nStedid: " + QString::number(getCityID()) + "\nStedsnavn: " + getCityName() + "\nLandID: " + QString::number(getCountryID()));
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
}

void ShowCities::buttonFirstClicked()
{
    try
    {
        checkChanges();
        getCity(1);
        ui->btnFirst->setEnabled(false);
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(true);
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

void ShowCities::buttonLastClicked()
{
    try
    {
        checkChanges();
        ui->comboBoxCityID->setCurrentIndex(ui->comboBoxCityID->count() -1);
        getCity(ui->comboBoxCityID->currentText().toInt());
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

void ShowCities::buttonNextClicked()
{
    try
    {
        checkChanges();
        int currentCity = getCityID(), counter = 1;
        while(QString::compare(p->getCityName(currentCity + counter), "", Qt::CaseSensitive) == 0)
        {
            qDebug("Info: Må gå enda lenger. Teller: %d\n", counter);
            counter ++;
        }
        getCity(currentCity + counter);
        ui->btnFirst->setEnabled(true);
        ui->btnPrev->setEnabled(true);
        if(currentCity + 1 == lastID)
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

void ShowCities::buttonPreviousClicked()
{
    try
    {
        checkChanges();
        int currentCity = getCityID(), counter=1;
        while(QString::compare(p->getCityName(currentCity - counter), "", Qt::CaseSensitive) == 0)
        {
            qDebug("Info: Må gå enda lenger. Teller: %d\n", counter);
            counter ++;
        }
        getCity(currentCity -counter);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        if(currentCity - 1 == 1)
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

void ShowCities::lineEditCityNameChanged()
{
    setCityName(ui->lineEditCityName->text());
    if(!cityIDchanged)
        setChanged(true);
}

void ShowCities::comboboxCityIDChanged()
{
    int currID = ui->comboBoxCityID->currentText().toInt();
    checkChanges();
    cityIDchanged = true;
    getCity(currID);
    cityIDchanged = false;
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

void ShowCities::comboboxCountryIDChanged()
{
    setCountryID(ui->comboBoxCountryID->currentText().toInt());
    ui->labelCountryName->setText(p->getCountryName(getCountryID()));
    if(!cityIDchanged)
        setChanged(true);
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
            if(p->updateCity(getCityName(),getCountryID(),getCityID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(winTitle);
                msg2.setText("Stedet ble oppdatert og har følgende verdier:\nStedid: " + QString::number(getCityID()) + "\nStedsnavn: " + getCityName() + "\nLandID: " + QString::number(getCountryID()));
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
