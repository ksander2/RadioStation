#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>
#include <QUdpSocket>

class UDPListener : public QObject
{
    Q_OBJECT
public:
    explicit UDPListener(QHostAddress host, int portListening, QObject *parent = 0);
    bool start();
    void stop();
    quint64 writeDataToUDP(QByteArray &bytes);

signals:
    void dataReady(QByteArray &data);
public slots:

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *socket;
    QHostAddress _host;
    int _port;
};

#endif // UDPLISTENER_H
