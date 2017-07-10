#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QObject>
#include <QPixmap>

class QTcpServer;
class QTcpSocket;
class SocketServer : public QObject
{
    Q_OBJECT
public:
    explicit SocketServer(QObject *parent = 0);
    void startServer();
private:
    QTcpServer *mServer;
    QTcpSocket *mSocket;

    quint64 mRecedSize;
    quint32 mSize;
    QByteArray mData;

    void acceptConnect();
    void readData();
    void reset();
signals:
    void onReceived(QPixmap pixmap);

};

#endif // SOCKETSERVER_H
