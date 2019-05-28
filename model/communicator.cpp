#include "communicator.h"

TCommunicator::TCommunicator(TCommParams& pars, QObject *parent) : QUdpSocket(parent)
{
    params = pars;
    ready = bind(params.rHost, params.rPort, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    if (ready) connect(this,SIGNAL(readyRead()),this,SLOT(recieve()));
     quint64 size = pendingDatagramSize();
    QByteArray msg(size,'\0');
    readDatagram(0, size);
}

bool TCommunicator::isReady()
{
    return ready;
}

void TCommunicator::send(QByteArray msg)
{
    if (ready)
    {
        writeDatagram(msg, params.sHost, params.sPort);
    }
}

void TCommunicator::recieve()
{
    if (hasPendingDatagrams())
    {
        quint64 size = pendingDatagramSize();
        QByteArray msg(size,'\0');
        readDatagram(msg.data(), size);
        std::cout << "recieve\n" << msg.data();
        emit recieved(msg);

    }

}

