#ifndef DETECTIONMANAGER_H
#define DETECTIONMANAGER_H
#include <opencv2/opencv.hpp>
#include <vector>
#include "opencv/ObjectDetector.h"

class DetectionManager {
public:
    DetectionManager();

public:
    std::vector<cv::Rect>   detectNewObjects(const cv::Mat& frame);
    bool                    loadModel(const std::string& path);

    void                    setSensetivity(const double& val);
    double                  getSensetivity(){return detector.getSensetivity();}

private:
    bool                    isNewObject(const cv::Rect& rect);

private:
    ObjectDetector          detector;
    std::vector<cv::Rect>   prevRects;
    double                  scaleFactor;
};

#endif