#include "spesificjobs.h"
#include "ui_spesificjobs.h"

// Konstruktør og destruktør
SpesificJobs::SpesificJobs(QString title, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpesicficJobs)
{
    ui->setupUi(this);
    winTitle = title;
    p = pg;

    connect(ui->btnSearch, SIGNAL(clicked(bool)), this, SLOT(btnSearchClicked()));
    connect(ui->lineEditJobTitle, SIGNAL(textChanged(QString)), this, SLOT(lineEditJobTitleChanged()));
    connect(ui->lineEditCompanyName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCompanyNameChanged()));
    connect(ui->lineEditDeadline, SIGNAL(textChanged(QString)), this, SLOT(lineEditDeadlineChanged()));
    connect(ui->comboBoxCityName, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxCityNameChanged()));
    connect(ui->comboBoxStatusName, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxStatusChanged()));
    getCityNames();
    getStatuses();
}

SpesificJobs::~SpesificJobs()
{
    delete ui;
}

// Offentlige metoder:
// "Getters"
QString SpesificJobs::getJobTitle()
{
    return jobTitle;
}

QString SpesificJobs::getCompanyName()
{
    return companyName;
}

QString SpesificJobs::getCityName()
{
    return cityName;
}

QString SpesificJobs::getStatus()
{
    return status;
}

QString SpesificJobs::getDeadline()
{
    return deadline;
}

// "Setters" - metoder som angir verdier
void SpesificJobs::setJobTitle(QString newTitle)
{
    jobTitle = newTitle;
}

void SpesificJobs::setCompanyName(QString newName)
{
    companyName = newName;
}

void SpesificJobs::setCityName(QString newCityName)
{
    if(QString::compare(newCityName, "Ingen spesielle steder", Qt::CaseSensitive) == 0)
        return;
    cityName = newCityName;
}

void SpesificJobs::setStatus(QString newStatus)
{
    if(QString::compare(newStatus, "Ingen spesielle statuser", Qt::CaseSensitive) == 0)
        return;
    status = newStatus;
}

void SpesificJobs::setDeadline(QString newDeadline)
{
    deadline = newDeadline;
}

// Andre offentlige metoder:
void SpesificJobs::getCityNames()
{
    ui->comboBoxCityName->addItem("Ingen spesielle steder");
    try
    {
        QList<QString> list = p->getCityNames();
        int i = 0;
        QList<QString>::iterator iter = list.begin();
        while(iter != list.end())
        {
            ui->comboBoxCityName->addItem(list.value(i));
            i++;
            iter++;
        }
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText(e.what());
        msg.exec();
    }
}

void SpesificJobs::getStatuses()
{
    ui->comboBoxStatusName->addItem("Ingen spesielle statuser");
    try
    {
        QList<QString> list = p->getStatuses();
        int i = 0;
        QList<QString>::iterator iter = list.begin();
        while(iter != list.end())
        {
            ui->comboBoxStatusName->addItem(list.value(i));
            i++;
            iter++;
        }
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(winTitle);
        msg.setText(e.what());
        msg.exec();
    }
}

void SpesificJobs::appendApplicationIDs()
{
    QList<QStandardItem *> list;
    QList<int> res = p->getSpecificApplicationIDs(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString());
    QList<int>::iterator iterInt = res.begin();
    int i = 0;
    while(iterInt != res.end())
    {
        list.append(new QStandardItem(QString::number(res.value(i))));
        i++;
        iterInt++;
    }
    model->appendColumn(list);
}
void SpesificJobs::appendJobTitles()
{
    QList<QStandardItem *> list;
    QList<QString> jobTitles = p->getSpecificJobNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString());
    QList<QString>::iterator iter;
    iter = jobTitles.begin();
    int i = 0;
    while(iter != jobTitles.end())
    {
        list.append(new QStandardItem(jobTitles.value(i)));
        i++;
        iter++;
    }
    model->appendColumn(list);
}
void SpesificJobs::appendCompanyNames()
{
    QList<QStandardItem *> list;
    QList<QString> companyNames = p->getSpecificCompanyNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = companyNames.begin(); iter != companyNames.end(); iter++)
    {
        list.append(new QStandardItem(companyNames.value(i)));
        i++;
    }
    model->appendColumn(list);
}

void SpesificJobs::appendCityNames()
{
    QList<QString> cityNames = p->getSpecificCityNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString());
    QList<QStandardItem *> list;
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = cityNames.begin(); iter != cityNames.end(); iter++)
    {
        list.append(new QStandardItem(cityNames.value(i)));
        i++;
    }
    model->appendColumn(list);
}

void SpesificJobs::appendStatuses()
{
    QList<QStandardItem *> list;
    QList<QString> statuses = p->getSpecificStatuses(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = statuses.begin(); iter != statuses.end(); iter++)
    {
        list.append(new QStandardItem(statuses.value(i)));
        i++;
    }
    model->appendColumn(list);
}

void SpesificJobs::appendDeadlines()
{
    QList<QStandardItem *> list;
    QList<QString> deadlines = p->getSpecificDeadlines(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = deadlines.begin(); iter != deadlines.end(); iter++)
    {
        list.append(new QStandardItem(deadlines.value(i)));
        i++;
    }
    model->appendColumn(list);
}

// Metoder som er plassert under private slots:
void SpesificJobs::btnSearchClicked()
{
    model = new QStandardItemModel(this);
    appendApplicationIDs();
    appendJobTitles();
    appendCompanyNames();
    appendCityNames();
    appendStatuses();
    appendDeadlines();
    ui->tableViewResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList h;
    h << "ID" << "Tittel" << "Bedrift" << "Stedsnavn" << "Status" << "Søknadsfrist";
    model->setHorizontalHeaderLabels(h);
    ui->tableViewResults->setModel(model);
}

void SpesificJobs::lineEditJobTitleChanged()
{
    setJobTitle(ui->lineEditJobTitle->text());
}

void SpesificJobs::lineEditCompanyNameChanged()
{
    setCompanyName(ui->lineEditCompanyName->text());
}

void SpesificJobs::lineEditDeadlineChanged()
{
    setDeadline(ui->lineEditDeadline->text());
}

void SpesificJobs::comboBoxCityNameChanged()
{
    setCityName(ui->comboBoxCityName->currentText());
}

void SpesificJobs::comboBoxStatusChanged()
{
    setStatus(ui->comboBoxStatusName->currentText());
}
