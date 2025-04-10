#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "opencv/CameraManager.h"
#include "opencv/DetectionManager.h"
#include "opencv/ObjectDetector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void                processFrame();
    void                onSensitivitySliderChanged(int value);
    void                logEvent(const QString& message, const cv::Rect& rect);
    
private:
    Ui::MainWindow      *ui;
    CameraManager       cam;
    DetectionManager    detectionManager;
    QTimer              *timer;
};

#endif