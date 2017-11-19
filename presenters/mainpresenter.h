#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

#include <QObject>
#include "mainwindow.h"
#include "net/udplistener.h"
#include "byteconverter.h"
#include "logger.h"

class MainPresenter : public QObject
{
    Q_OBJECT
public:
    explicit MainPresenter(MainWindow *window, UDPListener *listener, QObject *parent = 0);
    void showView();
    ~MainPresenter();

signals:
    void updateMode(char, char, char, quint16, bool, bool);
    void updateSubscribers();

private slots:
    void getUDPdata(QByteArray &bytes);

private:

    MainWindow *_window;
    UDPListener *_listener;
    Device *_device;
    ByteConverter *_byteConverter;

    void SendStateDevice(QByteArray &bytes);
    QByteArray FormingByteArrayToResponce(QByteArray &bytesRequest, QByteArray registry);
    void ParsingByteArray(QByteArray &bytesRequest);

    bool ChangeModeRegistersGroup(QByteArray &bytes);
    bool ChangeSubscriberRegistersGroup(QByteArray &bytes);
    Logger *_log;

};
#endif // MAINPRESENTER_H
