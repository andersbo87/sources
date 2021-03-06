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
/**
 * @brief NewJob The NewJob class constructor
 * @param windowTitle The title to be used in message boxes and other things.
 * @param pg A pointer to the PostgreSQL database.
 * @param parent
 */
NewJob::NewJob(QString windowTitle, psql *pg, QWidget *parent) : QMainWindow(parent), ui(new Ui::NewJob)
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
    connect(ui->comboBoxSted, SIGNAL(currentTextChanged(QString)), this, SLOT(cityIDchanged()));
    connect(ui->comboBoxStatusID, SIGNAL(currentIndexChanged(int)), this, SLOT(statusIDchanged()));
    connect(ui->lineEditSoknadsfrist, SIGNAL(textChanged(QString)), this, SLOT(dateChanged()));
    connect(ui->textEditMotivation, SIGNAL(textChanged()), this, SLOT(motivationTextChanged()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(OKButtonClicked()), Qt::UniqueConnection);
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    getStatusIDs();
    ui->comboBoxStatusID->setCurrentText(p->getStatusName(1));
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
        if(p->insertApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate(), getMotivation()))
        {
            // Lukker vinduet.
            QMessageBox msg;
            msg.setWindowTitle(winTitle);
            msg.setIcon(msg.Information);
            msg.setText("Den nye søknaden ble lagt inn med følgende data:\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusID: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate() + "\nMotivasjon: " + getMotivation());
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
        QList<QString> list;
        list = p->fillList("SELECT stedsnavn FROM sted ORDER BY stedsnavn ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBoxSted->addItem(list.value(i));
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
        QList<QString> list;
        list = p->fillList("SELECT status FROM status ORDER BY status ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBoxStatusID->addItem(list.value(i));
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
    try
    {
        setTitle(ui->lineEditTittel->text());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
    catch(invalid_argument &iaex)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
}

void NewJob::motivationTextChanged()
{
    try
    {
        setMotivation(ui->textEditMotivation->toPlainText());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
    catch(invalid_argument &iaex)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
}

/**
 * @brief Executes when the contents of the text box lineEditCompany is changed.
 */
void NewJob::companyTextChanged()
{
    try
    {
        setCompany(ui->lineEditBedrift->text());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
    catch(invalid_argument &iaex)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
}

/**
 * @brief Executes when the selected item of the combobox comboBoxSted is changed.
 */
void NewJob::cityIDchanged()
{
    setCityID(p->getCityID(ui->comboBoxSted->currentText().toStdString()));
    changed = canSave();
}

/**
 * @brief Executes when the selected item of the combobox comboBoxStatusID is changed.
 */
void NewJob::statusIDchanged()
{
    setStatusID(p->getStatusID(ui->comboBoxStatusID->currentText().toStdString()));
    changed = canSave();
}

/**
 * @brief Executes when the contents of the text box lineEditDate is changed.
 */
void NewJob::dateChanged()
{
    try
    {
        setDate(ui->lineEditSoknadsfrist->text());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
    catch(invalid_argument &iaex)
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canSave());
        changed = canSave();
    }
}

/**
 * @brief Checks if all textboxes contains at least one character.
 * @return True if all textboxes has at least one character, and false otherwise.
 */
bool NewJob::canSave()
{
    bool res = true;
    if(stringCheck::isNullOrWhitespace(ui->lineEditTittel->text()))
        res = false;
    if(stringCheck::isNullOrWhitespace(ui->lineEditBedrift->text()))
        res = false;
    if(stringCheck::isNullOrWhitespace(ui->lineEditSoknadsfrist->text()))
        res = false;
    return res;
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
                if(p->insertApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate(), getMotivation()))
                {
                    // Lukker vinduet.
                    QMessageBox msg;
                    msg.setWindowTitle(winTitle);
                    msg.setIcon(msg.Information);
                    msg.setText("Den nye søknaden ble lagt inn med følgende data:\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusID: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate() + "\nMotivasjon: " + getMotivation());
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
            if(p->insertApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate(), getMotivation()))
            {
                // Lukker vinduet.
                QMessageBox msg;
                msg.setWindowTitle(winTitle);
                msg.setIcon(msg.Information);
                msg.setText("Den nye søknaden ble lagt inn med følgende data:\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusID: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate() + "\nMotivasjon: " + getMotivation());
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
    if(stringCheck::isNullOrWhitespace(newTitle))
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        throw invalid_argument("Du må angi en jobbtittel. Denne tittelen kan ikke bestå av bare mellomrom.");
    }
    jobTitle = newTitle;
}

/**
 * @brief NewJob::setCompany: Sets a new job company
 * @param newCompany: The new job company
 */
void NewJob::setCompany(QString newCompany)
{
    if(stringCheck::isNullOrWhitespace(newCompany)){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        throw invalid_argument("Vennligst angi hva bedriften heter.");
    }
    company = newCompany;
}

/**
 * @brief NewJob::getCityID Gets the ID of the city where the job is located.
 * @return The ID of the city where the job is located.
 */
int NewJob::getCityID()
{
    return cityid;
}

/**
 * @brief NewJob::setCityID Sets the ID of the existing city where the job is located.
 * @param newID The ID of the city where the job is located.
 */
void NewJob::setCityID(int newID)
{
    cityid = newID;
}

/**
 * @brief NewJob::setCityName: Sets the name of the city in which the job is located.
 * @param newCityName: the name of the city in which the job is located.
 */
void NewJob::setCityName(QString newCityName)
{
    if(stringCheck::isNullOrWhitespace(newCityName))
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        throw invalid_argument("Stedsnavnet kan ikke være tomt. Det kan heller ikke bare bestå av mellomrom.");
    }
    cityname = newCityName;
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
    if(stringCheck::isNullOrWhitespace(newDate))
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        throw invalid_argument("Du må angi en søknadsfrist. Den kan heller ikke bare bestå av mellomrom. Er det ikke oppgitt en frist, kan du bruke uttrykk som 'snarest' isteden.");
    }
    date = newDate;
}

/**
 * @brief NewJob::setMotivation Sets the motivation for the current job
 * @param newMotivation A string containing information about what motivated the user to apply for this job.
 */
void NewJob::setMotivation(QString newMotivation)
{
    motivation = newMotivation; // Dette feltet er frivillig og kommer derfor ikke til å ha noen gyldighetstest.
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
QString NewJob::getCityName()
{
    return cityname;
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

/**
 * @brief NewJob::getMotivation Gets the job's current motivations (what motivated the user to apply for this job?)
 * @return
 */
QString NewJob::getMotivation()
{
    return motivation;
}
