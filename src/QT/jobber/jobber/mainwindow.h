#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "psql.h"
#include "connectpsql.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief cp A pointer to the connectPsql class
     */
    connectPsql *cp;

    /**
     * @brief MainWindow Class constructor
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    psql *p;
    QString progName;
private slots:
    void btn_newJob_Click();
    void btn_showJobs_Click();
    void btn_NewCity_Click();
    void btn_NewStatus_Click();
    void btn_ShowCities_Click();
    void btn_ShowStatuses_Click();
    void btn_NewCountry_Click();
    void btn_ShowCountries_Click();
};

#endif // MAINWINDOW_H
