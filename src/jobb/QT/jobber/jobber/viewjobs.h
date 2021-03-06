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

#ifndef VIEWJOBS_H
#define VIEWJOBS_H

#include <QMainWindow>
#include <QCloseEvent>
#include "psql.h"
#include "stringcheck.h"
#include <QMessageBox>

namespace Ui {
class ViewJobs;
}

/**
 * @brief The ViewJobs class
 */
class ViewJobs : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewJobs(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~ViewJobs();
    void getApplications();
    void getApplication(int appID);
    void setApplicationID(int newID);
    void setTitle(QString newTitle);
    void setCompany(QString newCompany);
    void setCityID(int newTownID);
    void setStatusID(int newStatusID);
    void setDate(QString newDate);
    void setMotivation(QString newMotivation);
    int getApplicationID();
    QString getTitle();
    QString getCompany();
    int getCityID();
    int getStatusID();
    QString getDate();
    void getCityIDs();
    QString getMotivation();
    void getStatusIDs();
    bool isChanged();
    void setChanged(bool change);
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *) override;
signals:
    void sigShowEvent();

private:
    Ui::ViewJobs *ui;
    psql *p;
    QString jobTitle, company, date, winTitle, motivation; // jobTitle: the title of the job. title: The name to be used in messageboxes
    int statusid, cityid, applicationid, lastid, cities, statuses;
    bool changed, soknadIDChanged, dateChanged, motivationChanged, companyChanged, statusChanged, titleChanged, cityChanged;
    void checkChanges();
    bool isNullOrWhitespace(QString string);
    bool canSave();

private slots:
    void comboboxApplicationIDChanged();
    void lineEditTitleChanged();
    void lineEditCompanyChanged();
    void lineEditDealineChanged();
    void comboBoxCityIDChanged();
    void comboBoxStatusIDChanged();
    void motivationTextChanged();
    void buttonFirstClicked();
    void buttonPreviousClicked();
    void buttonNextClicked();
    void buttonLastClicked();
    void buttonSaveClicked();
    void buttonDeleteClicked();
    void windowLoaded();
};

#endif // VIEWJOBS_H
