#include "CameraManager.h"
#include <opencv2/opencv.hpp>


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