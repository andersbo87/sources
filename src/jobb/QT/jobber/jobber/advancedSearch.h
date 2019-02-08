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

#ifndef SPESICFICJOBS_H
#define SPESICFICJOBS_H
#include "psql.h"
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class SpesicficJobs;
}

class advancedSearch : public QMainWindow
{
    Q_OBJECT

public:
    explicit advancedSearch(QString title, psql *pg, QWidget *parent = 0);
    ~advancedSearch();
    // "Getters":
    QString getJobTitle();
    QString getCompanyName();
    QString getCityName();
    QString getStatus();
    QString getDeadline();
    QString getMotivation();

    // "Setters":
    void setJobTitle(QString newTitle);
    void setCompanyName(QString newName);
    void setCityName(QString newCityName);
    void setStatus(QString newStatus);
    void setDeadline(QString newDeadline);
    void setMotivation(QString newMotivation);

    // Offentlige metoder som henter ulike datastrukturer:
    void getCityNames();
    void getStatuses();

private:
    Ui::SpesicficJobs *ui;
    QString winTitle, jobTitle, companyName, cityName, status, deadline, motivation;
    psql *p;
    QStandardItemModel *model;
    void appendApplicationIDs();
    void appendJobTitles();
    void appendCompanyNames();
    void appendCityNames();
    void appendStatuses();
    void appendDeadlines();
    void appendMotivations();

private slots:
    void btnSearchClicked();
    void comboBoxCityNameChanged();
    void comboBoxStatusChanged();
    void lineEditJobTitleChanged();
    void lineEditCompanyNameChanged();
    void lineEditDeadlineChanged();

};

#endif // SPESICFICJOBS_H
