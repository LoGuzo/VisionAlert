// MainWindow.cpp
#include "Qt/MainWindow.h"
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QTime>
#include "ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    setWindowTitle("VisionAlert - 얼굴 인식");
    ui->sense_slider->setRange(1,10);
    ui->sense_slider->setValue(5);
    if (!cam.open()) {
        ui->video_label->setText("카메라를 열 수 없습니다.");
        return;
    }

    if (!detectionManager.loadModel("../assets/haarcascade_frontalface_default.xml")) {
        ui->video_label->setText("모델 로딩 실패.");
        return;
    }
    onSensitivitySliderChanged(ui->sense_slider->value());
    connect(ui->sense_slider, &QSlider::valueChanged, this, &MainWindow::onSensitivitySliderChanged);
    connect(timer, &QTimer::timeout, this, &MainWindow::processFrame);
    timer->start(30); // 약 33fps
}

MainWindow::~MainWindow() {
    cam.release();
    delete ui;
}

void MainWindow::processFrame() {
    cv::Mat frame = cam.getFrame();
    if (frame.empty()) return;

    auto faces = detectionManager.detectNewObjects(frame);
    for (const auto& face : faces) {
        cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        logEvent(QStringLiteral("새 객체 감지"), face);
    }

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->video_label->setPixmap(QPixmap::fromImage(img).scaled(ui->video_label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::onSensitivitySliderChanged(int value){
    double scale = 1.01 + ((value - 1) / 9.0) * 0.49;
    detectionManager.setSensetivity(scale);
    
    ui->sense_label->setText(QString::asprintf("감도 : %.2lf", detectionManager.getSensetivity()));
}

void MainWindow::logEvent(const QString& message, const cv::Rect& rect) {
    // QString timeStr = QTime::currentTime().toString(QStringLiteral("hh:mm:ss"));

    // QString infoStr = QStringLiteral("%1 (%2, %3, %4×%5)")
    //                 .arg(message)
    //                 .arg(rect.x)
    //                 .arg(rect.y)
    //                 .arg(rect.width)
    //                 .arg(rect.height);

    int currentRow = ui->log_table->rowCount();
    int currentCol = ui->log_table->columnCount();
    // // 시간 행
    ui->log_table->insertColumn(currentCol);
    ui->log_table->setItem(0, currentCol, new QTableWidgetItem("time"));

    // // 내용 행
    ui->log_table->setItem(1, currentCol, new QTableWidgetItem("info"));
}