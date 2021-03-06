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

#ifndef SHOWCITIES_H
#define SHOWCITIES_H
#include <QCloseEvent>
#include "psql.h"
#include "stringcheck.h"
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class ShowCities;
}

/**
 * @brief The ShowCities class
 */
class ShowCities : public QMainWindow
{
    Q_OBJECT

public:

    explicit ShowCities(QString title, psql *pg, QWidget *parent = 0);
    ~ShowCities();
    void getCities();
    void getCity(int cityName);
    void setCityID(int newID);
    void setCityName(QString newName);
    void setCountryID(int newID);
    void setCountryName(QString newName);
    int getCityID();
    void getCountryIDs();
    int getCountryID();
    QString getCityName();
    QString getCountryName();

private:
    Ui::ShowCities *ui;
    psql *p;
    QString oldCityName, cityName, countryName, winTitle; // Tittelen som skal brukes i meldingsbokser.
    int cityID, countryID, lastID, runs, countries, cities; // Countries: antall land, cities: antall steder.
    bool changed, cityIDchanged;
    void checkChanges();
    bool isChanged();
    void setChanged(bool change);
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *) override;
    bool isNullOrWhitespace(QString string);
    bool canSave();
    bool buildingList;

private slots:
    void comboboxCityIDChanged();
    void comboboxCountryIDChanged();
    void lineEditCityNameChanged();
    void buttonSaveClicked();
    void buttonDeleteClicked();
    void windowLoaded();
    void buildComboboxCityList();
};

#endif // SHOWCITIES_H
