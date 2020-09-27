#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

void drawOpticalFlow(const Mat&, Mat&);

int main(int, char** argv)
{
    VideoCapture inputVideo("data.mp4");

    if (!inputVideo.isOpened())
    {
        cout << "Failed to open the file!" << endl;
        return EXIT_FAILURE;
    }

    Mat next, prev, flow, flowGray, frame;
    string windowName = "Farneback Flow";
    namedWindow(windowName);

    while (true)
    {
        if (!inputVideo.read(frame)) break;

        cvtColor(frame, next, COLOR_BGR2GRAY);

        if (prev.data)
        {
            // Init params
            float pyrScale = 0.5;
            int numLevels = 3;
            int windowSize = 15;
            int numIterations = 3;
            int neighborhoodSize = 5;
            float stdDeviation = 1.2;

            // Calculate optical flow map by Farneback algorithm
            calcOpticalFlowFarneback(prev, next, flow,
                                     pyrScale, numLevels, windowSize, 
                                     numIterations, neighborhoodSize, stdDeviation, 
                                     cv::MOTION_TRANSLATION);

            cvtColor(prev, flowGray, COLOR_GRAY2BGR);

            drawOpticalFlow(flow, flowGray);

            imshow(windowName, flowGray);
        }

        char ch = waitKey(1);
        if (ch == 27) break;

        std::swap(prev, next);
    }

    return EXIT_SUCCESS;
}


void drawOpticalFlow(const Mat& flow, Mat& flowGray)
{
    int step = 16;

    for (int y = 0; y < flowGray.rows; y += step)
    {
        for (int x = 0; x < flowGray.cols; x += step)
        {
            // indicate the motion vectors
            Point2f pt = flow.at<Point2f>(y, x);
            line(flowGray, Point(x, y), Point(cvRound(x + pt.x), cvRound(y + pt.y)), Scalar(0, 255, 0));
        }
    }
}
