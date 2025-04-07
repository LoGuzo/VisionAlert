#ifndef CAMERAMANGER_H
#define CAMERAMANGER_H
#include <opencv2/opencv.hpp>

class CameraManager{
public:
    bool open(int cameraindex = 0);
    cv::Mat getFrame();
    void release();

private:
    cv::VideoCapture cap;
};

#endif