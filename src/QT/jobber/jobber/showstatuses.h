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
    // Konstruktør og destruktør
    /**
     * @brief ShowStatuses The ShowStatuses class constructor
     * @param windowTitle The title to be used with message boxes (QMessageBox)
     * @param pg A pointer to the PostgreSQL database.
     * @param parent
     */
    explicit ShowStatuses(QString windowTitle, psql *pg, QWidget *parent = 0);
    ~ShowStatuses();

    // Offentlige metoder
    void getStatus(int statusID);
    void getStatuses();
    /**
     * @brief getStatusID Gets the ID of the current status
     * @return The status identification number
     */
    int getStatusID();
    QString getStatusName();
    void setStatusID(int newID);
    void setStatusName(QString newName);

private:
    // Private variabler
    bool changed, statusIDchanged;
    int statusID, lastID;
    psql *p;
    QString statusName, title; // Tittelen som skal brukes på meldingsboksene.
    Ui::ShowStatuses *ui;

    // Private metoder
    void checkChanges();
    void closeEvent(QCloseEvent *event) override;
    bool isChanged();
    void setChanged(bool change);

private slots:
    void buttonFirstClicked();
    void buttonLastClicked();
    void buttonNextClicked();
    void buttonPreviousClicked();
    void comboboxStatusIDChanged();
    void lineEditStatusnameChanged();
};

#endif // SHOWSTATUSES_H
