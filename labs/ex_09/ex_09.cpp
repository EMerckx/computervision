// see: http://opencvexamples.blogspot.com/2014/01/perspective-transform.html

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int counter = 0;
Mat image;
Point2f inputQuad[4];
Point2f outputQuad[4];

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN ) // others: EVENT_RBUTTONDOWN, EVENT_MBUTTONDOWN, EVENT_MOUSEMOVE
     {
        cout << "Counter = " << counter << "\n";
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;

        inputQuad[counter] = Point2f(x,y);




        

        // get the matrix for the points
        //Mat rect = *((Mat*)(userdata));

        //rect

        // set the current clicked point
        //rect(counter) = cv::Point(x, y);

        // if it's the 4th point, calculate the new image and show it
        if(counter == 3){

            // Set the lambda matrix the same type and size as input
            Mat lambda;
            lambda = Mat::zeros( image.rows, image.cols, image.type() );

            outputQuad[0] = Point2f( 0,0 );
            outputQuad[1] = Point2f( image.cols-1,0);
            outputQuad[2] = Point2f( image.cols-1,image.rows-1);
            outputQuad[3] = Point2f( 0,image.rows-1);

            
            // Get the Perspective Transform Matrix i.e. lambda 
            lambda = getPerspectiveTransform( inputQuad, outputQuad );
            // Apply the Perspective Transform just found to the src image
            Mat image_perspective;
            warpPerspective(image,image_perspective,lambda,image.size() );


            //Mat rect( 2, 4, CV_32FC1 );

            //Mat image_perspective(rect.size(), rect.type());
            //Mat M = getPerspectiveTransform(rect, image_perspective);


            /*Mat image_warped;
            image_warped = warpPerspective(image, image_warped, , rect.size());*/


            string windowName2 = "Warp perspective image";
            namedWindow( windowName2, WINDOW_AUTOSIZE );
            imshow( windowName2, image_perspective );
            moveWindow( windowName2, image.size().width * 2, 0);
        }

        counter = (counter + 1) % 4;
     }
}

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    // read the image
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR); 

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

    // create 4x4 matrix and initialize all elements with (0,0)
    ///////////////cv::Mat_<cv::Point> matPoint(4, 4, cv::Point(0, 0));
    //Mat rect( 2, 4, CV_32FC1 );

    //set the callback function for any mouse event
    setMouseCallback(windowName1, CallBackFunc, NULL);
    



    waitKey(0);         // Wait for a keystroke in the window
    return 0;
}