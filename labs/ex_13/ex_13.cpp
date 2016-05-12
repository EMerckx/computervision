// see: https://stackoverflow.com/questions/23448420/orb-is-not-detecting-keypoints-in-opencv-2-4-9
// see: http://docs.opencv.org/trunk/db/d95/classcv_1_1ORB.html#gsc.tab=0
// see: https://github.com/AndreasDL/Tiwi-Beeldverwerking2013-2014/blob/master/oplossingen/opgave13.cpp

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 3)
    {
        cout << "Usage: ex_13.out image1 image2" << endl;
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

    // STEP 1: convert images to grayscale 
    Mat gray1;
    cvtColor( image1, gray1, CV_RGB2GRAY );
    Mat gray2;
    cvtColor( image2, gray2, CV_RGB2GRAY );

    // STEP 2: create ORB object
    // static Ptr<ORB> cv::ORB::create ( int nfeatures = 500, float scaleFactor =1.2f,
    //                                  int nlevels = 8, int edgeThreshold = 31,
    //                                  int firstLevel = 0, int WTA_K = 2, 
    //                                  int scoreType = ORB::HARRIS_SCORE, 
    //                                  int patchSize = 31, int fastThreshold = 20 )       
    Ptr<ORB> orb = ORB::create( 48 );

    // STEP 3: detect keypoints of image
    // void detect (InputArray image, std::vector< KeyPoint > &keypoints, InputArray mask=noArray())
    // Detects keypoints in an image.
    vector<KeyPoint> keypoints1;
    orb->detect( gray1, keypoints1);
    vector<KeyPoint> keypoints2;
    orb->detect( gray2, keypoints2);

    // STEP 4: compute descriptors of image and keypoints
    // void compute (InputArray image, std::vector< KeyPoint > &keypoints, OutputArray descriptors)
    // Computes the descriptors for a set of keypoints detected in an image.
    Mat descriptors1;
    orb->compute( gray1, keypoints1, descriptors1 );
    Mat descriptors2;
    orb->compute( gray2, keypoints2, descriptors2 );

    // STEP 5: create bfmatcher
    // BFMatcher::BFMatcher(int normType=NORM_L2, bool crossCheck=false )
    BFMatcher bfmatcher;

    // STEP 6: find matches
    // void DescriptorMatcher::knnMatch(const Mat& queryDescriptors, const Mat& trainDescriptors, 
    //                                  vector<vector<DMatch>>& matches, int k, const Mat& mask=Mat(), 
    //                                  bool compactResult=false )
    // with k – Count of best matches found per each query descriptor or 
    //          less if a query descriptor has less than k possible matches in total.
    vector<vector<DMatch> > matches;
    bfmatcher.knnMatch( descriptors1, descriptors2, matches, 1);

    // STEP 7: draw keypoints for each image
    // void drawKeypoints(const Mat& image, const vector<KeyPoint>& keypoints, Mat& outImage, 
    //                      const Scalar& color=Scalar::all(-1), int flags=DrawMatchesFlags::DEFAULT )
    Mat kpimage1 = image1.clone();
    drawKeypoints( image1, keypoints1, kpimage1, Scalar(0,255,0) );
    Mat kpimage2 = image1.clone();
    drawKeypoints( image2, keypoints2, kpimage2, Scalar(0,255,0) );

    // STEP 7: draw matches
    // void drawMatches(const Mat& img1, const vector<KeyPoint>& keypoints1, const Mat& img2, 
    //                  const vector<KeyPoint>& keypoints2, const vector<DMatch>& matches1to2, 
    //                  Mat& outImg, const Scalar& matchColor=Scalar::all(-1), 
    //                  const Scalar& singlePointColor=Scalar::all(-1), 
    //                  const vector<char>& matchesMask=vector<char>(), 
    //                  int flags=DrawMatchesFlags::DEFAULT )
    Mat result;
    drawMatches(image1, keypoints1, image1, keypoints2, matches, result);

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

    // show the keypoints of image 1
    string windowName3 = "Keypoints image 1";
    namedWindow( windowName3, WINDOW_AUTOSIZE );
    imshow( windowName3, kpimage1 );
    moveWindow( windowName3, 0, image1.size().height + 55 );

    // show the keypoints of image 2
    string windowName4 = "Keypoints image 2";
    namedWindow( windowName4, WINDOW_AUTOSIZE );
    imshow( windowName4, kpimage2 );
    moveWindow( windowName4, image1.size().width, image1.size().height + 55 );

    // show the matches
    string windowName5 = "Matches";
    namedWindow( windowName5, WINDOW_AUTOSIZE );
    imshow( windowName5, result );
    moveWindow( windowName5, 0, image1.size().height * 2 + 80 );

    //-----------------------------------------------------------------------------------

    // Wait for a keystroke in the window
    waitKey(0);
    return 0;
}