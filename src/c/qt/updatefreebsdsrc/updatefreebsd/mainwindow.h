#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //QProcess *myProcess;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void slotButtonClicked();
    void On_pushButton_Click();
    void updateError();
    void updateText();
    void deactivateButtons();
    void activateButtons();
    void on_pushButton_2_clicked();
    void on_myFreeBSDUpdateFetchExit(int exitCode, QProcess::ExitStatus exitStatus);
    void on_myFreeBSDUpdateInstallExit(int exitCode, QProcess::ExitStatus exitStatus);
    void on_myPkgUpgradeExit(int exitCode, QProcess::ExitStatus exitStatus);
    void on_pushButton_3_clicked();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
