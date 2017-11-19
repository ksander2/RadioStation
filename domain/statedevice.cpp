#include "statedevice.h"

StateDevice::StateDevice(QObject *parent) : QObject(parent)
{
    const int numberSubcribers = 4;
    _abonents_connect = new bool[numberSubcribers] { false, true, true, true };
}

StateDevice::~StateDevice()
{
    delete[] _abonents_connect;
}

bool StateDevice::valid() const
{
    return _valid;
}

void StateDevice::setValid(bool valid)
{
    _valid = valid;
}

bool StateDevice::avaliableInfo() const
{
    return _avaliableInfo;
}

void StateDevice::setAvaliableInfo(bool avaliableInfo)
{
    _avaliableInfo = avaliableInfo;
}

quint8 StateDevice::signalLevel() const
{
    return _signalLevel;
}

void StateDevice::setSignalLevel(const quint8 &signalLevel)
{
    _signalLevel = signalLevel;
}

bool *StateDevice::abonents_connect() const
{
    return _abonents_connect;
}

void StateDevice::setAbonents_connect(bool *abonents_connect)
{
    _abonents_connect = abonents_connect;
}

StateDevice::Signal StateDevice::signal() const
{
    return _signal;
}

void StateDevice::setSignal(const StateDevice::Signal &signal)
{
    _signal = signal;
}

StateDevice::Connection StateDevice::connection() const
{
    return _connection;
}

void StateDevice::setConnection(const StateDevice::Connection &connection)
{
    _connection = connection;
}
