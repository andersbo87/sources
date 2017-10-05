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
    /**
     * @brief ShowStatuses The ShowStatuses class constructor
     * @param pg A pointer to the PostgreSQL database.
     * @param parent
     */
    explicit ShowStatuses(psql *pg, QWidget *parent = 0);
    ~ShowStatuses();

private:
    Ui::ShowStatuses *ui;
    psql *p;
    void closeEvent(QCloseEvent *event) override;
};

#endif // SHOWSTATUSES_H
