// see: http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 3)
    {
        cout << "Usage: ex_12.out image1 image2" << endl;
        return -1;
    }

    // read the image
    Mat image1;
    image1 = imread( argv[1], CV_LOAD_IMAGE_COLOR );
    Mat image2;
    image2 = imread( argv[2], CV_LOAD_IMAGE_COLOR );

    // check for errors
    if(! image1.data )
    {
        cout <<  "Could not open or find the first image" << endl;
        return -1;
    }
    if(! image2.data )
    {
        cout <<  "Could not open or find the second image" << endl;
        return -1;
    }

    //-----------------------------------------------------------------------------------

    // STEP 1: convert images to grayscale for better detection
    Mat gray1;
    cvtColor( image1, gray1, CV_RGB2GRAY );
    Mat gray2;
    cvtColor( image2, gray2, CV_RGB2GRAY );

    // STEP 2: get the Harris corners
    // void goodFeaturesToTrack(InputArray image, OutputArray corners, int maxCorners, 
    //                          double qualityLevel, double minDistance, InputArray mask=noArray(),
    //                          int blockSize=3, bool useHarrisDetector=false, double k=0.04 )
    vector<Point2f> harrisCorners1;
    goodFeaturesToTrack(gray1, harrisCorners1, 200, 0.05, 10, Mat(), 3, true, 0.04);
    vector<Point2f> harrisCorners2;
    goodFeaturesToTrack(gray2, harrisCorners2, 200, 0.05, 10, Mat(), 3, true, 0.04);

    // STEP 3: show the corners in the image via green circles
    // void circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8)
    int radius = 2;
    Mat result1 = image1.clone();
    for( int i = 0; i < harrisCorners1.size(); i++ ){ 
        circle( result1, harrisCorners1[i], radius, Scalar(0,255,0), -1, 8 ); 
    }
    Mat result2 = image2.clone();
    for( int i = 0; i < harrisCorners1.size(); i++ ){ 
        circle( result2, harrisCorners2[i], radius, Scalar(0,255,0), -1, 8 ); 
    }

    //-----------------------------------------------------------------------------------

    // show the original image 1
    string windowName1 = "Original image 1";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image1 );
    moveWindow( windowName1, 0, 0 );

    // show the original image 2
    string windowName2 = "Original image 2";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image2 );
    moveWindow( windowName2, image1.size().width, 0 );

    // show the result image 1
    string windowName3 = "Result image 1";
    namedWindow( windowName3, WINDOW_AUTOSIZE );
    imshow( windowName3, result1 );
    moveWindow( windowName3, 0, image1.size().height + 55 );

    // show the result image 1
    string windowName4 = "Result image 2";
    namedWindow( windowName4, WINDOW_AUTOSIZE );
    imshow( windowName4, result2 );
    moveWindow( windowName4, image1.size().width, image1.size().height + 55 );

    //-----------------------------------------------------------------------------------

    // Wait for a keystroke in the window
    waitKey(0);
    return 0;
}