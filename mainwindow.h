#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QMetaEnum>
#include "domain/device.h"
#include "byteconverter.h"
#include "subscriberwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDevice(Device *value);

public slots:
    void updateModeWidgets(char mode,
                           char communictionType,
                           char speed,
                           quint16 frequency,
                           bool inverse,
                           bool compress);

    void updateSubscribers();

private slots:

    void on_FrequencySbx_valueChanged(int arg1);

    void on_inversionCbx_clicked(bool checked);

    void on_compressionCbx_clicked(bool checked);

    void on_modeCmbx_activated(const QString &arg1);

    void on_speedCmbx_activated(const QString &arg1);

    void on_ComunicationTypeCmbx_activated(const QString &arg1);

    void on_isValidModemcbx_clicked(bool checked);

    void on_isInfoAvaliableCbx_clicked(bool checked);

    void on_levelSignalSpinbox_valueChanged(int arg1);

    void on_signalCmbx_currentIndexChanged(const QString &arg1);

    void on_connectionCmbx_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStringListModel *strModel;
    QMetaEnum enumType;
    Device* device;
    QMap<QString, OperationMode::CommunicationType> *comTypeOptions;
    QMap<QString, OperationMode::Mode> *modeOptions;
    QMap<QString, OperationMode::Speed> *speedOptions;
    QMap<StateDevice::Connection, QString> *connectionOptions;
    QMap<StateDevice::Signal, QString> *signalOptions;

    QList<SubscriberWidget*> _listSubWidgets;


    QString boolToWord(bool b);
    bool static compareNumbers(const QString &s1, const QString &s2);

};

#endif // MAINWINDOW_H
