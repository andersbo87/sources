#ifndef SHOWCOUNTRIES_H
#define SHOWCOUNTRIES_H

#include <QMainWindow>
#include <QCloseEvent>
#include "psql.h"

namespace Ui {
class ShowCountries;
}

class ShowCountries : public QMainWindow
{
    Q_OBJECT

public:
    // Konstruktør og destruktør
    explicit ShowCountries(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~ShowCountries();

    // Offentlige metoder:
    void getCountries();
    void getCountry(int countryID);
    int getCountryID();
    QString getCountryName();
    void getCountryIDs();
    void setCountryID(int newID);
    void setCountryName(QString newName);

private:
    // Private variabler for denne klassen:
    bool changed, countryIDchanged;
    int countryID, lastID;
    psql *p;
    QString countryName, title; //title = the title to be used as titles in QMessageBox.
    Ui::ShowCountries *ui;

    // Private metoder:
    void checkChanges();
    void closeEvent(QCloseEvent *event) override;
    bool isChanged();
    void setChanged(bool change);

private slots:
    void buttonFirstClicked();
    void buttonLastClicked();
    void buttonNextClicked();
    void buttonPreviousClicked();
    void comboboxCountryIDChanged();
    void lineEditCountrynameChanged();
};

#endif // SHOWCOUNTRIES_H
