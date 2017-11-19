#include "presenters/mainpresenter.h"
#include "gbl.h"

MainPresenter::MainPresenter(MainWindow *window, UDPListener *listener, QObject *parent) : QObject(parent)
{

    _window = window;
    _listener = listener;
    _device = new Device(this);
    _window->setDevice(_device);
    _byteConverter = new ByteConverter(_device,this);
    _log = Logger::Instance();

    connect(_listener, &UDPListener::dataReady, this, &MainPresenter::getUDPdata);
    connect(this, &MainPresenter::updateMode, _window, &MainWindow::updateModeWidgets);
    connect(this, &MainPresenter::updateSubscribers, _window, &MainWindow::updateSubscribers);
}


void MainPresenter::showView()
{
    _window->show();
}

MainPresenter::~MainPresenter()
{
    _listener->stop();
}


void MainPresenter::getUDPdata(QByteArray &bytes)
{
   // qDebug() << bytes;

    switch (bytes[0]) {
        case WRITING_REGISTERS:
        {
            ParsingByteArray(bytes);
            break;
        }
        case READING_REGISTERS:
        {
            SendStateDevice(bytes);
            break;
        }
        default:
            break;
    }
    _log->logByteArray(bytes, Logger::OPERATION_TYPE::READ);
}

void MainPresenter::SendStateDevice(QByteArray &bytes)
{
    QByteArray temp;
    switch (bytes[1]) {
    case ALL_REGISTERS:
    {
        temp = FormingByteArrayToResponce(bytes,_byteConverter->getAllRegisters());
        _listener->writeDataToUDP(temp);
        break;
    }
    case REGISTERS_GROUP_1:
    {
        temp = FormingByteArrayToResponce(bytes,_byteConverter->getByteArrayOfMode());
        _listener->writeDataToUDP(temp);
        break;
    }
    case REGISTERS_GROUP_2:
    {
        temp = FormingByteArrayToResponce(bytes,_byteConverter->getByteArrayOfAllSubscribers());
        _listener->writeDataToUDP(temp);
        break;
    }
    case REGISTERS_GROUP_3:
    {
        temp = FormingByteArrayToResponce(bytes,_byteConverter->getByteArrayOfState());
        _listener->writeDataToUDP(temp);
        break;
    }
    default:
        temp.append(REQUEST_FAILED);
        temp.append(bytes[1]);
        _listener->writeDataToUDP(temp);
        break;
    }
    _log->logByteArray(temp, Logger::OPERATION_TYPE::WRITE);
}

QByteArray MainPresenter::FormingByteArrayToResponce(QByteArray &bytesRequest, QByteArray registry)
{
    QByteArray bytes;

    bytes.append(REQUEST_COMPLETED);
    bytes.append(bytesRequest[1]);
    bytes.append(registry);

    return bytes;
}

void MainPresenter::ParsingByteArray(QByteArray &bytesRequest)
{
    QByteArray temp;
    switch (bytesRequest[1]) {
    case REGISTERS_GROUP_1:
    {
        if (ChangeModeRegistersGroup(bytesRequest))
        {
            temp.append(REQUEST_COMPLETED);
            temp.append(REGISTERS_GROUP_1);
            _listener->writeDataToUDP(temp);
        }
        else
        {
            temp.append(REQUEST_FAILED);
            temp.append(REGISTERS_GROUP_1);
            _listener->writeDataToUDP(temp);
        }
        break;
    }
    case REGISTERS_GROUP_2:
    {
        if (ChangeSubscriberRegistersGroup(bytesRequest))
        {
            temp.append(REQUEST_COMPLETED);
            temp.append(REGISTERS_GROUP_2);
            _listener->writeDataToUDP(temp);  
        }
        else
        {
            temp.append(REQUEST_FAILED);
            temp.append(REGISTERS_GROUP_2);
            _listener->writeDataToUDP(temp);
        }
        break;
    }
    default:
        temp.append(REQUEST_FAILED);
        temp.append(bytesRequest[1]);
        _listener->writeDataToUDP(temp);
        break;
    }
     _log->logByteArray(temp, Logger::OPERATION_TYPE::WRITE);
}

bool MainPresenter::ChangeModeRegistersGroup(QByteArray &bytes)
{
    if(bytes.size() == 10)
    {
        char mode = bytes[2] & 0x0F;
        char type_communication = bytes[2] & 0xF0;
        char speed = bytes[3];
        quint16 frequency_ = bytes[8] <<8;
        frequency_ |= bytes[7];
        bool invers = bytes[9] & 0x01;
        bool compress = bytes[9] & 0xf0;

        _device->OpMode()->setMode((OperationMode::Mode)mode);
        _device->OpMode()->setCommunicationType((OperationMode::CommunicationType)type_communication);
        _device->OpMode()->setSpeed((OperationMode::Speed)speed);
        _device->OpMode()->setFrequency(frequency_);
        _device->OpMode()->setInversion(invers);
        _device->OpMode()->setCompression(compress);

        emit updateMode(mode, type_communication, speed, frequency_, invers, compress);

        return true;
    }
    else
    {
        return false;
    }
}

bool MainPresenter::ChangeSubscriberRegistersGroup(QByteArray &bytes)
{
    QList<subscriber*> subs = _device->getListSubscribers();

    if(bytes.size() == 14)
    {
        for(int i=0; i< subs.size(); i++)
        {
            subscriber *sub = subs[i];
            char id_sub = bytes[i*3 + 2];
            char num_channel = bytes[i*3 + 3];
            bool autocall = bytes[i*3 + 4] & 0x01;
            bool support_connect = bytes[i*3 + 4] & 0x10;

            sub->setId(id_sub);
            sub->setNumberChannel(num_channel);
            sub->setAutoCall(autocall);
            sub->setSupportConnection(support_connect);
        }
        emit updateSubscribers();
        return true;
    }
    else
    {
        return false;
    }
}


