// MotionDetector.h
#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

#include <opencv2/opencv.hpp>

// MotionDetector.h
class MotionDetector {
    public:
        MotionDetector();
        void setThreshold(int t);      // 감도 설정용 함수
        void setMinArea(int area);     // 작은 노이즈 거르기
    
        std::vector<cv::Rect> detect(const cv::Mat& frame);
    
    private:
        int thresholdValue;
        int minArea;
    
        cv::Mat prevGray;
    };
    

#endif // MOTIONDETECTOR_H
