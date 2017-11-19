#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "byteconverter.h"
#include "gbl.h"
#include "logger.h"
#include "logview.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FrequencySbx_valueChanged(int arg1)
{
    device->OpMode()->setFrequency(arg1);
}

void MainWindow::on_inversionCbx_clicked(bool checked)
{
     device->OpMode()->setInversion(checked);
}

void MainWindow::on_compressionCbx_clicked(bool checked)
{
    device->OpMode()->setCompression(checked);
}

QString MainWindow::boolToWord(bool b)
{
    if(b) return "да";
    else return "нет";
}

bool MainWindow::compareNumbers(const QString &s1, const QString &s2)
{
    return s1.toDouble() < s2.toDouble();
}

void MainWindow::on_modeCmbx_activated(const QString &arg1)
{
    device->OpMode()->setMode(modeOptions->value(arg1));
}

void MainWindow::on_speedCmbx_activated(const QString &arg1)
{
    device->OpMode()->setSpeed(speedOptions->value(arg1));
}

void MainWindow::on_ComunicationTypeCmbx_activated(const QString &arg1)
{
    device->OpMode()->setCommunicationType(comTypeOptions->value(arg1));
}

void MainWindow::setDevice(Device *value)
{
    device = value;
    comTypeOptions = new QMap<QString, OperationMode::CommunicationType>;

    comTypeOptions->insert("none", OperationMode::CommunicationType::NONE_TYPE);
    comTypeOptions->insert("simplex", OperationMode::CommunicationType::SIMPLEX);
    comTypeOptions->insert("duplex", OperationMode::CommunicationType::DUPLEX);
    comTypeOptions->insert("halfduplex", OperationMode::CommunicationType::HALFDUPLEX);

    QStringList list = comTypeOptions->keys();

    ui->ComunicationTypeCmbx->addItems(list);
    ui->ComunicationTypeCmbx->setCurrentText(comTypeOptions->key(device->OpMode()->communicationType()));

    modeOptions = new QMap<QString, OperationMode::Mode>;
    modeOptions->insert("none", OperationMode::Mode::NONE_MODE);
    modeOptions->insert("test", OperationMode::Mode::TEST);
    modeOptions->insert("silence", OperationMode::Mode::SILENCE);
    modeOptions->insert("main", OperationMode::Mode::MAIN);

    ui->modeCmbx->addItems(modeOptions->keys());
    ui->modeCmbx->setCurrentText(modeOptions->key(device->OpMode()->mode()));

    speedOptions = new QMap<QString, OperationMode::Speed>;
    speedOptions->insert("none", OperationMode::Speed::SNone);
    speedOptions->insert("2.4", OperationMode::Speed::S2_4);
    speedOptions->insert("4.8", OperationMode::Speed::S4_8);
    speedOptions->insert("9.6", OperationMode::Speed::S9_6);
    speedOptions->insert("32", OperationMode::Speed::S32);
    speedOptions->insert("64", OperationMode::Speed::S64);
    speedOptions->insert("128", OperationMode::Speed::S128);
    speedOptions->insert("256", OperationMode::Speed::S256);
    speedOptions->insert("512", OperationMode::Speed::S512);

    QStringList listSpeed = speedOptions->keys();
    qSort(listSpeed.begin(), listSpeed.end(), compareNumbers);

    ui->speedCmbx->addItems(listSpeed);
    ui->speedCmbx->setCurrentText(speedOptions->key(device->OpMode()->speed()));

    ui->FrequencySbx->setValue(device->OpMode()->frequency());

    ui->inversionCbx->setChecked(device->OpMode()->inversion());
    ui->compressionCbx->setChecked(device->OpMode()->compression());

    ui->isValidModemcbx->setChecked(device->getState()->valid());
    ui->isInfoAvaliableCbx->setChecked(device->getState()->avaliableInfo());

    ui->levelSignalSpinbox->setValue(device->getState()->signalLevel());

    connectionOptions = new QMap<StateDevice::Connection, QString>;
    connectionOptions->insert(StateDevice::Connection::NORMAL_CON, "норма");
    connectionOptions->insert(StateDevice::Connection::WARNING_CON , "предупреждение" );
    connectionOptions->insert(StateDevice::Connection::ERROR_CON, "ошибка");

    QStringList connection_status = connectionOptions->values();
    ui->connectionCmbx->addItems(connection_status);
    ui->connectionCmbx->setCurrentText(connectionOptions->value(device->getState()->connection()));

    signalOptions = new QMap<StateDevice::Signal, QString>;
    signalOptions->insert(StateDevice::Signal::NORMAL, "норма");
    signalOptions->insert(StateDevice::Signal::WARNING , "предупреждение" );
    signalOptions->insert(StateDevice::Signal::ERROR, "ошибка");

    QStringList signal_status = signalOptions->values();
    ui->signalCmbx->addItems(signal_status);
    ui->signalCmbx->setCurrentText(signalOptions->value(device->getState()->signal()));

    bool *subscriber_connects = device->getState()->abonents_connect();
    int subscriber_connects_num = sizeof(subscriber_connects);

    for(int i=0; i<subscriber_connects_num; i++)
    {
       bool b = *subscriber_connects++;

       QString aa= QString("Связь с абонентом %1: %2").arg(i).arg(boolToWord(b));
       QLabel *label = new QLabel(aa);
       ui->verticalLayout->addWidget(label);
    }

    QList<subscriber*> sublist = device->getListSubscribers();
    for(int i=0; i<sublist.length(); i++)
    {
        SubscriberWidget * sub_widget = new SubscriberWidget(sublist[i]);
        _listSubWidgets.append(sub_widget);
        ui->horizontalLayout->addWidget(sub_widget);
    }

    QString UDPStatus = QString("Статус UDP:\nПорт прослушки: %1\nПорт отправки сообщений: %2\nХост: %3")
            .arg(gbl::portListening)
            .arg(gbl::portWriting)
            .arg(gbl::hostAddress.toString());
    ui->statusUDPlabel->setText(UDPStatus);
}

