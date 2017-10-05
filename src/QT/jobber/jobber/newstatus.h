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
    /**
     * @brief NewStatus NewStatus class constructor
     * @param pg A pointer to the PostgreSQL database
     * @param parent
     */
    explicit NewStatus(psql *pg,QWidget *parent = 0);
    ~NewStatus();
    void setStatus(QString newStatus);
    QString getStatus();

private:
    Ui::NewStatus *ui;
    /**
     * @brief closeEvent Code to be executed when the window closes
     * @param event This pointer points to the QCloseEvent class that contains functions to prvent the window from closing.
     */
    void closeEvent(QCloseEvent *event) override;
    psql *p;
    bool changed, close;
    QString status;
    bool canSave();

private slots:
    void OKButtonClicked();
    void lineEditStatusNameChanged();
};

#endif // NEWSTATUS_H
