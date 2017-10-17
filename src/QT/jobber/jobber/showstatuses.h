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

#ifndef SHOWSTATUSES_H
#define SHOWSTATUSES_H
#include <QCloseEvent>
#include "psql.h"
#include <QMainWindow>

namespace Ui {
class ShowStatuses;
}

/**
 * @brief The ShowStatuses class
 */
class ShowStatuses : public QMainWindow
{
    Q_OBJECT

public:
    // Konstruktør og destruktør
    /**
     * @brief ShowStatuses The ShowStatuses class constructor
     * @param windowTitle The title to be used with message boxes (QMessageBox)
     * @param pg A pointer to the PostgreSQL database.
     * @param parent
     */
    explicit ShowStatuses(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~ShowStatuses();

    // Offentlige metoder
    void getStatus(int statusID);
    void getStatuses();
    /**
     * @brief getStatusID Gets the ID of the current status
     * @return The status identification number
     */
    int getStatusID();
    QString getStatusName();
    void setStatusID(int newID);
    void setStatusName(QString newName);

private:
    // Private variabler
    bool changed, statusIDchanged;
    int statusID, lastID;
    psql *p;
    QString statusName, winTitle; // Tittelen som skal brukes på meldingsboksene.
    Ui::ShowStatuses *ui;

    // Private metoder
    void checkChanges();
    void closeEvent(QCloseEvent *event) override;
    bool isChanged();
    void setChanged(bool change);

private slots:
    void buttonFirstClicked();
    void buttonLastClicked();
    void buttonNextClicked();
    void buttonPreviousClicked();
    void comboboxStatusIDChanged();
    void lineEditStatusnameChanged();
    void btnSaveClicked();
    void btnDeleteClicked();
};

#endif // SHOWSTATUSES_H
