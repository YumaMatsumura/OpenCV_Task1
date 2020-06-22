/*
 * チャレンジ課題
 *
 * 動作確認
 * OS: Windows 8
 * OpenCV version: 4.3.0
 * OpenCV contrib version: 4.3.0
 */

#include<opencv2/aruco.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

//MarkerのIDを表示
void displayMarkerIds(cv::OutputArray in) {
	std::vector<cv::Mat> ids;
	in.getMatVector(ids);
	std::cout << "Marker IDs: " << std::endl;
	for (auto ids : ids) {
		std::cout << ids << std::endl;
	}
}

int main(int argc, const char* argv[]) {
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
	cv::Mat frame;
	cv::VideoCapture cap(0);
	int tmp;

	if (!cap.isOpened()) {
		return -1;
	}

	while (cap.read(frame)) {
		std::vector<int> ids;
		std::vector<std::vector<cv::Point2f>> corners;

		cv::aruco::detectMarkers(frame, dictionary, corners, ids);
		if (ids.size() > 0) {
			cv::aruco::drawDetectedMarkers(frame, corners, ids);
			//idを昇順へ
			for (int i = 0; i < ids.size(); i++) {
				for (int j = i + 1; j < ids.size(); j++) {
					if (ids[i] > ids[j]) {
						tmp = ids[i];
						ids[i] = ids[j];
						ids[j] = tmp;
					}
				}
			}
			displayMarkerIds(ids);
		}

		cv::imshow("cam", frame);

		const int key = cv::waitKey(1);
		if (key == 'q') {
			break;
		}
	}
	cv::destroyAllWindows();

	return 0;
}