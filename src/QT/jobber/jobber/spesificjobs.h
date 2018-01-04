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

class SpesificJobs : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpesificJobs(QString title, psql *pg, QWidget *parent = 0);
    ~SpesificJobs();
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
