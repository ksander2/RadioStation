#ifndef BYTECONVERTER_H
#define BYTECONVERTER_H

#include <QObject>
#include "domain/device.h"

class ByteConverter : public QObject
{
    Q_OBJECT
public:
    explicit ByteConverter(Device *device, QObject *parent = 0);
    QByteArray getByteArrayOfState();
    QByteArray getByteArrayOfMode();
    QByteArray getByteArrayOfAllSubscribers();
    QByteArray getAllRegisters();

signals:

public slots:
private:
    Device *_device;
    QByteArray ByteArrayOfsubscriber(subscriber *sub);
};

#endif // BYTECONVERTER_H
