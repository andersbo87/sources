#ifndef VIEWJOBS_H
#define VIEWJOBS_H

#include <QMainWindow>
#include <QCloseEvent>
#include "psql.h"

namespace Ui {
class ViewJobs;
}

/**
 * @brief The ViewJobs class
 */
class ViewJobs : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief ViewJobs The ViewJobs class constructor
     * @param pg A pointer to the PostgreSQL database class.
     * @param parent
     */
    explicit ViewJobs(psql *pg, QWidget *parent = 0);
    ~ViewJobs();
    void getApplications();
    void getApplication(int appID);
    void setApplicationID(int newID);
    void setTitle(QString newTitle);
    void setCompany(QString newCompany);
    void setCityID(int newTownID);
    void setStatusID(int newStatusID);
    void setDate(QString newDate);
    int getApplicationID();
    QString getTitle();
    QString getCompany();
    int getCityID();
    int getStatusID();
    QString getDate();
    void getCityIDs();
    void getStatusIDs();
    bool isChanged();
    void setChanged(bool change);
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::ViewJobs *ui;
    psql *p;
    QString title, company, date;
    int statusid, cityid, applicationid, lastid;
    bool changed, soknadIDChanged;
    void checkChanges();

private slots:
    void comboboxApplicationIDChanged();
    void lineEditTitleChanged();
    void lineEditCompanyChanged();
    void lineEditDealineChanged();
    void comboBoxCityIDChanged();
    void comboBoxStatusIDChanged();
    void buttonFirstClicked();
    void buttonPreviousClicked();
    void buttonNextClicked();
    void buttonLastClicked();
};

#endif // VIEWJOBS_H
