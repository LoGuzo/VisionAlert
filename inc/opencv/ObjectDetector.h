#ifndef OBJECTDETECTOR_H
#define OBJECTDETECTOR_H
#include <opencv2/opencv.hpp>

using namespace std;

class ObjectDetector{
public:
    ObjectDetector();

public:
    bool                    loadModel(const string& path);
    vector<cv::Rect>        detect(const cv::Mat& frame);

    void                    setSensetivity(const double& val);
    double                  getSensetivity(){return scaleFactor;}

private:
    cv::CascadeClassifier   classifier;
    double                  scaleFactor;
};
#endif