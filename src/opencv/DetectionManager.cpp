// DetectionManager.cpp
#include "opencv/DetectionManager.h"

DetectionManager::DetectionManager() : motionOngoing(false) {}

double DetectionManager::computeIOU(const cv::Rect& a, const cv::Rect& b) {
    int x1 = std::max(a.x, b.x);
    int y1 = std::max(a.y, b.y);
    int x2 = std::min(a.x + a.width, b.x + b.width);
    int y2 = std::min(a.y + a.height, b.y + b.height);

    int interArea = std::max(0, x2 - x1) * std::max(0, y2 - y1);
    int unionArea = a.area() + b.area() - interArea;
    return unionArea > 0 ? (double)interArea / unionArea : 0.0;
}

std::vector<cv::Rect> DetectionManager::detectAbnormalBehavior(const cv::Mat& frame) {
    std::vector<cv::Rect> abnormalRects;
    auto motions = motionDetector.detect(frame);
    auto now = std::chrono::steady_clock::now();

    if (!motions.empty()) {
        if (!motionOngoing) {
            lastMotionTime = now;
            motionOngoing = true;
        } else {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastMotionTime).count();
            if (duration > 2) {  // 이상행동 지속 시간 (기존 조건 유지)
                for (const auto& rect : motions) {
                    bool shouldLog = true;

                    // 최근에 기록된 객체와 비교 (IOU + 시간 기준)
                    for (const auto& [loggedRect, loggedTime] : recentlyLogged) {
                        double iou = computeIOU(rect, loggedRect);
                        if (iou > 0.5) {
                            if (std::chrono::duration_cast<std::chrono::seconds>(now - loggedTime).count() < suppressSeconds) {
                                shouldLog = false;
                                break;
                            }
                        }
                    }

                    if (shouldLog) {
                        abnormalRects.push_back(rect);
                        recentlyLogged.push_back({ rect, now });
                    }
                }
            }
        }
    } else {
        motionOngoing = false;
    }

    // 오래된 로그 제거 (선택적 유지 관리)
    recentlyLogged.erase(
        std::remove_if(recentlyLogged.begin(), recentlyLogged.end(),
            [&](const auto& pair) {
                return std::chrono::duration_cast<std::chrono::seconds>(now - pair.second).count() > suppressSeconds;
            }),
        recentlyLogged.end()
    );

    return abnormalRects;
}

void DetectionManager::setThreshold(int t) {
    motionDetector.setThreshold(t);  // 내부 MotionDetector에 전달
}

void DetectionManager::setMinArea(int a) {
    motionDetector.setMinArea(a);
}