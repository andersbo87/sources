#ifndef NEWJOB_H
#define NEWJOB_H

#include "psql.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QPushButton>

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
    explicit NewJob(psql *pg, QWidget *parent = 0);
    ~NewJob();
    void setTitle(QString newTitle);
    void setCompany(QString newCompany);
    void setCityID(int newCityID);
    void setStatusID(int newStatusID);
    void setDate(QString newDate);
    QString getTitle();
    QString getCompany();
    int getCityID();
    int getStatusID();
    QString getDate();

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
    QString title, company, date;
    int statusid, cityid;
    psql *p;

private slots:
    void titleTextChanged();
    void companyTextChanged();
    void cityIDchanged();
    void statusIDchanged();
    void dateChanged();
    void OKButtonClicked();
    void CancelButtonClicked();
};

#endif // NEWJOB_H
