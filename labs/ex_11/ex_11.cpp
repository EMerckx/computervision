// see: http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
        cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
        return -1;
    }

    // read the image
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR); 

    // check for errors
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    //-----------------------------------------------------------------------------------

    // STEP 1: find the edges in the image using the Canny algorithm
    // void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2)
    Mat cannyEdges;
    Canny(image, cannyEdges, 15, 10);

    // STEP 2: get all the lines from the canny edge image
    // void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, 
    //                     int threshold, double minLineLength=0, double maxLineGap=0 )
    vector<Vec4i> lines;
    HoughLinesP( cannyEdges, lines, 0.5, CV_PI/180, 30, 10, 10 );

    // STEP 3: draw the lines on the image
    // void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8)
    Mat image_dst = image.clone();
    for( size_t i = 0; i < lines.size(); i++ )
    {

        line(image_dst, 
            Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), 
            Scalar(0,255,0), 
            2,
            CV_AA);
    }

    //-----------------------------------------------------------------------------------

    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image );
    moveWindow( windowName1, 0, 0);

    // show the canny edges
    string windowName2 = "Canny edges";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, cannyEdges );
    moveWindow( windowName2, image.size().width, 0);

    // show the original image
    string windowName3 = "Result";
    namedWindow( windowName3, WINDOW_AUTOSIZE );
    imshow( windowName3, image_dst );
    moveWindow( windowName3, 
        image.size().width + cannyEdges.size().width, 0);

    //-----------------------------------------------------------------------------------

    // Wait for a keystroke in the window
    waitKey(0);
    return 0;
}