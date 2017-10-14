#ifndef VIEWSPECIFICJOBS_H
#define VIEWSPECIFICJOBS_H
#include "psql.h"
#include <QCloseEvent>
#include <QMainWindow>

namespace Ui {
class ViewSpecificJobs;
}

class ViewSpecificJobs : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewSpecificJobs(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~ViewSpecificJobs();

private slots:
    void btnSearch_clicked();

private:
    Ui::ViewSpecificJobs *ui;
    psql *p;
    QString title;
};

#endif // VIEWSPECIFICJOBS_H
