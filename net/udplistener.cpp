#include "udplistener.h"
#include <QNetworkDatagram>
#include "gbl.h"

UDPListener::UDPListener(QHostAddress host, int portListening, QObject *parent) : QObject(parent)
{
    _host = host;
    _port = portListening;
}

bool UDPListener::start()
{
    socket = new QUdpSocket(this);
    bool b = socket->bind(_host, _port);

    connect(socket, &QUdpSocket::readyRead, this, &UDPListener::readPendingDatagrams);
    return b;
}

void UDPListener::readPendingDatagrams()
{
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        QByteArray array = datagram.data();
        emit dataReady(array);
    }
}

void UDPListener::stop()
{
    disconnect(socket, &QUdpSocket::readyRead, this, &UDPListener::readPendingDatagrams);
    socket->disconnect();
}

quint64 UDPListener::writeDataToUDP(QByteArray &bytes)
{
    return socket->writeDatagram(bytes, _host, gbl::portWriting);
}
