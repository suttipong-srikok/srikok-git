#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Srikok Git");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Srikoksoft");
    app.setOrganizationDomain("srikoksoft.com");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}