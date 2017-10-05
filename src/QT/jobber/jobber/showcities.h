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
    explicit ShowCities(psql *pg, QWidget *parent = 0);
    ~ShowCities();

private:
    Ui::ShowCities *ui;
    psql *p;
    void closeEvent(QCloseEvent *event) override;
};

#endif // SHOWCITIES_H
