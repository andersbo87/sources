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

#include "viewjobs.h"
#include "ui_viewjobs.h"

/**
 * @brief ViewJobs The ViewJobs class constructor
 * @param windowTitle The name to be used as titles in windows and message boxes.
 * @param pg A pointer to the PostgreSQL database class.
 * @param parent
 */
ViewJobs::ViewJobs(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewJobs)
{
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    ui->setupUi(this);
    setFixedSize(size());
    p = pg;
    winTitle = windowTitle;
    connect(ui->comboBoxApplicationID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxApplicationIDChanged()));
    connect(ui->lineEditTitle, SIGNAL(textChanged(QString)), this, SLOT(lineEditTitleChanged()));
    connect(ui->lineEditCompany, SIGNAL(textChanged(QString)), this, SLOT(lineEditCompanyChanged()));
    connect(ui->comboBoxTownID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxCityIDChanged()));
    connect(ui->comboBoxStatusID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxStatusIDChanged()));
    connect(ui->lineEditDeadline, SIGNAL(textChanged(QString)), this, SLOT(lineEditDealineChanged()));
    connect(ui->textEditMotivation, SIGNAL(textChanged()), this, SLOT(motivationTextChanged()), Qt::UniqueConnection);
    connect(ui->btnFirst, SIGNAL(clicked(bool)), this, SLOT(buttonFirstClicked()), Qt::UniqueConnection);
    connect(ui->btnLast, SIGNAL(clicked(bool)), this, SLOT(buttonLastClicked()), Qt::UniqueConnection);
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(buttonNextClicked()), Qt::UniqueConnection);
    connect(ui->btnPrev, SIGNAL(clicked(bool)), this, SLOT(buttonPreviousClicked()), Qt::UniqueConnection);
    connect(ui->btnSave, SIGNAL(clicked(bool)), this, SLOT(buttonSaveClicked()), Qt::UniqueConnection);
    connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(buttonDeleteClicked()), Qt::UniqueConnection);
    //connect(this, SIGNAL(window_loaded), this, SLOT(windowLoaded()), Qt::ConnectionType(Qt::QueuedConnection | Qt::UniqueConnection));
    connect(this, SIGNAL(sigShowEvent()), this, SLOT(windowLoaded()));
}

/*void ViewJobs::showEvent(QShowEvent e)
{
    ViewJobs::showEvent(e);
    emit sigShowEvent();
}*/
ViewJobs::~ViewJobs()
{
    delete ui;
}

/**
 * @brief ViewJobs::isChanged Checks if there have been any unsaved changes to the current record
 * @return True if there are unsaved changes and false otherwise.
 */
bool ViewJobs::isChanged()
{
    return changed;
}

/**
 * @brief ViewJobs::setChanged Sets the changed variable to true if there are unsaved changes, and false if those changes have been saved.
 * @param change true if a record has been changed and false if that record has been saved
 */
void ViewJobs::setChanged(bool change)
{
    ui->btnSave->setEnabled(change);
    changed = change;
}

void ViewJobs::motivationTextChanged()
{
    setMotivation(ui->textEditMotivation->toPlainText());
    if(!soknadIDChanged)
    {
        setChanged(canSave());
    }
    else
    {
        setChanged(false);
    }
}

void ViewJobs::comboBoxStatusIDChanged()
{
    try
    {
        setStatusID(p->getStatusID(ui->comboBoxStatusID->currentText().toStdString()));
        if(!soknadIDChanged)
            setChanged(canSave());
    }
    catch(invalid_argument ia)
    {
        // La oss skrive feilen ut til konsollen.
        qDebug("En feil har oppstått: %s\n", ia.what());
        setChanged(false);
    }
}

void ViewJobs::comboBoxCityIDChanged()
{
    try
    {
        setCityID(p->getCityID(ui->comboBoxTownID->currentText().toStdString()));
        if(!soknadIDChanged)
            setChanged(canSave());
    }
    catch(invalid_argument ia)
    {
        // La oss bare ignorere feilen og evt sette changed til false. Brukeren kan ikke gjøre noe feil uansett...
        qDebug("En feil har oppstått: %s\n", ia.what());
        setChanged(false);
    }
}

void ViewJobs::lineEditDealineChanged()
{
    try
    {
        setDate(ui->lineEditDeadline->text());
        if(!soknadIDChanged)
            setChanged(canSave());
    }
    catch(invalid_argument)
    {
        setChanged(false);
    }
}

