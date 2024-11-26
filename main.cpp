#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


using namespace std;
using namespace cv;

// 鼠标回调函数
void mouseCallback(int event, int x, int y, int, void* param) {
    if (event == EVENT_LBUTTONDOWN) { // 检测左键点击事件    //EVENT_RBUTTONDOWN左键点击事件
        Mat* frame = reinterpret_cast<Mat*>(param);
        if (x >= 0 && x < frame->cols && y >= 0 && y < frame->rows) {
            Vec3b bgr = frame->at<Vec3b>(Point(x, y)); // 获取BGR值
            //cout << "BGR: (" << (int)bgr[0] << ", " << (int)bgr[1] << ", " << (int)bgr[2] << ")" << endl;

            // 转换为HSV并输出
            Mat hsv;
            cvtColor(*frame, hsv, COLOR_BGR2HSV);
            Vec3b hsvValue = hsv.at<Vec3b>(Point(x, y));
            //cout << "HSV: (" << (int)hsvValue[0] << ", " << (int)hsvValue[1] << ", " << (int)hsvValue[2] << ")" << endl;

            cout << Point(x, y) << endl;
            // cout << x*x + y*y << endl;
        }
    }
}


int main() {
    // 打开视频文件
    cv::VideoCapture cap("前哨站.avi");

    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    int total_frames = cap.get(cv::CAP_PROP_FRAME_COUNT); // 获取视频的总帧数

    // 创建一个窗口
    cv::namedWindow("Video", cv::WINDOW_NORMAL);

    // 创建滑动条，滑动条的名字为 "Position"，初始值为 0，最大值为视频的总帧数
    int slider_position = 0;
    cv::createTrackbar("Position", "Video", &slider_position, total_frames);

    while (true) {
        // 根据滑动条的值跳转到指定的帧
        cap.set(cv::CAP_PROP_POS_FRAMES, slider_position);

        cv::Mat frame;
        cap >> frame; // 获取当前帧

        if (frame.empty()) {
            break; // 如果没有更多帧，退出
        }

        // 显示当前帧
        cv::imshow("Video", frame);
        setMouseCallback("Video", mouseCallback, &frame);
        // 按 'q' 键退出
        char c = cv::waitKey(30);
        if (c == 'q' || c == 27) {
            break;
        }

        // 更新滑动条的位置
        slider_position = cv::getTrackbarPos("Position", "Video");
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

// #include <opencv2/opencv.hpp>
// #include <vector>

// // 定义一个全局变量来存储轮廓的最小外接矩形面积
// int minRectArea = 0;

// // 滑动条回调函数，用于获取阈值
// void onTrackbar(int, void*) {
//     // 不做任何事，只是更新最小外接矩形的计算
// }

// // 鼠标回调函数，点击时获取鼠标位置，进行轮廓检测
// void mouseCallback(int event, int x, int y, int, void* userdata) {
//     if (event == cv::EVENT_LBUTTONDOWN) {
//         cv::Mat frame = *((cv::Mat*)userdata);
//         cv::Mat gray, thresh;
        
//         // 转换为灰度图
//         cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        
//         // 应用滑动条设置的阈值
//         int threshVal = cv::getTrackbarPos("Threshold", "Video");
//         cv::threshold(gray, thresh, threshVal, 255, cv::THRESH_BINARY);

//         // 查找轮廓
//         std::vector<std::vector<cv::Point>> contours;
//         cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

//         // 计算最小外接矩形
//         minRectArea = 0;
//         for (size_t i = 0; i < contours.size(); i++) {
//             if (contours[i].size() >= 5) { // 确保轮廓有足够的点来计算最小外接矩形
//                 cv::RotatedRect minRect = cv::minAreaRect(contours[i]);
//                 minRectArea = std::max(minRectArea, (int)(minRect.size.width * minRect.size.height));
//             }
//         }

//         // 显示计算的最小外接矩形面积
//         std::cout << "Min Rect Area: " << minRectArea << std::endl;
//     }
// }

// int main() {
//     // 打开视频文件或摄像头
//     cv::VideoCapture cap("near.avi");
//     if (!cap.isOpened()) {
//         std::cerr << "无法打开视频文件!" << std::endl;
//         return -1;
//     }

//     cv::Mat frame;
//     cv::namedWindow("Video", cv::WINDOW_NORMAL);

//     // 设置滑动条
//     cv::createTrackbar("Threshold", "Video", nullptr, 255, onTrackbar);

//     // 设置鼠标回调函数
//     cv::setMouseCallback("Video", mouseCallback, &frame);

//     while (true) {
//         cap >> frame;
//         if (frame.empty()) break;

//         // 显示当前帧
//         cv::imshow("Video", frame);

//         // 按 'q' 键退出
//         if (cv::waitKey(30) == 'q') break;
//     }

//     cap.release();
//     cv::destroyAllWindows();
//     return 0;
// }
