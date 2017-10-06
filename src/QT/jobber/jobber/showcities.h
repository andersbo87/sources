#ifndef SHOWCITIES_H
#define SHOWCITIES_H
#include <QCloseEvent>
#include "psql.h"
#include <QMainWindow>

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
    /**
     * @brief ShowCities The ShowCitis class constructor.
     * @param pg A pointer to the PostgreSQL database
     * @param parent
     */
    explicit ShowCities(QString title, psql *pg, QWidget *parent = 0);
    ~ShowCities();
    void getCities();
    void getCity(int cityID);
    void setCityID(int newID);
    void setCityName(QString newName);
    void setCountryID(int newID);
    int getCityID();
    void getCountryIDs();
    int getCountryID();
    QString getCityName();
    QString getCountryName();

private:
    Ui::ShowCities *ui;
    psql *p;
    QString cityName, countryName, title;
    int cityID, countryID, lastID;
    bool changed, cityIDchanged;
    void checkChanges();
    bool isChanged();
    void setChanged(bool change);
    void closeEvent(QCloseEvent *event) override;

private slots:
    void comboboxCityIDChanged();
    void comboboxCountryIDChanged();
    void lineEditCityNameChanged();
    void buttonFirstClicked();
    void buttonPreviousClicked();
    void buttonNextClicked();
    void buttonLastClicked();
};

#endif // SHOWCITIES_H
