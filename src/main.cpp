#include "opencv2/opencv.hpp"

#include <iostream>
#include "CameraManager.h"
#include "ObjectDetector.h"

using namespace std;

int main(int arg, char** argu) {
	CameraManager cam;
	if(!cam.open()){
		cerr<<"Error : Cannot open camera."<<std::endl;
		return 1;
	}

	ObjectDetector detector;
	if(!detector.loadModel("../assets/haarcascade_frontalface_default.xml")){
		cerr<<"Error"<<endl;
		return 1;
	}

	cv::Mat frame;
	while(true){
		frame = cam.getFrame();
		if(frame.empty()) break;

		auto objects = detector.detect(frame);

		for(const auto& object : objects){
			cv::rectangle(frame, object, cv::Scalar(0, 255, 0), 2);
		}

		cv::imshow("SmartVision - Object Detection", frame);
		if(cv::waitKey(10) == 27) break; //esc 키 누르면 종료
	}
	cam.release();
	cv::destroyAllWindows();

	return 0;
}