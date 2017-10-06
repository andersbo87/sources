#ifndef NEWSTATUS_H
#define NEWSTATUS_H
#include <QCloseEvent>
#include "psql.h"
#include <QMainWindow>

namespace Ui {
class NewStatus;
}

/**
 * @brief The NewStatus class
 */
class NewStatus : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewStatus(QString windowTitle, psql *pg,QWidget *parent = 0);
    ~NewStatus();
    void setStatus(QString newStatus);
    QString getStatus();

private:
    Ui::NewStatus *ui;
    void closeEvent(QCloseEvent *event) override;
    psql *p;
    bool changed, close;
    QString status, title;
    bool canSave();

private slots:
    void OKButtonClicked();
    void lineEditStatusNameChanged();
};

#endif // NEWSTATUS_H
