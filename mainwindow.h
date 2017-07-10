#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class SocketServer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    SocketServer *mServer;
};

#endif // MAINWINDOW_H
