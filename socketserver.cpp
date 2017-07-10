#include "socketserver.h"
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
SocketServer::SocketServer(QObject *parent) :
    QObject(parent)
{
    reset();
    mServer = new QTcpServer(this);
}

void SocketServer::startServer()
{
    if(!mServer->listen(QHostAddress::Any,10000)){
        qDebug() << "failed";
    }else{
         qDebug() << "success";
       connect(mServer,&QTcpServer::newConnection,this,&SocketServer::acceptConnect);
    }
}

void SocketServer::acceptConnect()
{
    qDebug() << "connect" <<endl;
    mSocket = mServer->nextPendingConnection();
    connect(mSocket,&QTcpSocket::readyRead,this,&SocketServer::readData);
}

void SocketServer::readData()
{
    if(mSize == 0 && mRecedSize == 0){
        if(mSocket->bytesAvailable() < sizeof(quint32)){
            return;
        }
        QDataStream stream(mSocket);
        stream >> mSize;
        qDebug() << "size = " << mSize << endl;
    }
    if(mRecedSize < mSize){
        int diff = mSize - mRecedSize;
        QByteArray temp = mSocket->read(diff);
        mRecedSize +=temp.size();
        mData.append(temp);
    }
    if(mRecedSize >= mSize ){
        qDebug() << "receiveSize = " << mRecedSize << endl;
        QPixmap map;
        map.loadFromData(mData);
        reset();
        emit onReceived(map);
        char temp[] = {0xFF};
        mSocket->write(temp,sizeof(temp));
        mSocket->waitForBytesWritten();
    }
}

void SocketServer::reset()
{
    mSize = 0;
    mRecedSize = 0;
    mData.resize(0);
}
