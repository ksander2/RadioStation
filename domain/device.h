#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include "operationmode.h"
#include "statedevice.h"
#include "subscriber.h"

class Device: public QObject
{
    Q_OBJECT
public:
   explicit Device(QObject *parent = 0);

    OperationMode *OpMode() const;

    StateDevice *getState() const;
    void setState(StateDevice *value);

    QList<subscriber *> getListSubscribers() const;
    void setListSubscribers(const QList<subscriber *> &listSubscribers);

private:
    OperationMode *opMode;
    StateDevice *state;
    QList<subscriber *> _listSubscribers;
};

#endif // DEVICE_H
