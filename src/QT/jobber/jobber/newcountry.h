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

#ifndef NEWCOUNTRY_H
#define NEWCOUNTRY_H

#include <QCloseEvent>
#include "psql.h"
#include "stringcheck.h"
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class NewCountry;
}

class NewCountry : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewCountry(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~NewCountry();
    QString getCountry();
    void setCountry(QString newCountry);

private:
    // Private variabler
    bool changed, close;
    psql *p;
    QString country, winTitle;
    Ui::NewCountry *ui;

    // Private metoder
    bool canSave();
    void closeEvent(QCloseEvent *event) override;


private slots:
    void OKButtonClicked();
    void lineEditCountryNameChanged();
};

#endif // NEWCOUNTRY_H
