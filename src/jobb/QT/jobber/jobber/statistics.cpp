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

#include "statistics.h"
#include "ui_statistics.h"

/**
 * @brief statistics::statistics statisitcs class constructor.
 * @param pg The pointer to the psql class
 * @param parent Pointer the the parent class
 */
statistics::statistics(psql *pg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics)
{
    p = pg;
    ui->setupUi(this);
    updateData();
    connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(btnUpdateClicked()));
}

/**
 * @brief statistics::updateData Fetches new application statistics from the database.
 */
void statistics::updateData()
{
    ui->labelTotalValue->setText(QString::number(p->countTotalApplications()));
    ui->labelAcceptedValue->setText(QString::number(p->countAccepted()));
    ui->labelDeclinedValue->setText(QString::number(p->countDeclinedApplications()));
    ui->labelInterviewValue->setText(QString::number(p->countInterviews()));
    ui->labelRegisteredValue->setText(QString::number(p->countRegisteredApplications()));
    ui->labelSentValue->setText(QString::number(p->countSentApplications()));
    ui->labelWrittenButNotSentValue->setText(QString::number(p->countWrittenButNotSent()));
    double percent = ((p->countAccepted() + p->countDeclinedAfterInterview() + p->countDeclinedApplications() + p->countInterviews())/p->countTotalApplications())*100;
    ui->labelAnsweredValue->setText(QString::number(p->countAccepted() + p->countDeclinedAfterInterview() + p->countDeclinedApplications() + p->countInterviews()) + " (" + QString::number(percent) + " %)");
    ui->labelDeclinedAfterInterviewValue->setText(QString::number(p->countDeclinedAfterInterview()));
}

void statistics::btnUpdateClicked()
{
    updateData();
}

statistics::~statistics()
{
    delete ui;
}
