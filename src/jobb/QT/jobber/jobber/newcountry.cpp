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

#include "newcountry.h"
#include "ui_newcountry.h"
#include <QPushButton>

/**
 * @brief NewCountry::NewCountry NewCountry class constructor
 * @param windowTitle The title to be used with message boxes (QMessageBox)
 * @param pg A pointer to the PostgreSQL database class
 * @param parent
 */
NewCountry::NewCountry(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewCountry)
{
    ui->setupUi(this);
    setFixedHeight(height());
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    winTitle = windowTitle;
    p = pg;
    close = false;
    changed = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Lagre");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()),this, SLOT(OKButtonClicked()), Qt::UniqueConnection);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->lineEditCountryName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCountryNameChanged()));
}

// Offentlige metoder som henter verdier:
/**
 * @brief NewCountry::getCountry Gets the current country name.
 * @return The name of the country
 */
QString NewCountry::getCountry()
{
    return country;
}

// Offentlige metoder som setter verdier
/**
 * @brief NewCountry::setCountry Sets the name of the country
 * @param newCountry The new name of the country
 */
void NewCountry::setCountry(QString newCountry)
{
    if(stringCheck::isNullOrWhitespace(newCountry))
    {
        throw invalid_argument("Landnavnet kan ikke være null eller bare bestå av mellomrom.");
    }
    country = newCountry;
}

// Andre offentlite metoder
NewCountry::~NewCountry()
{
    delete ui;
}

// Private metoder
/**
 * @brief NewCountry::canSave Checks if the unsaved changes can be saved or not.
 * @return True if the changes can be saved (getCountry length is >= 1) and false otherwise.
 */
bool NewCountry::canSave()
{
    bool res = true;
    if(stringCheck::isNullOrWhitespace(ui->lineEditCountryName->text()))
        res = false;
    return res;
}

/**
 * @brief NewCountry::closeEvent Code to be executed when the window closes
 * @param event This pointer points to the QCloseEvent class that contains functions to prvent the window from closing.
 */
void NewCountry::closeEvent(QCloseEvent *event)
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
                if(p->insertCountry(getCountry()))
                {
                    // Lukker vinduet.
                    QMessageBox msg;
                    msg.setWindowTitle(winTitle);
                    msg.setIcon(msg.Information);
                    msg.setText("Det nye landet ble lagret med følgende verdier:\nLandnavn: " + getCountry());
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
            if(p->insertCountry(getCountry()))
            {
                // Lukker vinduet.
                QMessageBox msg;
                msg.setWindowTitle(winTitle);
                msg.setIcon(msg.Information);
                msg.setText("Det nye landet ble lagret med følgende verdier:\nLandnavn: " + getCountry());
                msg.exec();
                event->accept();
            }
        }
    }
}

// Metoder definert under "private slots":
void NewCountry::lineEditCountryNameChanged()
{
    try
    {
        setCountry(ui->lineEditCountryName->text());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
    catch(invalid_argument &ia)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        fprintf(stderr, "%s\n", ia.what());
        changed = canSave();
    }
}

void NewCountry::OKButtonClicked()
{
    if(canSave())
    {
        if(p->insertCountry(getCountry()))
        {
            // Lukker vinduet.
            QMessageBox msg;
            msg.setWindowTitle(winTitle);
            msg.setIcon(msg.Information);
            msg.setText("Det nye landet ble lagret med følgende verdier:\nLandnavn: " + getCountry());
            msg.exec();
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
