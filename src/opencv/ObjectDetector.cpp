#include "opencv/ObjectDetector.h"


ObjectDetector::ObjectDetector()
    : scaleFactor(1.1f) 
{
}

bool ObjectDetector::loadModel(const string& path){
    return classifier.load(path);
}

vector<cv::Rect> ObjectDetector::detect(const cv::Mat& frame){
    vector<cv::Rect> objects;
    cv::Mat gray;
    cv::cvtColor(frame, gray,cv::COLOR_BGR2GRAY);
    classifier.detectMultiScale(gray, objects, scaleFactor);
    return objects;
}

void ObjectDetector::setSensetivity(const double& val){
    scaleFactor = val;
}