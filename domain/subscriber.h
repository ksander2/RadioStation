#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>

class subscriber : public QObject
{
    Q_OBJECT
public:
    explicit subscriber(QObject *parent = 0);
    subscriber(quint8 id, quint8 numberChannel, bool autoCall, bool supportConnection, QObject *parent = 0);

    quint8 id() const;
    void setId(const quint8 &id);

    quint8 numberChannel() const;
    void setNumberChannel(const quint8 &numberChannel);

    bool autoCall() const;
    void setAutoCall(bool autoCall);

    bool supportConnection() const;
    void setSupportConnection(bool supportConnection);

signals:

public slots:

private:
    quint8 _id;
    quint8 _numberChannel;
    bool _autoCall;
    bool _supportConnection;

};

#endif // SUBSCRIBER_H