void MainWindow::updateModeWidgets(char mode,
                                   char communictionType,
                                   char speed,
                                   quint16 frequency,
                                   bool inverse,
                                   bool compress)
{

    OperationMode::Mode modeEnum = (OperationMode::Mode)mode;
    OperationMode::CommunicationType cType =
            (OperationMode::CommunicationType) communictionType;
    OperationMode::Speed speedEnum = (OperationMode::Speed)speed;

    ui->ComunicationTypeCmbx->setCurrentText(comTypeOptions->key(cType));
    ui->speedCmbx->setCurrentText(speedOptions->key(speedEnum));
    ui->modeCmbx->setCurrentText(modeOptions->key(modeEnum));

    ui->FrequencySbx->setValue(frequency);

    ui->inversionCbx->setChecked(inverse);
    ui->compressionCbx->setChecked(compress);
}

void MainWindow::updateSubscribers()
{
    QList<subscriber*> subs = device->getListSubscribers();
    for(int i=0; i<_listSubWidgets.size(); i++)
    {
        SubscriberWidget *widget = _listSubWidgets[i];
        subscriber *sub = subs[i];
        widget->update(sub->id(),sub->numberChannel(), sub->autoCall(), sub->supportConnection());
    }
}

void MainWindow::on_isValidModemcbx_clicked(bool checked)
{
      device->getState()->setValid(checked);
}

void MainWindow::on_isInfoAvaliableCbx_clicked(bool checked)
{
    device->getState()->setAvaliableInfo(checked);
}

void MainWindow::on_levelSignalSpinbox_valueChanged(int arg1)
{
    device->getState()->setSignalLevel(arg1);
}

void MainWindow::on_signalCmbx_currentIndexChanged(const QString &arg1)
{
    device->getState()->setSignal(signalOptions->key(arg1));
}

void MainWindow::on_connectionCmbx_currentIndexChanged(const QString &arg1)
{
      device->getState()->setConnection(connectionOptions->key(arg1));
}

void MainWindow::on_pushButton_clicked()
{
    QFile *file =new QFile(gbl::LogFileName);
    file->open(QFile::ReadOnly | QFile::Text);
    QString s = file->readAll();
    file->close();
    delete file;

    LogView log_view;
    log_view.setLogtext(s);
    log_view.exec();
}
