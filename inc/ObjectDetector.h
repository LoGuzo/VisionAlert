#ifndef OBJECTDETECTOR_H
#define OBJECTDETECTOR_H
#include <opencv2/opencv.hpp>

using namespace std;

class ObjectDetector{
public:
    bool loadModel(const string& path);
    vector<cv::Rect> detect(const cv::Mat& frame);

private:
    cv::CascadeClassifier classifier;
};
#endif