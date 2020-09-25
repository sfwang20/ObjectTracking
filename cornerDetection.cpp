#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace cv;
using namespace std;

Mat goodFeaturesTrack(Mat, Mat, int, RNG);
Mat cornerHarrisTrack(Mat, Mat, int, RNG);

int main(int argc, char* argv[])
{
    int numCorners = 30;

    RNG rng(12345);
    string windowName = "Feature points";

    Mat frame, frameGray;

    char ch;
    float scalingFactor = 0.25;

    const string& fileName = "river.MOV";
    VideoCapture inputVideo(fileName);

    if (!inputVideo.isOpened()) {
        cerr << "Failed to open the video." << endl;
        return EXIT_FAILURE;
    }

    // Video output
    const string video_name = "output.mp4";
    int video_FourCC = static_cast<int>(inputVideo.get(CAP_PROP_FOURCC));     // Get Codec Type
    int video_fps = inputVideo.get(CAP_PROP_FPS);
    Size video_size = Size(int(inputVideo.get(CAP_PROP_FRAME_WIDTH)*0.5),
                           int(inputVideo.get(CAP_PROP_FRAME_HEIGHT))*0.25);

    VideoWriter outputVideo;
    outputVideo.open(video_name, video_FourCC, video_fps, video_size, true);

    
    while (true) {
        if (!inputVideo.read(frame)) break;
        
        resize(frame, frame, Size(), scalingFactor, scalingFactor, INTER_AREA);
        cvtColor(frame, frameGray, COLOR_BGR2GRAY);

        Mat frameGoodFeatures = goodFeaturesTrack(frame, frameGray, numCorners, rng);
        Mat frameHarris = cornerHarrisTrack(frame, frameGray, numCorners, rng);

        // stack two frames
        Mat frameShow;
        hconcat(frameGoodFeatures, frameHarris, frameShow);

        outputVideo.write(frameShow);
        imshow(windowName, frameShow);

        ch = waitKey(1);
        if (ch == 27) {
            break;
        }
    }

    inputVideo.release();
    destroyAllWindows();

    return EXIT_SUCCESS;
}


Mat goodFeaturesTrack(Mat frame, Mat frameGray, int numCorners, RNG rng) {

    // Init the params for Shi-Tomasi algorithm
    vector<Point2f> corners;
    double qualityThreshold = 0.02;
    double minDist = 15;
    int blockSize = 5;
    bool useHarrisDetector = false;
    double k = 0.05;

    Mat frameCopy = frame.clone();

    // corner detection
    goodFeaturesToTrack(frameGray, corners, numCorners, qualityThreshold, minDist,
                        Mat(), blockSize, useHarrisDetector, k);

    // Draw the detected corners by circles
    for (size_t i = 0; i < corners.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        circle(frameCopy, corners[i], 8, color, 2, 2, 0);
    }

    return frameCopy;
}


Mat cornerHarrisTrack(Mat frame, Mat frameGray, int numCorners, RNG rng) {

    // Init params
    Mat dst, dst_norm, dst_norm_scaled;
    int apertureSize = 5;
    double k = 0.04;
    int blockSize = 2;
    int thresh = 200;    
    dst = Mat::zeros(frame.size(), CV_32FC1);

    // Detecting corners
    cornerHarris(frameGray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);

    // Draw the detected corners by circles
    for (int j = 0; j < dst_norm.rows; j++)
    {
        for (int i = 0; i < dst_norm.cols; i++)
        {
            if ((int)dst_norm.at<float>(j, i) > thresh)
            {
                Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
                circle(frame, Point(i, j), 8, color, 2, 8, 0);
            }
        }
    }

    return frame;
}