void ViewJobs::lineEditCompanyChanged()
{
    try
    {
        setCompany(ui->lineEditCompany->text());
        if(!soknadIDChanged)
            setChanged(canSave());
    }
    catch(invalid_argument)
    {
        setChanged(false);
    }
}

void ViewJobs::lineEditTitleChanged()
{
    try
    {
        setTitle(ui->lineEditTitle->text());
        if(!soknadIDChanged)
            setChanged(canSave());
    }
    catch(invalid_argument)
    {
        setChanged(false);
    }
}

bool ViewJobs::canSave()
{
    bool res = true;
    if(stringCheck::isNullOrWhitespace(ui->lineEditTitle->text()))
        res = false;
    if(stringCheck::isNullOrWhitespace(ui->lineEditCompany->text()))
        res = false;
    if(stringCheck::isNullOrWhitespace(ui->lineEditDeadline->text()))
        res = false;
    return res;
}

/**
 * @brief ViewJobs::windowLoaded Code to be executed after the window has been loaded.
 */
void ViewJobs::windowLoaded()
{
    setChanged(false);
    getApplications();
    getCityIDs();
    getStatusIDs();
    getApplication(1);
    setChanged(false); // Just to be sure the systems doesn't think we've made any changes.
    soknadIDChanged = false;
}

/**
 * @brief ViewJobs::showEvent Code to be run when the window is shown.
 */
void ViewJobs::showEvent(QShowEvent *)
{
    QTimer::singleShot(50, this, SLOT(windowLoaded()));
}

/**
 * @brief ViewJobs::closeEvent Code to be executed when the user has ordered the window to be closed.
 * @param event No help available, sorry
 */
