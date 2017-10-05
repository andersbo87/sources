#include "mainwindow.h"
#include <QApplication>
#include <QCloseEvent>
#include "ui_mainwindow.h"
#include "newjob.h"
#include "viewjobs.h"
#include "newcity.h"
#include "newstatus.h"
#include "showcities.h"
#include "showstatuses.h"
#include "psql.h"
#include <pqxx/pqxx>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_newJob, SIGNAL(clicked()), this, SLOT(btn_newJob_Click()));
    connect(ui->btn_ShowJobs, SIGNAL(clicked()), this, SLOT(btn_showJobs_Click()));
    connect(ui->btn_NewCity, SIGNAL(clicked(bool)), this, SLOT(btn_NewCity_Click()));
    connect(ui->btn_NewStatus, SIGNAL(clicked(bool)), this, SLOT(btn_NewStatus_Click()));
    connect(ui->btn_ShowCities, SIGNAL(clicked(bool)), this, SLOT(btn_ShowCities_Click()));
    connect(ui->btn_ShowStatuses, SIGNAL(clicked(bool)), this, SLOT(btn_ShowStatuses_Click()));
    cp = new connectPsql();
    p = cp->p; // Kanskje ikke verdens smarteste idé, men lar den likevel peke på psql-objektet i klassen "connectpsql" inntil videre.
    cp->exec();
    if(cp->result() == cp->Rejected)
    {
        exit(1);
    }
}

void MainWindow::btn_NewStatus_Click()
{
    NewStatus *ns = new NewStatus(p, this);
    ns->show();
}

void MainWindow::btn_ShowCities_Click()
{
    ShowCities *sc = new ShowCities(p, this);
    sc->show();
}

void MainWindow::btn_ShowStatuses_Click()
{
    ShowStatuses *ss = new ShowStatuses(p, this);
    ss->show();
}

void MainWindow::btn_NewCity_Click()
{
    NewCity *nc = new NewCity(p, this);
    nc->show();
}

void MainWindow::btn_showJobs_Click()
{
    ViewJobs *vj = new ViewJobs(p, this);
    vj->show();
}


void MainWindow::btn_newJob_Click()
{
    /*
     * Åpner opp et nytt vindu som inneholder et skjema brukeren fyller ut
     * hvor man legger inn detaljer om den nye jobben.
    */
    NewJob *nj = new NewJob(p, this);
    nj->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
