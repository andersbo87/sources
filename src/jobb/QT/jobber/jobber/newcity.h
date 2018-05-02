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

#ifndef NEWCITY_H
#define NEWCITY_H
#include "psql.h"
#include "stringcheck.h"
#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class NewCity;
}

/**
 * @brief The NewCity class
 */
class NewCity : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewCity(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~NewCity();
    void setCountryID(int newCountryID);
    int getCountryID();
    void setCityName(QString name);
    QString getCityName();


private:
    Ui::NewCity *ui;
    psql *p;
    void closeEvent(QCloseEvent *event) override;
    void getCountryIDs();
    bool canSave();
    int countryID;
    QString cityName, winTitle;
    bool changed, close;


private slots:
    void OKButtonClicked();
    void countryIDchanged();
    void lineEditCityNameChanged();
};

#endif // NEWCITY_H
