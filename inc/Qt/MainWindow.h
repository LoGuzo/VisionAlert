#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "onencv/CameraManager.h"
#include "onencv/ObjectDetector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void processFrame();

private:
    Ui::MainWindow *ui;
    CameraManager   cam;
    ObjectDetector  detector;
    QTimer          *timer;
    QLabel          *videoLabel;
};

#endif