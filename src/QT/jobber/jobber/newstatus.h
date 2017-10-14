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

#ifndef NEWSTATUS_H
#define NEWSTATUS_H
#include <QCloseEvent>
#include "psql.h"
#include <QMainWindow>

namespace Ui {
class NewStatus;
}

/**
 * @brief The NewStatus class
 */
class NewStatus : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewStatus(QString windowTitle, psql *pg,QWidget *parent = 0);
    ~NewStatus();
    void setStatus(QString newStatus);
    QString getStatus();

private:
    Ui::NewStatus *ui;
    void closeEvent(QCloseEvent *event) override;
    psql *p;
    bool changed, close;
    QString status, winTitle; //winTitle: Tittelen på meldingsboksene
    bool canSave();

private slots:
    void OKButtonClicked();
    void lineEditStatusNameChanged();
};

#endif // NEWSTATUS_H
