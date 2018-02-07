#include "spesificjobs.h"
#include "ui_spesificjobs.h"

// Konstruktør og destruktør
/**
 * @brief SpesificJobs::SpesificJobs SpesificJobs class constructor
 * @param title The title to be used in windows and dialog boxes.
 * @param pg Pointer to the psql class
 * @param parent
 */
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

/**
 * @brief SpesificJobs::getJobTitle Gets the job title
 * @return The job title
 */
QString SpesificJobs::getJobTitle()
{
    return jobTitle;
}

/**
 * @brief SpesificJobs::getCompanyName Gets the company name
 * @return The name of the company
 */
QString SpesificJobs::getCompanyName()
{
    return companyName;
}

/**
 * @brief SpesificJobs::getCityName Gets the name of the city where the job is located
 * @return The city name
 */
QString SpesificJobs::getCityName()
{
    return cityName;
}

/**
 * @brief SpesificJobs::getStatus Gets the status of the job application
 * @return The name of the current application status (sent, declined/rejected, etc)
 */
QString SpesificJobs::getStatus()
{
    return status;
}

/**
 * @brief SpesificJobs::getDeadline Gets the deadline of the application
 * @return The application deadline
 */
QString SpesificJobs::getDeadline()
{
    return deadline;
}

/**
 * @brief SpesificJobs::getMotivation Gets the motivation for applying for this job.
 * @return The application motivation
 */
QString SpesificJobs::getMotivation()
{
    return motivation;
}

// "Setters" - metoder som angir verdier
/**
 * @brief SpesificJobs::setJobTitle Sets the title of the job
 * @param newTitle The name of the job
 */
void SpesificJobs::setJobTitle(QString newTitle)
{
    jobTitle = newTitle;
}

/**
 * @brief SpesificJobs::setCompanyName Sets the name of the company
 * @param newName The company name
 */
void SpesificJobs::setCompanyName(QString newName)
{
    companyName = newName;
}

/**
 * @brief SpesificJobs::setCityName Sets the name of the city where the job is located.
 * @param newCityName The name of the city
 */
void SpesificJobs::setCityName(QString newCityName)
{
    if(QString::compare(newCityName, "Ingen spesielle steder", Qt::CaseSensitive) == 0)
        return;
    cityName = newCityName;
}

/**
 * @brief SpesificJobs::setStatus Set the status of the job application
 * @param newStatus The status of the application.
 */
void SpesificJobs::setStatus(QString newStatus)
{
    if(QString::compare(newStatus, "Ingen spesielle statuser", Qt::CaseSensitive) == 0)
        return;
    status = newStatus;
}

/**
 * @brief SpesificJobs::setDeadline Sets the deadline of the application
 * @param newDeadline The application dealine (could be a date in any format or 'ASAP' or something)
 */
void SpesificJobs::setDeadline(QString newDeadline)
{
    deadline = newDeadline;
}

/**
 * @brief SpesificJobs::setMotivation Sets the reasons for applying for this job (optional)
 * @param newMotivation The motivation. Is there something about the job or company that made you apply for that job
 */
void SpesificJobs::setMotivation(QString newMotivation)
{
    motivation = newMotivation;
}

// Andre offentlige metoder:
/**
 * @brief SpesificJobs::getCityNames Fetches a list of city names to be added to the comboBoxCityName.
 */
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

/**
 * @brief SpesificJobs::getStatuses Fetches a list of status names to be added to the comboBoxStatusName
 */
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
    QList<int> res = p->getSpecificApplicationIDs(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
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
    QList<QString> jobTitles = p->getSpecificJobNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
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
    QList<QString> companyNames = p->getSpecificCompanyNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
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
    QList<QString> cityNames = p->getSpecificCityNames(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
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
    QList<QString> statuses = p->getSpecificStatuses(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
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
    QList<QString> deadlines = p->getSpecificDeadlines(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = deadlines.begin(); iter != deadlines.end(); iter++)
    {
        list.append(new QStandardItem(deadlines.value(i)));
        i++;
    }
    model->appendColumn(list);
}

void SpesificJobs::appendMotivations()
{
    QList<QStandardItem *> list;
    QList<QString> motivations = p->getSpecificMotivations(getJobTitle().toStdString(), getCompanyName().toStdString(), getCityName().toStdString(), getStatus().toStdString(), getDeadline().toStdString(), getMotivation().toStdString());
    QList<QString>::iterator iter;
    int i = 0;
    for(iter = motivations.begin(); iter != motivations.end(); iter++)
    {
        list.append(new QStandardItem(motivations.value(i)));
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
    appendMotivations();
    ui->tableViewResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList h;
    h << "ID" << "Tittel" << "Bedrift" << "Stedsnavn" << "Status" << "Søknadsfrist" << "Motivasjon";
    model->setHorizontalHeaderLabels(h);
    ui->tableViewResults->setModel(model);
    if(model->rowCount() == 0){
        QMessageBox msg;
        msg.setWindowTitle(winTitle);
        msg.setIcon(msg.Information);
        msg.setText("Søket returnerte ingen treff.");
        msg.exec();
    }
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
