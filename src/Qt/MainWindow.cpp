// MainWindow.cpp
#include "Qt/MainWindow.h"
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), timer(new QTimer(this)), videoLabel(new QLabel(this)) 
{
    setWindowTitle("VisionAlert - 얼굴 인식");
    resize(800, 600);  // 메인 창 자체 크기 키우기

    videoLabel = new QLabel(this);
    videoLabel->setMinimumSize(640, 480);
    videoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(videoLabel);
    setCentralWidget(centralWidget);

    if (!cam.open()) {
        videoLabel->setText("카메라를 열 수 없습니다.");
        return;
    }

    if (!detector.loadModel("../assets/haarcascade_frontalface_default.xml")) {
        videoLabel->setText("모델 로딩 실패.");
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
    videoLabel->setPixmap(QPixmap::fromImage(img).scaled(videoLabel->size(), Qt::KeepAspectRatio));
}
