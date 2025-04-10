#include <opencv2/opencv.hpp>
#include "opencv/CameraManager.h"

bool CameraManager::open(int cameraindex){
    cap.open(cameraindex);
    return cap.isOpened();
}

cv::Mat CameraManager::getFrame(){
    cv::Mat frame;
    cap>>frame;
    return frame;
}

void CameraManager::release(){
    cap.release();
}