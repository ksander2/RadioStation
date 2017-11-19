#ifndef SUBSCRIBERWIDGET_H
#define SUBSCRIBERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "domain/subscriber.h"

class SubscriberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubscriberWidget(subscriber *sub, QWidget *parent = 0);
    void update(quint8 id, quint8 num_channel, bool autocall, bool support_connect);

signals:

public slots:

private:
    QVBoxLayout *layout;

    QLabel *lblId;
    QLabel *lblNum_channel;
    QLabel *lblAutocall;
    QLabel *lblsupport_connect;

    QString boolToWord(bool b);
    void paintEvent(QPaintEvent *);

};

#endif // SUBSCRIBERWIDGET_H
