#include "subscriberwidget.h"
#include <QStyleOption>
#include <QPainter>

SubscriberWidget::SubscriberWidget(subscriber *sub, QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout;
    QLabel *lblname = new QLabel("Абонент: ");
    lblId = new QLabel(QString("id абоненты: %1").arg(sub->id()));
    lblNum_channel = new QLabel(QString("Номер канала: %1").arg(sub->numberChannel()));
    lblAutocall = new QLabel(QString("Автовызов : %1").arg(sub->autoCall()));
    lblsupport_connect = new QLabel(QString("Поддержка связи: %1").arg(sub->supportConnection()));

    layout->addWidget(lblname);
    layout->addWidget(lblId);
    layout->addWidget(lblNum_channel);
    layout->addWidget(lblAutocall);
    layout->addWidget(lblsupport_connect);

    this->setLayout(layout);
    setStyleSheet("border: 1px solid red");
    QList<QLabel*> lbls = this->findChildren<QLabel*>();

    foreach (QLabel *lbl, lbls) {
        lbl->setStyleSheet("border: 0px");
    }

}

QString SubscriberWidget::boolToWord(bool b)
{
    if(b) return "да";
    else return "нет";
}

void SubscriberWidget::update(quint8 id, quint8 num_channel, bool autocall, bool support_connect)
{
    lblId->setText(QString("id абоненты: %1").arg(id));
    lblNum_channel->setText(QString("Номер канала: %1").arg(num_channel));
    lblAutocall->setText(QString("Автовызов : %1").arg(autocall));
    lblsupport_connect->setText(QString("Поддержка связи: %1").arg(support_connect));
}

void SubscriberWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


