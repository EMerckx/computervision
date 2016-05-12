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
     cout << "Usage: ex_06.out image" << endl;
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
    int dim = 15;
    matrix = Mat::zeros( dim, dim, CV_64F );

    // first 7 diagonal elements have the value 1/7
    for(int i=0; i<7; i++){
        matrix.Mat::at<double>(i,i) = 1.0/7.0;
    }

    // apply filter2D
    //void filter2D( InputArray src, OutputArray dst, int ddepth, InputArray kernel, 
    //              Point anchor=Point(-1,-1), double delta=0, int borderType=BORDER_DEFAULT )
    Mat image_filter2D;
    filter2D( image, image_filter2D, -1, matrix, 
        Point( matrix.cols - 1,matrix.rows - 1 ), 0, BORDER_DEFAULT );

    //-----------------------------------------------------------------------------------
    
    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image );
    moveWindow( windowName1, 0, 0 );

    // show the gray image
    string windowName2 = "Filter2D image";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image_filter2D );
    moveWindow( windowName2, image.size().width, 0 );

    //-----------------------------------------------------------------------------------

    waitKey(0);
    return 0;
}
