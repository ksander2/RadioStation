#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>

class Logger : public QObject
{
    Q_OBJECT
    Q_ENUMS(OPERATION_TYPE)
public:
    static Logger *Instance();
    void startLogging();
    void write(QString str);

    ~Logger();

    enum OPERATION_TYPE
    {
       READ,
       WRITE
    };

    void logByteArray(QByteArray &bytes, const Logger::OPERATION_TYPE &type);

signals:

public slots:

private:
    static Logger *_instance;

    explicit Logger(QObject *parent = 0);
    Logger(const Logger& root);
    Logger& operator=(const Logger&);
    QFile *_logfile;
};

#endif // LOGGER_H
