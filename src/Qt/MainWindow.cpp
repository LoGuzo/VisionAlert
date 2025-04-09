// MainWindow.cpp
#include "Qt/MainWindow.h"
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include "ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
    , videoLabel(new QLabel(this)) 
{
    ui->setupUi(this);
    setWindowTitle("VisionAlert - 얼굴 인식");
    ui->sense_slider->setRange(1,10);
    ui->sense_slider->setValue(5);

    if (!cam.open()) {
        ui->video_label->setText("카메라를 열 수 없습니다.");
        return;
    }

    if (!detector.loadModel("../assets/haarcascade_frontalface_default.xml")) {
        ui->video_label->setText("모델 로딩 실패.");
        return;
    }

    connect(timer, &QTimer::timeout, this, &MainWindow::processFrame);
    timer->start(30); // 약 33fps
}

MainWindow::~MainWindow() {
    cam.release();
}

void MainWindow::processFrame() {
    cv::Mat frame = cam.getFrame();
    if (frame.empty()) return;

    auto faces = detector.detect(frame);
    for (const auto& face : faces) {
        cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
    }

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->video_label->setPixmap(QPixmap::fromImage(img).scaled(ui->video_label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
