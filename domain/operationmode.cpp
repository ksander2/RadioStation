#include "operationmode.h"

OperationMode::OperationMode(QObject *parent) : QObject(parent)
{

}

OperationMode::CommunicationType OperationMode::communicationType() const
{
    return _communicationType;
}

void OperationMode::setCommunicationType(const OperationMode::CommunicationType &communicationType)
{
    _communicationType = communicationType;
}

OperationMode::Mode OperationMode::mode() const
{
    return _mode;
}

void OperationMode::setMode(const OperationMode::Mode &mode)
{
    _mode = mode;
}

OperationMode::Speed OperationMode::speed() const
{
    return _speed;
}

void OperationMode::setSpeed(const OperationMode::Speed &speed)
{
    _speed = speed;
}

quint16 OperationMode::frequency() const
{
    return _frequency;
}

void OperationMode::setFrequency(const quint16 &frequency)
{
    _frequency = frequency;
}

bool OperationMode::inversion() const
{
    return _inversion;
}

void OperationMode::setInversion(bool inversion)
{
    _inversion = inversion;
}

bool OperationMode::compression() const
{
    return _compression;
}

void OperationMode::setCompression(bool compression)
{
    _compression = compression;
}
