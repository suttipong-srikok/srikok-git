#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("SRK Git");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("SRK IT Service");
    app.setOrganizationDomain("srkitservice.com");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}