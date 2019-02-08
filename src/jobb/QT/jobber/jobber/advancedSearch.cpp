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

#include "advancedSearch.h"
#include "ui_advancedSearch.h"

// Konstruktør og destruktør
/**
 * @brief advancedSearch::advancedSearch advancedSearch class constructor
 * @param title The title to be used in windows and dialog boxes.
 * @param pg Pointer to the psql class
 * @param parent
 */
advancedSearch::advancedSearch(QString title, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpesicficJobs)
{
    ui->setupUi(this);
    winTitle = title;
    p = pg;

    connect(ui->btnSearch, SIGNAL(clicked(bool)), this, SLOT(btnSearchClicked()));
    connect(ui->lineEditJobTitle, SIGNAL(textChanged(QString)), this, SLOT(lineEditJobTitleChanged()));
    connect(ui->lineEditCompanyName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCompanyNameChanged()));
    connect(ui->lineEditDeadline, SIGNAL(textChanged(QString)), this, SLOT(lineEditDeadlineChanged()));
    connect(ui->comboBoxCityName, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxCityNameChanged()));
    connect(ui->comboBoxStatusName, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxStatusChanged()));
    getCityNames();
    getStatuses();
}

advancedSearch::~advancedSearch()
{
    delete ui;
}

// Offentlige metoder:
// "Getters"

/**
 * @brief advancedSearch::getJobTitle Gets the job title
 * @return The job title
 */
QString advancedSearch::getJobTitle()
{
    return jobTitle;
}

/**
 * @brief advancedSearch::getCompanyName Gets the company name
 * @return The name of the company
 */
QString advancedSearch::getCompanyName()
{
    return companyName;
}

/**
 * @brief advancedSearch::getCityName Gets the name of the city where the job is located
 * @return The city name
 */
QString advancedSearch::getCityName()
{
    return cityName;
}

/**
 * @brief advancedSearch::getStatus Gets the status of the job application
 * @return The name of the current application status (sent, declined/rejected, etc)
 */
QString advancedSearch::getStatus()
{
    return status;
}

/**
 * @brief advancedSearch::getDeadline Gets the deadline of the application
 * @return The application deadline
 */
QString advancedSearch::getDeadline()
{
    return deadline;
}

/**
 * @brief advancedSearch::getMotivation Gets the motivation for applying for this job.
 * @return The application motivation
 */
QString advancedSearch::getMotivation()
{
    return motivation;
}

// "Setters" - metoder som angir verdier
/**
 * @brief advancedSearch::setJobTitle Sets the title of the job
 * @param newTitle The name of the job
 */
void advancedSearch::setJobTitle(QString newTitle)
{
    jobTitle = newTitle;
}

/**
 * @brief advancedSearch::setCompanyName Sets the name of the company
 * @param newName The company name
 */
void advancedSearch::setCompanyName(QString newName)
{
    companyName = newName;
}

/**
 * @brief advancedSearch::setCityName Sets the name of the city where the job is located.
 * @param newCityName The name of the city
 */
void advancedSearch::setCityName(QString newCityName)
{
    if(QString::compare(newCityName, "Ingen spesielle steder", Qt::CaseSensitive) == 0)
        return;
    cityName = newCityName;
}

/**
 * @brief advancedSearch::setStatus Set the status of the job application
 * @param newStatus The status of the application.
 */
void advancedSearch::setStatus(QString newStatus)
{
    if(QString::compare(newStatus, "Ingen spesielle statuser", Qt::CaseSensitive) == 0)
        return;
    status = newStatus;
}

/**
 * @brief advancedSearch::setDeadline Sets the deadline of the application
 * @param newDeadline The application dealine (could be a date in any format or 'ASAP' or something)
 */
void advancedSearch::setDeadline(QString newDeadline)
{
    deadline = newDeadline;
}

/**
 * @brief advancedSearch::setMotivation Sets the reasons for applying for this job (optional)
 * @param newMotivation The motivation. Is there something about the job or company that made you apply for that job
 */
void advancedSearch::setMotivation(QString newMotivation)
{
    motivation = newMotivation;
}

// Andre offentlige metoder:
/**
 * @brief advancedSearch::getCityNames Fetches a list of city names to be added to the comboBoxCityName.
 */
