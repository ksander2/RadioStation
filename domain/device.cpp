#include "device.h"
#include "gbl.h"

Device::Device(QObject *parent) : QObject(parent)
{
    opMode = new OperationMode(this);
    state = new StateDevice(this);

    for(int i=0; i<gbl::subscriber_number; i++)
    {
        subscriber *sub = new subscriber(i, i, false, true, this);
        _listSubscribers.append(sub);
    }
}

OperationMode *Device::OpMode() const
{
    return opMode;
}

StateDevice *Device::getState() const
{
    return state;
}

void Device::setState(StateDevice *value)
{
    state = value;
}

QList<subscriber *> Device::getListSubscribers() const
{
    return _listSubscribers;
}

void Device::setListSubscribers(const QList<subscriber *> &listSubscribers)
{
    _listSubscribers = listSubscribers;
}

