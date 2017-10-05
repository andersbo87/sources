#ifndef NEWCITY_H
#define NEWCITY_H
#include "psql.h"
#include <QCloseEvent>
#include <QMainWindow>

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
    /**
     * @brief NewCity The NewCity class constructor
     * @param pg Pointer to the PostgreSQL database
     * @param parent
     */
    explicit NewCity(psql *pg, QWidget *parent = 0);
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
    QString cityName;
    bool changed, close;


private slots:
    void OKButtonClicked();
    void countryIDchanged();
    void lineEditCityNameChanged();
};

#endif // NEWCITY_H
