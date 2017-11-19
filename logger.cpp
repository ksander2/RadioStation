#include "logger.h"
#include <QTextStream>
#include <QDateTime>
#include "gbl.h"

Logger::Logger(QObject *parent) : QObject(parent)
{

}

Logger* Logger::_instance=0;

Logger *Logger::Instance()
{
    if (!_instance) {
        _instance = new Logger();
    };
    return _instance;
}

void Logger::startLogging()
{
    _logfile = new QFile(gbl::LogFileName);
    _logfile->open(QFile::Append | QFile::Text | QFile::ReadWrite);
}

void Logger::write(QString str)
{
    QTextStream out(_logfile);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    out << str << endl;
}

Logger::~Logger()
{
    _logfile->close();
    delete _logfile;
}

void Logger::logByteArray(QByteArray &bytes, const OPERATION_TYPE &type)
{
     QTextStream out(_logfile);
     QString str =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
     switch (type) {
     case WRITE:
         str +=" write UDP ";
         break;
     case READ:
         str +=" read UDP ";
         break;
     default:
         break;
     }

     for (int var = 0; var < bytes.size(); var++)
     {
         uint8_t c   =  bytes[var];
         QString temp = QString::number(c,16);
         str += " " +temp;
     }

     out << str << endl;
}

