#ifndef NEWCOUNTRY_H
#define NEWCOUNTRY_H

#include <QCloseEvent>
#include "psql.h"
#include <QMainWindow>

namespace Ui {
class NewCountry;
}

class NewCountry : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewCountry(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~NewCountry();
    QString getCountry();
    void setCountry(QString newCountry);

private:
    // Private variabler
    bool changed, close;
    psql *p;
    QString country, title;
    Ui::NewCountry *ui;

    // Private metoder
    bool canSave();
    void closeEvent(QCloseEvent *event) override;


private slots:
    void OKButtonClicked();
    void lineEditCountryNameChanged();
};

#endif // NEWCOUNTRY_H
