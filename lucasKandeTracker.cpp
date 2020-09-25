#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

bool pointTrackingFlag = false;
Point2f currentPoint;

void onMouse(int event, int x, int y, int, void*);

int main(int argc, char* argv[])
{
    string file_name = "landing.mov";
    VideoCapture inputVideo(file_name);

    if (!inputVideo.isOpened())
    {
        cerr << "Unable to open the webcam or video." << endl;
        return EXIT_FAILURE;
    }

    TermCriteria terminationCriteria(TermCriteria::COUNT | TermCriteria::EPS, 10, 0.02);

    Size windowSize(25, 25);

    // Maximum number of points want to track
    const int maxNumPoints = 200;

    string windowName = "Lucas Kanade Tracker";
    namedWindow(windowName);
    setMouseCallback(windowName, onMouse, 0);

    Mat prevGrayImage, curGrayImage, image, frame;
    vector<Point2f> trackingPoints[2];

    // Video output
    const string video_name = "output.mp4";
    int video_FourCC = static_cast<int>(inputVideo.get(CAP_PROP_FOURCC));     // Get Codec Type
    int video_fps = inputVideo.get(CAP_PROP_FPS);
    Size video_size = Size(int(inputVideo.get(CAP_PROP_FRAME_WIDTH)),
                           int(inputVideo.get(CAP_PROP_FRAME_HEIGHT)));

    VideoWriter outputVideo;
    outputVideo.open(video_name, video_FourCC, video_fps, video_size, true);

    while (true)
    {   
        if (!inputVideo.read(frame)) break;
        
        frame.copyTo(image);
        //resize(frame, image, Size(0, 0), 0.5, 0.5);          
        cvtColor(image, curGrayImage, COLOR_BGR2GRAY);

        // Check if there are points to track
        if (!trackingPoints[0].empty())
        {
            vector<uchar> statusVector;
            vector<float> errorVector;

            if (prevGrayImage.empty())
            {
                curGrayImage.copyTo(prevGrayImage);
            }

            // Calculate the optical flow using Lucas-Kanade algorithm
            calcOpticalFlowPyrLK(prevGrayImage, curGrayImage, 
                                 trackingPoints[0], trackingPoints[1], 
                                 statusVector, errorVector, windowSize, 3, 
                                 terminationCriteria, 0, 0.001);

            int count = 0;           
            int minDist = 7;

            for (int i = 0; i < trackingPoints[1].size(); i++)
            {
                if (pointTrackingFlag)
                {
                    if (norm(currentPoint - trackingPoints[1][i]) <= minDist)
                    {
                        pointTrackingFlag = false;
                        continue;
                    }
                }

                // Check the status vector
                if (!statusVector[i])
                    continue;

                trackingPoints[1][count++] = trackingPoints[1][i];

                int radius = 16;
                int thickness = 2;
                int lineType = 8;
                circle(image, trackingPoints[1][i], radius, Scalar(0, 0, 255), thickness, lineType);
            }

            trackingPoints[1].resize(count);
        }

        // Refining the location of the feature points
        if (pointTrackingFlag && trackingPoints[1].size() < maxNumPoints)
        {
            vector<Point2f> tempPoints;
            tempPoints.push_back(currentPoint);

            // refine the location of the corners to subpixel accuracy.
            cornerSubPix(curGrayImage, tempPoints, windowSize, Size(-1, -1), terminationCriteria);

            trackingPoints[1].push_back(tempPoints[0]);
            pointTrackingFlag = false;
        }


        outputVideo.write(image);

        imshow(windowName, image);
        
        char ch = waitKey(100);
        if (ch == 27)
            break;

        std::swap(trackingPoints[1], trackingPoints[0]);

        cv::swap(prevGrayImage, curGrayImage);
    }

    inputVideo.release();
    outputVideo.release();

    return EXIT_SUCCESS;
}


void onMouse(int event, int x, int y, int, void*)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        currentPoint = Point2f((float)x, (float)y);
        pointTrackingFlag = true;
    }    
}