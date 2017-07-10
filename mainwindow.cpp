#include "mainwindow.h"
#include "socketserver.h"
#include "display.h"

#include <wiringPi.h>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    wiringPiSetup();
    QLabel *label = new QLabel;
    Display *display = new Display(0x3C);
    display->update();
    setCentralWidget(label);
    mServer = new SocketServer(this);
    mServer->startServer();
    connect(mServer,&SocketServer::onReceived,this,[=](QPixmap pixmap){
        label->setPixmap(pixmap);
        display->drawImg(pixmap);
        display->update();
    });
}

MainWindow::~MainWindow()
{
}
