#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "onencv/CameraManager.h"
#include "onencv/ObjectDetector.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //virtual void forceVTable() {};

private slots:
    void processFrame();

private:
    CameraManager   cam;
    ObjectDetector  detector;
    QTimer          *timer;
    QLabel          *videoLabel;
};

#endif