#include "mainwindow.h"
#include <QApplication>
#include "presenters/mainpresenter.h"
#include "net/udplistener.h"
#include <QMessageBox>
#include <QThread>
#include "gbl.h"
#include "logger.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    UDPListener *listener = new UDPListener(gbl::hostAddress, gbl::portListening);


    Logger* log = Logger::Instance();
    QThread *thread = new QThread;
    log->moveToThread(thread);

    log->startLogging();

    MainWindow w;
    QMessageBox box;

    if(listener->start())
    {
        MainPresenter *presenter = new MainPresenter(&w, listener);
        presenter->showView();
    }
    else
    {
        QString str = QString("Problem connect to UDP socket on port %1").arg(gbl::portListening);
        box.setText(str);
        box.show();
    }

    return a.exec();
}
