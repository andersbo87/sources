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

#ifndef NEWJOB_H
#define NEWJOB_H

#include "psql.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class NewJob;
}

/**
 * @brief The NewJob class
 */
class NewJob : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief NewJob The NewJob class constructor
     * @param pg A pointer to the PostgreSQL database.
     * @param parent
     */
    explicit NewJob(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~NewJob();
    void setTitle(QString newTitle);
    void setCompany(QString newCompany);
    void setCityName(QString newCityName);
    void setStatusID(int newStatusID);
    void setDate(QString newDate);
    void setMotivation(QString newMotivation);
    void setCityID(int newID);
    QString getTitle();
    QString getCompany();
    QString getCityName();
    int getCityID();
    int getStatusID();
    QString getDate();
    QString getMotivation();

    /**
     * @brief closeEvent Code to be executed when the window closes
     * @param event This pointer points to the QCloseEvent class that contains functions to prvent the window from closing.
     */
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::NewJob *ui;
    bool canSave();
    void getCityIDs();
    void getStatusIDs();
    bool changed, close;
    // jobTitle: The name of the job (developer, CEO, etc.). winTitle: The name to be used in message boxes.
    QString jobTitle, winTitle, company, date, motivation, cityname;
    int statusid, cityid;
    psql *p;

private slots:
    void titleTextChanged();
    void companyTextChanged();
    void cityIDchanged();
    void statusIDchanged();
    void dateChanged();
    void motivationTextChanged();
    void OKButtonClicked();
    void CancelButtonClicked();
};

#endif // NEWJOB_H