void ViewJobs::closeEvent(QCloseEvent *event)
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
            if(p->updateApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate(), getMotivation(), getApplicationID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(winTitle);
                msg2.setText("Oppdateringen ble lagret med følgende verdier:\nID: " + QString::number(getApplicationID()) + "\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusid: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate() + "\nMotivasjon: " + getMotivation());
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

void ViewJobs::checkChanges()
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
            if(p->updateApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate(), getMotivation(), getApplicationID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(winTitle);
                msg2.setText("Oppdateringen ble lagret med følgende verdier:\nID: " + QString::number(getApplicationID()) + "\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusid: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate() + "\nMotivasjon: " + getMotivation());
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
        }
        setChanged(false);
    }
}

void ViewJobs::buttonSaveClicked()
{
    if(p->updateApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate(), getMotivation(), getApplicationID()))
    {
        QMessageBox msg2;
        msg2.setIcon(msg2.Information);
        msg2.setWindowTitle(winTitle);
        msg2.setText("Oppdateringen ble lagret med følgende verdier:\nID: " + QString::number(getApplicationID()) + "\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusid: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate() + "\nMotivasjon: " + getMotivation());
        msg2.exec();
        setChanged(false);
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


void ViewJobs::buttonFirstClicked()
{
    try
    {
        checkChanges();
        getApplication(1);
        ui->btnFirst->setEnabled(false);
        ui->btnPrev->setEnabled(false);
        ui->btnNext->setEnabled(true);
        ui->btnLast->setEnabled(true);
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

void ViewJobs::buttonDeleteClicked()
{
    QMessageBox confirm;
    confirm.setWindowTitle(winTitle);
    confirm.setIcon(confirm.Question);
    confirm.setStandardButtons(confirm.Yes);
    confirm.addButton(confirm.No);
    confirm.setDefaultButton(confirm.Yes);
    confirm.setText("Du er i ferd med å slette jobbsøknaden med ID " + QString::number(getApplicationID()) + " fra databasen. Denne handlingen kan ikke angres. Er du sikker på at du vil fortsette?");
    if(confirm.exec() == QMessageBox::Yes)
    {
        if(p->deleteApplication(getApplicationID()))
        {
            QMessageBox success;
            success.setWindowTitle(winTitle);
            success.setIcon(success.Information);
            success.setText("Søknaden med ID " + QString::number(getApplicationID()) + " ble fjernet fra databasen.");
            success.exec();
            ui->comboBoxApplicationID->removeItem(ui->comboBoxApplicationID->currentIndex());
            lastid = lastid-1;
            setApplicationID(ui->comboBoxApplicationID->currentText().toInt());
            if(ui->comboBoxApplicationID->currentText().toInt() == lastid)
            {
                ui->btnNext->setEnabled(false);
                ui->btnLast->setEnabled(false);
                //ui->comboBoxApplicationID->set
            }
            if(getApplicationID() == 1)
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

void ViewJobs::buttonLastClicked()
{
    try
    {
        checkChanges();
        ui->comboBoxApplicationID->setCurrentIndex(ui->comboBoxApplicationID->count()-1);
        getApplication(ui->comboBoxApplicationID->currentText().toInt());
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

void ViewJobs::buttonNextClicked()
{
    try
    {
        checkChanges();
        int currentApplication = getApplicationID(), counter = 1;
        while(QString::compare(p->getCompany(currentApplication + counter), "", Qt::CaseSensitive) == 0)
        {
            counter++;
        }
        getApplication(currentApplication + counter);
        ui->btnFirst->setEnabled(true);
        ui->btnPrev->setEnabled(true);
        if(currentApplication + 1 == lastid)
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

void ViewJobs::buttonPreviousClicked()
{
    try
    {
        checkChanges();
        int currentApplication = getApplicationID(), counter = 1;
        while(QString::compare(p->getCompany(currentApplication - counter), "", Qt::CaseSensitive) == 0)
        {
            counter++;
        }
        getApplication(currentApplication - counter);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        if(currentApplication -1 == 1)
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

void ViewJobs::comboboxApplicationIDChanged()
{
    int id = ui->comboBoxApplicationID->currentText().toInt();
    checkChanges();
    soknadIDChanged = true;
    getApplication(id);
    //setApplicationID(id);
    soknadIDChanged = false;
    if(id == 1)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnPrev->setEnabled(false);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
    }
    else if(ui->comboBoxApplicationID->currentIndex() == ui->comboBoxApplicationID->count()-1)
    {
        ui->btnFirst->setEnabled(true);
        ui->btnPrev->setEnabled(true);
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
    }
    else
    {
        ui->btnFirst->setEnabled(true);
        ui->btnPrev->setEnabled(true);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
    }
}

/**
 * @brief ViewJobs::getCityIDs Fills the comboBoxTownID with all city names that exist in the databse. The city names are sorted in an alphabetic order.
 */
void ViewJobs::getCityIDs()
{
    try
    {
        QList<QString> list;
        list = p->fillList("SELECT stedsnavn FROM sted ORDER BY stedsnavn ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBoxTownID->addItem(list.value(i));
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
 * @brief ViewJobs::getStatusIDs Fills the comboBoxStatusID with all status names that exist in the database. Status names are sorted in an alphabetical order.
 */
void ViewJobs::getStatusIDs()
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
 * @brief ViewJobs::getApplicationID Gets the current application ID.
 * @return The current application ID.
 */
int ViewJobs::getApplicationID()
{
    return applicationid;
}

/**
 * @brief ViewJobs::getTitle Gets the application ID.
 * @return the current title.
 */
QString ViewJobs::getTitle()
{
    return jobTitle;
}

/**
 * @brief ViewJobs::getCompany Gets the current employer company.
 * @return the current company.
 */
QString ViewJobs::getCompany()
{
    return company;
}

/**
 * @brief ViewJobs::getCityID Gets the ID of the city where the job is located.
 * @return the ID of the city where the job is located.
 */
int ViewJobs::getCityID()
{
    return cityid;
}

/**
 * @brief ViewJobs::getStatusID Gets the current status ID of the job application.
 * @return the application's current status ID.
 */
int ViewJobs::getStatusID()
{
    return statusid;
}

/**
 * @brief ViewJobs::getDate Gets the current application's dealine.
 * @return The deadline of the current application.
 */
QString ViewJobs::getDate()
{
    return date;
}

/**
 * @brief ViewJobs::getMotivation Gets the current job motivation
 * @return A string containing what motivated the user to apply for this job.
 */
QString ViewJobs::getMotivation()
{
    return motivation;
}

/**
 * @brief ViewJobs::setMotivation Sets the new job motivation.
 * @param newMotivation A string explaining what motivated the user to apply for this job.
 */
void ViewJobs::setMotivation(QString newMotivation)
{
    motivation = newMotivation;
}

/**
 * @brief ViewJobs::setApplicationID sets a new application ID. Note that this does NOT change the ID of the current application.
 * @param newID the new ID.
 */
void ViewJobs::setApplicationID(int newID)
{
    if(newID > 0)
        applicationid = newID;
    else
        throw invalid_argument("SøknadID må være større enn 0.");
}

/**
 * @brief ViewJobs::setTitle Sets a new job title
 * @param newTitle The new job/position title to be used.
 */
void ViewJobs::setTitle(QString newTitle)
{
    if(stringCheck::isNullOrWhitespace(newTitle))
        throw invalid_argument("Tittelen kan ikke være tom. Tittelen kan heller ikke bare bestå av mellomrom.");
    jobTitle = newTitle;
}

/**
 * @brief ViewJobs::setCompany Sets a new employer company name.
 * @param newCompany the new company name.
 */
void ViewJobs::setCompany(QString newCompany)
{
    if(stringCheck::isNullOrWhitespace(newCompany))
        throw invalid_argument("Bedriftsnavnet kan ikke være tomt og kan heller ikke bare bestå av mellomrom.");
    company = newCompany;
}

/**
 * @brief ViewJobs::setCityID Sets a new city ID
 * @param newTownID the new city ID.
 */
void ViewJobs::setCityID(int newTownID)
{
    if(newTownID > 0)
        cityid = newTownID;
    else
        throw invalid_argument("StedID må ha verdi > 0.");
}

/**
 * @brief ViewJobs::setStatusID Sets a new status ID for the current job.
 * @param newStatusID the ID of the application's updated status.
 */
void ViewJobs::setStatusID(int newStatusID)
{
    if(newStatusID > 0 && newStatusID <= 7)
        statusid = newStatusID;
    else
        throw invalid_argument("StatusID må ha verdi >0 og <7.");
}

/**
 * @brief ViewJobs::setDate Sets a new application deadline for the job application.
 * @param newDate The new deadline for the current job application.
 */
void ViewJobs::setDate(QString newDate)
{
    if(stringCheck::isNullOrWhitespace(newDate))
        throw invalid_argument("Søknadsfristen kan ikke være tom og den kan heller ikke bare bestå av mellomrom. Er det ikke angitt frist, kan du skrive 'Snarest' eller tilsvarende isteden.");
    date = newDate;
}

/**
 * @brief ViewJobs::getApplications Fills the comboBoxApplicationID with all application IDs in the database.
 */
void ViewJobs::getApplications()
{
    try
    {
        QList<QString> list;
        list = p->fillList("SELECT soknadid FROM soknad ORDER BY soknadid ASC");
        int i = 0;
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
            QList<QString>::iterator iter = list.begin();
            while(iter != list.end())
            {
                ui->comboBoxApplicationID->addItem(list.value(i));
                i++;
                iter++;
            }
            lastid = i;
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
 * @brief ViewJobs::getApplication Fills the window with information based on the application ID
 * @param appID the application ID to be used.
 */
void ViewJobs::getApplication(int appID)
{
    try
    {
        ui->comboBoxApplicationID->setCurrentText(QString::number(appID));
        ui->lineEditTitle->setText(p->getTitle(appID));
        ui->lineEditCompany->setText(p->getCompany(appID));
        ui->comboBoxTownID->setCurrentText(p->getCityName(p->getCityID(appID)));
        //ui->comboBoxStatusID->setCurrentText(QString::number(p->getStatusID(appID)));
        ui->comboBoxStatusID->setCurrentText(p->getStatusName(p->getStatusID(appID)));
        ui->lineEditDeadline->setText(p->getDate(appID));
        bool old = ui->textEditMotivation->blockSignals(true);
        ui->textEditMotivation->setText(p->getMotivation(appID));
        ui->textEditMotivation->blockSignals(old);
        setApplicationID(appID);
        setTitle(ui->lineEditTitle->text());
        setCompany(ui->lineEditCompany->text());
        //setCityID(ui->comboBoxTownID->currentText().toInt());
        setCityID(p->getCityID(appID));
        //setStatusID(ui->comboBoxStatusID->currentText().toInt());
        setStatusID(p->getStatusID(appID));
        setDate(ui->lineEditDeadline->text());
        setMotivation(ui->textEditMotivation->toPlainText());
    }
    catch(invalid_argument iaex)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText(iaex.what());
        msg.exec();
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