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

#include "newjob.h"
#include "ui_newjob.h"

// Konstruktør
NewJob::NewJob(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewJob)
{
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    ui->setupUi(this);
    setFixedHeight(height());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Lagre");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    p = pg;
    close = false;
    changed = false;
    winTitle = windowTitle;
    connect(ui->lineEditTittel, SIGNAL(textChanged(QString)), this, SLOT(titleTextChanged()));
    connect(ui->lineEditBedrift, SIGNAL(textChanged(QString)), this, SLOT(companyTextChanged()));
    connect(ui->comboBoxStedID, SIGNAL(currentTextChanged(QString)), this, SLOT(cityIDchanged()));
    connect(ui->comboBoxStatusID, SIGNAL(currentIndexChanged(int)), this, SLOT(statusIDchanged()));
    connect(ui->lineEditSoknadsfrist, SIGNAL(textChanged(QString)), this, SLOT(dateChanged()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(OKButtonClicked()), Qt::UniqueConnection);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    getStatusIDs();
    getCityIDs();
}

// Destruktør
NewJob::~NewJob()
{
    delete ui;
}

void NewJob::OKButtonClicked()
{
    // Setter dataene inn i databasen.
    if(canSave())
    {
        if(p->insertApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate()))
        {
            // Lukker vinduet.
            QMessageBox msg;
            msg.setWindowTitle(winTitle);
            msg.setIcon(msg.Information);
            msg.setText("Den nye søknaden ble lagt inn med følgende data:\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusID: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate());
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

void NewJob::CancelButtonClicked()
{
    // Siden vi ikke skal lagre noe i databasen, lukker vi vinduet selv om det er gjort forandringer.
    //changed = false;
    hide();
}

/**
 * @brief Creates a list of city IDs to be added to a combobox.
 */
void NewJob::getCityIDs()
{
    try
    {
        QList<int> list;// = new QLinkedList<int>();
        list = p->fillList("SELECT stedid FROM sted ORDER BY stedid ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBoxStedID->addItem(QString::number(i+1));
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
 * @brief Creates a list of status IDs to be added to a combobox.
 */
void NewJob::getStatusIDs()
{
    try
    {
        QList<int> list;
        list = p->fillList("SELECT statusid FROM status ORDER BY statusid ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBoxStatusID->addItem(QString::number(i+1));
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
 * @brief Executes when the contents of the text box lineEditTitle is changed.
 */
void NewJob::titleTextChanged()
{
    setTitle(ui->lineEditTittel->text());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
    changed = canSave();
}

/**
 * @brief Executes when the contents of the text box lineEditCompany is changed.
 */
void NewJob::companyTextChanged()
{
    setCompany(ui->lineEditBedrift->text());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
    changed = canSave();
}

/**
 * @brief Executes when the selected item of the combobox comboBoxStedID is changed.
 */
void NewJob::cityIDchanged()
{
    setCityID(ui->comboBoxStedID->currentText().toInt());
    ui->labelCityValue->setText(p->getCityName(getCityID()));
    changed = canSave();
}

/**
 * @brief Executes when the selected item of the combobox comboBoxStatusID is changed.
 */
void NewJob::statusIDchanged()
{
    setStatusID(ui->comboBoxStatusID->currentText().toInt());
    ui->labelStatusValue->setText(p->getStatusName(getStatusID()));
    changed = canSave();
}

/**
 * @brief Executes when the contents of the text box lineEditDate is changed.
 */
void NewJob::dateChanged()
{
    setDate(ui->lineEditSoknadsfrist->text());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
    changed = canSave();
}

/**
 * @brief Checks if all textboxes contains at least one character.
 * @return True if all textboxes has at least one character, and false otherwise.
 */
bool NewJob::canSave()
{
    if(jobTitle.length() == 0)
        close = false;
    else if(company.length() == 0)
        close = false;
    else if(cityid == 0)
        close = false;
    else if(statusid == 0)
        close = false;
    else if(date.length() == 0)
        close = false;
    else
        close = true;
    return close;
}

void NewJob::closeEvent(QCloseEvent *event)
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
                // Setter dataene inn i databasen.
                if(p->insertApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate()))
                {
                    // Lukker vinduet.
                    QMessageBox msg;
                    msg.setWindowTitle(winTitle);
                    msg.setIcon(msg.Information);
                    msg.setText("Den nye søknaden ble lagt inn med følgende data:\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusID: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate());
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
            // Setter dataene inn i databasen.
            if(p->insertApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate()))
            {
                // Lukker vinduet.
                QMessageBox msg;
                msg.setWindowTitle(winTitle);
                msg.setIcon(msg.Information);
                msg.setText("Den nye søknaden ble lagt inn med følgende data:\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusID: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate());
                msg.exec();
                event->accept();
            }
        }
    }
}

/*
 * Metoder som setter nye verdier:
*/
/**
 * @brief NewJob::setTitle: Sets a new job title
 * @param newTitle: The new job title.
 */
void NewJob::setTitle(QString newTitle)
{
    jobTitle = newTitle;
}

/**
 * @brief NewJob::setCompany: Sets a new job company
 * @param newCompany: The new job company
 */
void NewJob::setCompany(QString newCompany)
{
    company = newCompany;
}

/**
 * @brief NewJob::setCityID: Sets the ID of the city in which the job is located.
 * @param newCityID: the ID of the city in which the job is located.
 */
void NewJob::setCityID(int newCityID)
{
    cityid = newCityID;
}

/**
 * @brief NewJob::setStatusID: Sets the status ID of the job application
 * @param newStatusID: The new status ID of the job application
 */
void NewJob::setStatusID(int newStatusID)
{
    statusid = newStatusID;
}

/**
 * @brief NewJob::setDate: Sets the deadline for when the job application has to be sent.
 * @param newDate: The deadline of the new job.
 */
void NewJob::setDate(QString newDate)
{
    date = newDate;
}

/*
 * Metoder som henter gamle verdier:
 */

/**
 * @brief NewJob::getTitle: Gets the position title
 * @return The position title
 */
QString NewJob::getTitle()
{
    return jobTitle;
}

/**
 * @brief NewJob::getCompany: Gets the name of the company
 * @return The name of the company
 */
QString NewJob::getCompany()
{
    return company;
}

/**
 * @brief NewJob::getCityID: Gets the ID of the city where the job is located.
 * @return the ID of the city where the job is located.
 */
int NewJob::getCityID()
{
    return cityid;
}

/**
 * @brief NewJob::getStatusID: Gets the current status ID of the job
 * @return the ID of the job's status
 */
int NewJob::getStatusID()
{
    return statusid;
}

/**
 * @brief NewJob::getDate: Gets the job's current application deadline
 * @return The deadline of the job
 */
QString NewJob::getDate()
{
    return date;
}
