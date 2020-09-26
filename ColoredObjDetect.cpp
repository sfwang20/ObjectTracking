#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture inputVideo(0);

    if (!inputVideo.isOpened())
    {
        cerr << "Failed to open the webcam!" << endl;
        return EXIT_FAILURE;
    }

    Mat frame, hsvImage, mask, outputImage;
    char ch;

    while (true)
    {
        outputImage = Scalar(0, 0, 0);

        if (!inputVideo.read(frame)) break;

        resize(frame, frame, Size(), 0.5, 0.5, INTER_AREA);

        cvtColor(frame, hsvImage, COLOR_BGR2HSV);

        // blue
        Scalar lowerLimit = Scalar(60, 100, 100);
        Scalar upperLimit = Scalar(180, 255, 255);

        // get only blue color
        inRange(hsvImage, lowerLimit, upperLimit, mask);

        bitwise_and(frame, frame, outputImage, mask = mask);

        medianBlur(outputImage, outputImage, 5);
 
        imshow("Input", frame);
        imshow("Output", outputImage);

        ch = waitKey(30);
        if (ch == 27) break;        
    }

    return EXIT_SUCCESS;
}
