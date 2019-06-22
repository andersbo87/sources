#include <QApplication>
#include <QWebView>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pid_t pid = fork();
    if(pid == 0){
        const char *pgAdmin[3];
        pgAdmin[0] = "/usr/local/bin/python3.6";
        pgAdmin[1] = "/usr/local/lib/python3.6/site-packages/pgadmin4/pgAdmin4.py";
        pgAdmin[2] = NULL;
        execvp(pgAdmin[0], const_cast<char* const*>(pgAdmin));
    }
    sleep(6);
    QWebView view;
    view.show();
    view.load(QUrl("http://localhost:5050"));
    int res = a.exec();
    system("kill -2 `ps aux | grep /usr/local/lib/python3.6/site-packages/pgadmin4/pgAdmin4.py | awk {'print $2'}`");
    return res;
}
