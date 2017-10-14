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

#include "mainwindow.h"
#include <QApplication>
#include <QCloseEvent>
#include "ui_mainwindow.h"
#include "newjob.h"
#include "viewjobs.h"
#include "newcity.h"
#include "newcountry.h"
#include "newstatus.h"
#include "showcities.h"
#include "showcountries.h"
#include "showstatuses.h"
#include "psql.h"
#include <pqxx/pqxx>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    progName = "Jobber";
    setFixedSize(size());
    setWindowFlags(( (this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint));
    connect(ui->btn_newJob, SIGNAL(clicked()), this, SLOT(btn_newJob_Click()));
    connect(ui->btn_ShowJobs, SIGNAL(clicked()), this, SLOT(btn_showJobs_Click()));
    connect(ui->btn_NewCity, SIGNAL(clicked(bool)), this, SLOT(btn_NewCity_Click()));
    connect(ui->btn_NewCountry, SIGNAL(clicked(bool)), this, SLOT(btn_NewCountry_Click()));
    connect(ui->btn_NewStatus, SIGNAL(clicked(bool)), this, SLOT(btn_NewStatus_Click()));
    connect(ui->btn_ShowCities, SIGNAL(clicked(bool)), this, SLOT(btn_ShowCities_Click()));
    connect(ui->btn_showCountries, SIGNAL(clicked(bool)), this, SLOT(btn_ShowCountries_Click()));
    connect(ui->btn_ShowStatuses, SIGNAL(clicked(bool)), this, SLOT(btn_ShowStatuses_Click()));
    cp = new connectPsql(progName);
    p = cp->p; // Kanskje ikke verdens smarteste idé, men lar den likevel peke på psql-objektet i klassen "connectpsql" inntil videre.
    cp->exec();
    if(cp->result() == cp->Rejected)
    {
        exit(1);
    }
}

void MainWindow::btn_NewCountry_Click()
{
    NewCountry *ncty = new NewCountry(progName, p, this);
    ncty->show();
}

void MainWindow::btn_ShowCountries_Click()
{
    ShowCountries *scty = new ShowCountries(progName,p, this);
    scty->show();
}

void MainWindow::btn_NewStatus_Click()
{
    NewStatus *ns = new NewStatus(progName,p, this);
    ns->show();
}

void MainWindow::btn_ShowCities_Click()
{
    ShowCities *sc = new ShowCities(progName, p, this);
    sc->show();
}

void MainWindow::btn_ShowStatuses_Click()
{
    ShowStatuses *ss = new ShowStatuses(progName, p, this);
    ss->show();
}

void MainWindow::btn_NewCity_Click()
{
    NewCity *nc = new NewCity(progName, p, this);
    nc->show();
}

void MainWindow::btn_showJobs_Click()
{
    ViewJobs *vj = new ViewJobs(progName, p, this);
    vj->show();
}


void MainWindow::btn_newJob_Click()
{
    /*
     * Åpner opp et nytt vindu som inneholder et skjema brukeren fyller ut
     * hvor man legger inn detaljer om den nye jobben.
    */
    NewJob *nj = new NewJob(progName, p, this);
    nj->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


