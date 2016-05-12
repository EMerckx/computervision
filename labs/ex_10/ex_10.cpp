// see: https://github.com/AndreasDL/Tiwi-Beeldverwerking2013-2014/blob/master/oplossingen/opgave10.cpp

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

const int KERNEL_SIZE = 45;

int main( int argc, char** argv )
{
    if( argc != 2 )
    {
        cout << "Usage: ex_10.out image" << endl;
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

    // STEP 1: create 1D gaussian kernel
    Mat gaussKernel = getGaussianKernel( KERNEL_SIZE, 9.7, CV_32F );

    // STEP 2: copy the middle column of the kernel to a square matrix
    Mat square = Mat::zeros( KERNEL_SIZE, KERNEL_SIZE, CV_32F );
    Mat middleColumn = square.col( (int) KERNEL_SIZE / 2 );
    gaussKernel.col(0).copyTo(middleColumn);

    // STEP 3: create another 1D gaussian kernel 
    // use a smaller deviation and transpose it to obtain a row matrix
    Mat gaussRow = getGaussianKernel( KERNEL_SIZE, 0.3, CV_32F );
    gaussRow = gaussRow.t();

    // STEP 4: filter the square matrix with the row kernel
    // this to obtain a 2D gaussian
    Mat gauss2D;
    filter2D( square, gauss2D, CV_32F, gaussRow );

    // STEP 5: differentiate vertical (or horizontal) with Sobel
    // this to obtain a DoG filter (= Differential of Gaussian)
    // void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy)
    // NOTE: here vertical is needed because we want the (vertical) yellow lines
    Mat DogFilter;
    Sobel( gauss2D, DogFilter, CV_32F, 1, 0 ); 

    // STEP 6: create rotation matrix for the right angle of the yellow lines
    // this angle is 75 degrees
    // Mat getRotationMatrix2D(Point2f center, double angle, double scale)
    // angle – sRotation angle in degrees. Positive values mean counter-clockwise rotation
    //         (the coordinate origin is assumed to be the top-left corner).
    // 75 degrees from horizontal ~ -15 degrees from vertical 
    Point2f imageCenter ( KERNEL_SIZE / 2, KERNEL_SIZE / 2 );
    double angle = -15;
    Mat rotationMatrix = getRotationMatrix2D( imageCenter, angle, 1 );

    // STEP 7: rotate the DoG filter with the rotation matrix
    // void warpAffine(InputArray src, OutputArray dst, InputArray M, Size dsize)
    Mat rotatedDogFilter;
    warpAffine( DogFilter, rotatedDogFilter, rotationMatrix, DogFilter.size() );
    Mat dogFilterNormalized;
    normalize( rotatedDogFilter, dogFilterNormalized, 0, 1, NORM_MINMAX );

    // STEP 8: convert the picture to grayscale and filter it with the rotated DoG filter
    Mat gray;
    cvtColor( image, gray, CV_RGB2GRAY );
    Mat filtered;
    filter2D( gray, filtered, CV_32F, rotatedDogFilter );

    // STEP 9: take the absolute value of the filtered image
    // our image contains too much information, so we divide it by 256
    // if still too much, divide by larger value
    Mat dst;
    dst = abs( filtered / 256 );

    //-----------------------------------------------------------------------------------

    // show the original image
    string windowName1 = "Original image";
    namedWindow( windowName1, WINDOW_AUTOSIZE );
    imshow( windowName1, image );
    moveWindow( windowName1, 0, 0 );

    // show the rotated normalized dog filter
    string windowName2 = "DoG filter";
    namedWindow( windowName2, WINDOW_AUTOSIZE );
    imshow( windowName2, dogFilterNormalized );
    moveWindow( windowName2, image.size().width, 0 );

    // show the original image
    string windowName3 = "Result";
    namedWindow( windowName3, WINDOW_AUTOSIZE );
    imshow( windowName3, dst );
    moveWindow( windowName3, 
        image.size().width + dogFilterNormalized.size().width, 0 );

    //-----------------------------------------------------------------------------------

    // Wait for a keystroke in the window
    waitKey(0);
    return 0;
}