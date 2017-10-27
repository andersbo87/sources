#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

// Checks the operating system on which the application is run...
char *getOS()
{
#ifdef __FreeBSD__
return "FreeBSD";
#elif __NetBSD__
return "NetBSD";
#elif __APPLE__
return "Darwin"; // Darwin is the UNIX part of OS X.
#elif __linux__
return "Linux";
#elif __sun
return "SunOS"; // SunOS = Solaris.
#elif __OpenBSD__
return "OpenBSD";
#else
return "Other"; // Non-supported operating systems.
#endif
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(476,466);
    w.show();
    if(strcmp(getOS(), "FreeBSD") != 0){
        QMessageBox message;
        message.setIcon(message.Critical);
        message.setWindowTitle("Oppdater FreeBSD og installerte programmer");
        message.setText(QString::fromUtf8("Dette programmet kan kun kjøres på FreeBSD-baserte systemer."));
        message.exec();
    }
    return a.exec();
}
