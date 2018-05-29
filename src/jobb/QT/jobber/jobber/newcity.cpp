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

/**
  @file newcity.cpp
  */
#include "newcity.h"
#include "ui_newcity.h"
#include <QPushButton>

/**
 * @brief NewCity The NewCity class constructor
 * @param windowTitle The title to be used in message boxes, etc.
 * @param pg Pointer to the PostgreSQL database
 * @param parent
 */
NewCity::NewCity(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewCity)
{
    winTitle = windowTitle;
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    p = pg;
    close = false;
    changed = false;
    ui->setupUi(this);
    setFixedHeight(height());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Lagre");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(OKButtonClicked()), Qt::UniqueConnection);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->lineEditCityName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCityNameChanged()));
    connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(countryIDchanged()));
    getCountryIDs();
}

// Destruktør
NewCity::~NewCity()
{
    delete ui;
}

void NewCity::getCountryIDs()
{
    try
    {
        QList<QString> list;
        list = p->fillList("SELECT landid FROM land ORDER BY landid ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBox->addItem(QString::number(i+1));
            i++;
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
 * @brief NewCity::setCountryID Sets a new country ID to be used when saving the new city to the database.
 * @param newCountryID The ID of the country.
 */
void NewCity::setCountryID(int newCountryID)
{
    countryID = newCountryID;
}

void NewCity::countryIDchanged()
{
    setCountryID(ui->comboBox->currentText().toInt());
    ui->labelCountryName->setText(p->getCountryName(getCountryID()));
    changed = true;
}

/**
 * @brief NewCity::getCityName Gets the name of the new city
 * @return The name of the city to be saved in the database.
 */
QString NewCity::getCityName()
{
    return cityName;
}

/**
 * @brief NewCity::setCityName Sets the name of the new city.
 * @param name The new city name.
 */
void NewCity::setCityName(QString name)
{
    if(stringCheck::isNullOrWhitespace(name))
    {
        throw invalid_argument("Stedsnavnet kan ikke være tomt eller bare bestå av mellomrom.");
    }
    cityName = name;
}

void NewCity::lineEditCityNameChanged()
{
    try
    {
        setCityName(ui->lineEditCityName->text());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
    catch(invalid_argument)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
}

bool NewCity::canSave()
{
    bool res = true;
    if(stringCheck::isNullOrWhitespace(ui->lineEditCityName->text()))
        res = false;
    return res;
}

void NewCity::OKButtonClicked()
{
    if(canSave())
    {
        // Lagrer dataen i databasen.
        if(p->insertCity(getCityName(), getCountryID()))
        {
            // Lukker vinduet.
            QMessageBox msg;
            msg.setWindowTitle(winTitle);
            msg.setIcon(msg.Information);
            msg.setText("Det nye stedet ble lagt inn med følgende data:\nStedsnavn: " + getCityName() + "\nLandid: " + QString::number((getCountryID())));
            msg.exec();
            changed = false;
            hide();
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
    else
    {
        QMessageBox msg;
        msg.setWindowTitle(winTitle);
        msg.setIcon(msg.Warning);
        msg.setText("Alle felt må fylles ut.");
        msg.exec();
    }
}

/**
 * @brief NewCity::getCountryID Gets the chosen country ID
 * @return The the country ID
 */
int NewCity::getCountryID()
{
    return countryID;
}

void NewCity::closeEvent(QCloseEvent *event)
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
                if(p->insertCity(getCityName(), getCountryID()))
                {
                    // Lukker vinduet.
                    QMessageBox msg;
                    msg.setWindowTitle(winTitle);
                    msg.setIcon(msg.Information);
                    msg.setText("Det nye stedet ble lagt inn med følgende data:\nStedsnavn: " + getCityName() + "\nLandid: " + QString::number((getCountryID())));
                    msg.exec();
                    event->accept();
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
            else if(res == QMessageBox::No)
            {
                event->accept();
            }
        }
        else
        {
            if(p->insertCity(getCityName(), getCountryID()))
            {
                // Lukker vinduet.
                QMessageBox msg;
                msg.setWindowTitle(winTitle);
                msg.setIcon(msg.Information);
                msg.setText("Det nye stedet ble lagt inn med følgende data:\nStedsnavn: " + getCityName() + "\nLandid: " + QString::number((getCountryID())));
                msg.exec();
                event->accept();
            }
        }
    }
}
