// see: http://opencvexamples.blogspot.com/2014/01/perspective-transform.html
// click: left top - right top - right bottom - left bottom

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

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
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR); 

    // check for errors
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    //-----------------------------------------------------------------------------------

    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    
    imshow( windowName1, image );
    moveWindow( windowName1, 0, 0);

    //-----------------------------------------------------------------------------------

    waitKey(0);         // Wait for a keystroke in the window
    return 0;
}