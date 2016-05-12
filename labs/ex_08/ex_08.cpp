#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2 )
    {
     cout << "Usage: ex_08.out image" << endl;
     return -1;
    }

    // read the image
    Mat image;
    image = imread( argv[1], CV_LOAD_IMAGE_COLOR ); 

    // check for errors
    if(! image.data )
    {
        cout <<  "Could not open or find the image" << endl;
        return -1;
    }

    //-----------------------------------------------------------------------------------

    // create matrix
    Mat matrix;
    int rows = 2;
    int cols = 3;
    matrix = Mat::zeros( rows, cols, CV_64F );
    
    for( int i=0; i<rows; i++ ){
        matrix.Mat::at<double>(i,i) = 1;
    }

    double m = -0.125;
    matrix.Mat::at<double>(0,1) = m;

    // shear transformation
    Mat image_affine;
    warpAffine( image, image_affine, matrix, image.size() );

    //-----------------------------------------------------------------------------------

    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image );
    moveWindow( windowName1, 0, 0 );

    // show the warp affine image
    string windowName2 = "Warp affine image";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image_affine );
    moveWindow( windowName2, image.size().width, 0 );

    //-----------------------------------------------------------------------------------

    // Wait for a keystroke in the window
    waitKey(0);
    return 0;
}