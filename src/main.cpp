#include <QApplication>
#include "../inc/Qt/MainWindow.h"

#include <opencv2/opencv.hpp>


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}