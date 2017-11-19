#include "subscriber.h"

subscriber::subscriber(QObject *parent) : QObject(parent)
{

}

subscriber::subscriber(quint8 id, quint8 numberChannel, bool autoCall, bool supportConnection, QObject *parent) : QObject(parent)
{
    _id=id;
    _numberChannel = numberChannel;
    _autoCall = autoCall;
    _supportConnection = supportConnection;
}

quint8 subscriber::id() const
{
    return _id;
}

void subscriber::setId(const quint8 &id)
{
    _id = id;
}

quint8 subscriber::numberChannel() const
{
    return _numberChannel;
}

void subscriber::setNumberChannel(const quint8 &numberChannel)
{
    _numberChannel = numberChannel;
}

bool subscriber::autoCall() const
{
    return _autoCall;
}

void subscriber::setAutoCall(bool autoCall)
{
    _autoCall = autoCall;
}

bool subscriber::supportConnection() const
{
    return _supportConnection;
}

void subscriber::setSupportConnection(bool supportConnection)
{
    _supportConnection = supportConnection;
}
