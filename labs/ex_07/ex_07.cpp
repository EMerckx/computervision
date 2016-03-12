#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
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

    // create kernel
    int erosion_type = MORPH_CROSS; // MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE
    Mat element1 = getStructuringElement( erosion_type, Size(8,8) );

    // create erosion image
    Mat image_erosion;
    erode(image, image_erosion, element1);

    // create kernel2
    int dilatation_type = MORPH_RECT; // MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE
    Mat element2 = getStructuringElement( dilatation_type, Size(1,25) );

    // create dilatation image
    Mat image_dilatation;
    dilate( image_erosion, image_dilatation, element2 );
    
    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image );
    moveWindow( windowName1, 0, 0);

    // show the erosion image
    string windowName2 = "Erosion image";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, image_erosion );
    moveWindow( windowName2, image.size().width, 0);

    // show the dilatation image
    string windowName3 = "Dilatation image";
    namedWindow( windowName3, WINDOW_AUTOSIZE );
    imshow( windowName3, image_dilatation );
    moveWindow( windowName3, 2*image.size().width, 0);


    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}