// DetectionManager.h
#ifndef DETECTIONMANAGER_H
#define DETECTIONMANAGER_H

#include "MotionDetector.h"
#include <chrono>

class DetectionManager {
public:
    DetectionManager();

public:
    std::vector<cv::Rect> detectAbnormalBehavior(const cv::Mat& frame);
    void setThreshold(int t);
    void setMinArea(int a);

private:
    MotionDetector motionDetector;

    std::chrono::steady_clock::time_point lastMotionTime;
    bool motionOngoing;

    std::vector<std::pair<cv::Rect, std::chrono::steady_clock::time_point>> recentlyLogged;
    int suppressSeconds = 5;

    double computeIOU(const cv::Rect& a, const cv::Rect& b);
};

#endif // DETECTIONMANAGER_H
