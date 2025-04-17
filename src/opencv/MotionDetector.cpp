// MotionDetector.cpp
#include "opencv/MotionDetector.h"

MotionDetector::MotionDetector()
    : thresholdValue(25)
    , minArea(500)
{

}

void MotionDetector::setThreshold(int t) {
    thresholdValue = t;
}
void MotionDetector::setMinArea(int area) {
    minArea = area;
}

std::vector<cv::Rect> MotionDetector::detect(const cv::Mat& frame) {
    std::vector<cv::Rect> motionRects;
    cv::Mat gray, diff, thresh;

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    if (!prevGray.empty()) {
        cv::absdiff(prevGray, gray, diff);
        cv::threshold(diff, thresh, thresholdValue, 255, cv::THRESH_BINARY);
        cv::dilate(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 2);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        for (const auto& contour : contours) {
            if (cv::contourArea(contour) > minArea) {
                motionRects.push_back(cv::boundingRect(contour));
            }
        }
    }
    gray.copyTo(prevGray);
    return motionRects;
}
