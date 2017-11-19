#ifndef STATEDEVICE_H
#define STATEDEVICE_H

#include <QObject>

class StateDevice : public QObject
{
    Q_OBJECT
public:
    explicit StateDevice(QObject *parent = 0);
    ~StateDevice();

    enum Signal
    {
       NORMAL =  0b00000000,
       WARNING = 0b00000010,
       ERROR =   0b00000100
    };

    enum  Connection
    {
       NORMAL_CON =  0b00000000,
       WARNING_CON = 0b00001000,
       ERROR_CON =   0b00010000
    };

    bool valid() const;
    void setValid(bool valid);

    bool avaliableInfo() const;
    void setAvaliableInfo(bool avaliableInfo);

    quint8 signalLevel() const;
    void setSignalLevel(const quint8 &signalLevel);

    bool *abonents_connect() const;
    void setAbonents_connect(bool *abonents_connect);

    StateDevice::Signal signal() const;
    void setSignal(const StateDevice::Signal &signal);

    StateDevice::Connection connection() const;
    void setConnection(const StateDevice::Connection &connection);

signals:

public slots:
private:
    bool _valid = true;
    bool _avaliableInfo = true;
    quint8 _signalLevel = 235;
    bool *_abonents_connect;
    StateDevice::Signal _signal = Signal::ERROR;
    StateDevice::Connection _connection = Connection::ERROR_CON;

};

#endif // STATEDEVICE_H
