#ifndef GBL_H
#define GBL_H

#include <QHostAddress>

#define REQUEST_COMPLETED 0x40
#define REQUEST_FAILED 0x41
#define WRITING_REGISTERS 0x30
#define READING_REGISTERS 0x31

#define ALL_REGISTERS 0x00
#define REGISTERS_GROUP_1 0x01
#define REGISTERS_GROUP_2 0x02
#define REGISTERS_GROUP_3 0x03

class gbl
{
public:
    static const int subscriber_number;
    static const int portListening;
    static const int portWriting;
    static const QHostAddress hostAddress;
    static const QString LogFileName;
};

#endif // GBL_H
