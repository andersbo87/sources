#ifndef CONNECTPSQL_H
#define CONNECTPSQL_H
#include <QApplication>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include "psql.h"

namespace Ui {
class connectPsql;
}

/**
 * @brief The connectPsql class
 */
class connectPsql : public QDialog
{
    Q_OBJECT


public:
    /**
     * @brief p A PostgreSQL pointer
     */
    psql *p = new psql(); // Ikke verdens beste idé å gjøre denne "offentlig", men for enkelthetens skyld, i og med at jeg er ny…
    /**
     * @brief connectPsql Class constructor
     * @param parent
     */
    explicit connectPsql(QWidget *parent = 0);

    ~connectPsql();

private:
    Ui::connectPsql *ui;
    /**
     * @brief accept
     */
    void accept();
    QString userName,host, password;
private slots:
    void userTextChanged();
    void passwordTextChanged();
    void hostTextChanged();
};

#endif // CONNECTPSQL_H
