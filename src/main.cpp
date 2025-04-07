#include "opencv2/opencv.hpp"

#include <iostream>
#include "CameraManager.h"

using namespace std;

int main(int arg, char** argu) {
	CameraManager cam;
	if(!cam.open()){
		cerr<<"Error : Cannot open camera."<<std::endl;
		return 1;
	}

	cv::CascadeClassifier face_cascade;
	if(!face_cascade.load("../assets/haarcascade_frontalface_default.xml")){
		cerr<<"Error"<<endl;
		return 1;
	}

	cv::Mat frame, gray;
	while(true){
		frame = cam.getFrame();
		if(frame.empty()) break;

		cv::cvtColor(frame,gray,cv::COLOR_BGR2GRAY);
		vector<cv::Rect>faces;
		face_cascade.detectMultiScale(gray, faces);

		for(const auto& face : faces){
			cv::rectangle(frame, face,cv::Scalar(0,255,0),2);
		}

		cv::imshow("SmartVision - Object Detection", frame);
		if(cv::waitKey(10) == 27) break; //esc 키 누르면 종료
	}
	cam.release();
	cv::destroyAllWindows();

	return 0;
}