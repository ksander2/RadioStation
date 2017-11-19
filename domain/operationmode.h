#ifndef OPERATIONMODE_H
#define OPERATIONMODE_H

#include <QObject>
#include <QMap>

class OperationMode : public QObject
{
    Q_OBJECT
    Q_ENUMS(Mode)
    Q_ENUMS(CommunicationType)
public:
    explicit OperationMode(QObject *parent = 0);
    enum Mode
    {
       NONE_MODE =0x00,
       TEST =0x01,
       SILENCE =0x02,
       MAIN = 0x03
    };

    enum CommunicationType
    {
       NONE_TYPE =0x00,
       SIMPLEX =0x10,
       DUPLEX =0x20,
       HALFDUPLEX = 0x30
    };

    enum Speed
    {
        SNone = 0x00,
        S2_4 = 0x01,
        S4_8 = 0x02,
        S9_6 = 0x03,
        S32 = 0x11,
        S64 = 0x12,
        S128 = 0x13,
        S256 = 0x14,
        S512 =0x15
    };

    OperationMode::CommunicationType communicationType() const;
    void setCommunicationType(const OperationMode::CommunicationType &communicationType);

    OperationMode::Mode mode() const;
    void setMode(const OperationMode::Mode &mode);

    OperationMode::Speed speed() const;
    void setSpeed(const OperationMode::Speed &speed);

    quint16 frequency() const;
    void setFrequency(const quint16 &frequency);

    bool inversion() const;
    void setInversion(bool inversion);

    bool compression() const;
    void setCompression(bool compression);

signals:

public slots:
private:
    OperationMode::Mode _mode = OperationMode::Mode::SILENCE;
    OperationMode::CommunicationType _communicationType = OperationMode::CommunicationType::SIMPLEX;
    OperationMode::Speed _speed = OperationMode::Speed::S64;

    quint16 _frequency = 30000;
    bool _inversion = true;
    bool _compression = true;

};

#endif // OPERATIONMODE_H
