#ifndef TESTEFIL_H
#define TESTEFIL_H

#include <QMainWindow>

namespace Ui {
class testefil;
}

class testefil : public QMainWindow
{
    Q_OBJECT

public:
    explicit testefil(QWidget *parent = 0);
    ~testefil();

private:
    Ui::testefil *ui;
};

#endif // TESTEFIL_H
