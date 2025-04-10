#include "opencv/DetectionManager.h"

DetectionManager::DetectionManager(){}

bool DetectionManager::loadModel(const std::string& path) {
    return detector.loadModel(path);
}

void DetectionManager::setSensetivity(const double& val){
    detector.setSensetivity(val);
}

std::vector<cv::Rect> DetectionManager::detectNewObjects(const cv::Mat& frame) {
    std::vector<cv::Rect> currentRects = detector.detect(frame);
    std::vector<cv::Rect> newRects;

    for (const auto& rect : currentRects) {
        if (isNewObject(rect)) {
            newRects.push_back(rect);
        }
    }

    prevRects = currentRects;
    return newRects;
}

bool DetectionManager::isNewObject(const cv::Rect& rect) {
    for (const auto& prev : prevRects) {
        // 단순한 위치 + 크기 비교로 유사 객체 판단
        int dx = rect.x - prev.x;
        int dy = rect.y - prev.y;
        int dw = rect.width - prev.width;
        int dh = rect.height - prev.height;

        if (std::abs(dx) < 30 && std::abs(dy) < 30 &&
            std::abs(dw) < 20 && std::abs(dh) < 20) {
            return false; // 비슷한 게 이미 있었다면 새 객체 아님
        }
    }
    return true;
}
