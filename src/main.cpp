#include "include/mainwindow.h"
#include "include/authorization.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!connectDatabase())
    {
            return -1; // Exit if the database connection fails
    }

    MainWindow w;
    w.show();
    return a.exec();
}
