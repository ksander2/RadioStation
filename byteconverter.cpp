#include "byteconverter.h"
#include <QBitArray>
#include "gbl.h"

ByteConverter::ByteConverter(Device *device, QObject *parent) : QObject(parent)
{
    _device = device;
}

QByteArray ByteConverter::getByteArrayOfState()
{
    QByteArray bytes;
    bytes.resize(8);
    bytes.fill(0);

    StateDevice *state = _device->getState();

    char firstByte=0;

    firstByte |= state->valid();
    firstByte |= state->signal();
    firstByte |= state->connection();

    firstByte |= state->avaliableInfo()<<5;

    bytes[0] =firstByte;
    bytes[1] = bytes[1] | state->signalLevel();

    bool *connects_sub = state->abonents_connect();
    int sub_number = sizeof(connects_sub);

    for(int i=0; i< sub_number; i++)
    {
        bytes[2] = bytes[2] | (*connects_sub++ << i);
    }

    return bytes;
}

QByteArray ByteConverter::getByteArrayOfMode()
{
    QByteArray bytes;
    bytes.resize(8);
    bytes.fill(0);

    OperationMode *opMode = _device->OpMode();
    bytes[0] = bytes[0] | opMode->mode();
    bytes[0] = bytes[0] | opMode->communicationType();

    bytes[1] = opMode->speed();

    quint16 frequency = opMode->frequency();

    char a = (frequency >> 8) & 0XFF;
    char b = frequency & 0XFF;

    bytes[5] = b;
    bytes[6] = a;

    bytes[7] = bytes[7] | opMode->inversion();
    bytes[7] = bytes[7] | opMode->compression() << 4;

    return bytes;
}

QByteArray ByteConverter::ByteArrayOfsubscriber(subscriber *sub)
{
    QByteArray bytes;
    bytes.resize(3);
    bytes.fill(0);

    bytes[0] = sub->id() & 0xFF;
    bytes[1] = sub->numberChannel() & 0xFF;
    bytes[2] = bytes[2] | sub->autoCall();
    bytes[2] = bytes[2] | sub->supportConnection() << 4;

    return bytes;
}

QByteArray ByteConverter::getByteArrayOfAllSubscribers()
{
    QByteArray bytes;
    QList<subscriber*> subscribers = _device->getListSubscribers();

    foreach (subscriber * sub, subscribers) {
       QByteArray temp_array = ByteArrayOfsubscriber(sub);
       bytes.append(temp_array);
    }

    QByteArray temp;
    temp.resize(12);
    temp.fill(0);
    bytes.append(temp);

    return bytes;
}

QByteArray ByteConverter::getAllRegisters()
{
    QByteArray bytes;

    bytes.append(getByteArrayOfMode());
    bytes.append(getByteArrayOfAllSubscribers());
    bytes.append(getByteArrayOfState());

    return bytes;
}
