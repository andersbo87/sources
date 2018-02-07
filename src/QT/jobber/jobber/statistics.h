#ifndef STATISTICS_H
#define STATISTICS_H
#include "psql.h"
#include <QDialog>

namespace Ui {
class statistics;
}

class statistics : public QDialog
{
    Q_OBJECT

public:
    explicit statistics(psql *pg, QWidget *parent = 0);
    ~statistics();

private:
    Ui::statistics *ui;
    void updateData();
    psql *p;

private slots:
    void btnUpdateClicked();
};

#endif // STATISTICS_H
