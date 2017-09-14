////////////////////////////////////////////////////////////////:::
//Made By Savinien Bonheur
///////////////////////////////////////////////////////////////::::
#include "mainwindow.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("simplerythmfinder");//We give a name for the Dbus as it need an application name for interprocess communication
    MainWindow w;//declare a mainwindow object
    w.show();//display it
    app.exec();//execute the code
}