void advancedSearch::getCityNames()
{
    ui->comboBoxCityName->addItem("Ingen spesielle steder");
    try
    {
        QList<QString> list = p->getCityNames();
        int i = 0;
        QList<QString>::iterator iter = list.begin();
        while(iter != list.end())
        {
            ui->comboBoxCityName->addItem(list.value(i));
            i++;
            iter++;
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
 * @brief advancedSearch::getStatuses Fetches a list of status names to be added to the comboBoxStatusName
 */
void advancedSearch::getStatuses()
{
    ui->comboBoxStatusName->addItem("Ingen spesielle statuser");
    try
    {
        QList<QString> list = p->getStatuses();
        int i = 0;
        QList<QString>::iterator iter = list.begin();
        while(iter != list.end())
        {
            ui->comboBoxStatusName->addItem(list.value(i));
            i++;
            iter++;
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

void advancedSearch::appendApplicationIDs()
{
    QList<QStandardItem *> list;
    QList<int> res = p->getSpecificApplicationIDs(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<int>::iterator iterInt = res.begin();
    int i = 0;
    while(iterInt != res.end())
    {
        list.append(new QStandardItem(QString::number(res.value(i))));
        i++;
        iterInt++;
    }
    model->appendColumn(list);
}
void advancedSearch::appendJobTitles()
{
    QList<QStandardItem *> list;
    QList<QString> jobTitles = p->getSpecificJobNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<QString>::iterator iter;
    iter = jobTitles.begin();
    int i = 0;
    while(iter != jobTitles.end())
    {
        list.append(new QStandardItem(jobTitles.value(i)));
        i++;
        iter++;
    }
    model->appendColumn(list);
}
void advancedSearch::appendCompanyNames()
{
    QList<QStandardItem *> list;
    QList<QString> companyNames = p->getSpecificCompanyNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = companyNames.begin(); iter != companyNames.end(); iter++)
    {
        list.append(new QStandardItem(companyNames.value(i)));
        i++;
    }
    model->appendColumn(list);
}

void advancedSearch::appendCityNames()
{
    QList<QString> cityNames = p->getSpecificCityNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<QStandardItem *> list;
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = cityNames.begin(); iter != cityNames.end(); iter++)
    {
        list.append(new QStandardItem(cityNames.value(i)));
        i++;
    }
    model->appendColumn(list);
}

void advancedSearch::appendStatuses()
{
    QList<QStandardItem *> list;
    QList<QString> statuses = p->getSpecificStatuses(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = statuses.begin(); iter != statuses.end(); iter++)
    {
        list.append(new QStandardItem(statuses.value(i)));
        i++;
    }
    model->appendColumn(list);
}

void advancedSearch::appendDeadlines()
{
    QList<QStandardItem *> list;
    QList<QString> deadlines = p->getSpecificDeadlines(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = deadlines.begin(); iter != deadlines.end(); iter++)
    {
        list.append(new QStandardItem(deadlines.value(i)));
        i++;
    }
    model->appendColumn(list);
}

void advancedSearch::appendMotivations()
{
    QList<QStandardItem *> list;
    QList<QString> motivations = p->getSpecificMotivations(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = motivations.begin(); iter != motivations.end(); iter++)
    {
        list.append(new QStandardItem(motivations.value(i)));
        i++;
    }
    model->appendColumn(list);
}

// Metoder som er plassert under private slots:
void advancedSearch::btnSearchClicked()
{
    model = new QStandardItemModel(this);
    appendApplicationIDs();
    appendJobTitles();
    appendCompanyNames();
    appendCityNames();
    appendStatuses();
    appendDeadlines();
    appendMotivations();
    ui->tableViewResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList h;
    h << "ID" << "Tittel" << "Bedrift" << "Stedsnavn" << "Status" << "Søknadsfrist" << "Motivasjon";
    model->setHorizontalHeaderLabels(h);
    ui->tableViewResults->setModel(model);
    if(model->rowCount() == 0){
        QMessageBox msg;
        msg.setWindowTitle(winTitle);
        msg.setIcon(msg.Information);
        msg.setText("Søket returnerte ingen treff.");
        msg.exec();
    }
}

void advancedSearch::lineEditJobTitleChanged()
{
    setJobTitle(ui->lineEditJobTitle->text());
}

void advancedSearch::lineEditCompanyNameChanged()
{
    setCompanyName(ui->lineEditCompanyName->text());
}

void advancedSearch::lineEditDeadlineChanged()
{
    setDeadline(ui->lineEditDeadline->text());
}

void advancedSearch::comboBoxCityNameChanged()
{
    setCityName(ui->comboBoxCityName->currentText());
}

void advancedSearch::comboBoxStatusChanged()
{
    setStatus(ui->comboBoxStatusName->currentText());
}
