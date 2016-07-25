#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

#define singlePictureWidth 320
#define singlePictureHeight 240
#define workspaceMultiplier 10
#define workspaceWidth singlePictureWidth*workspaceMultiplier
#define workspaceHeight singlePictureHeight*workspaceMultiplier

#define fileOutPath "/home/david/Desktop/workSpace2.jpg"
#define fileInPath "/home/david/Desktop/panoTestPictures/panoTestLowResTransFast/"

using namespace std;
using namespace cv;

void appendToWorkspace(Mat &workspace, const Mat &image, unsigned int xPos, unsigned int yPos, double theta);

int main(int argc, char *argv[])
{

    Mat workspace = Mat(workspaceHeight, workspaceWidth, CV_8UC1);
    Mat singleImage = imread(fileInPath "image23.jpg");


    appendToWorkspace(workspace,singleImage,0,0,45);

    imwrite(fileOutPath,workspace);

    return 0;
}

void appendToWorkspace(Mat &workspace, const Mat &image, unsigned int xPos=0, unsigned int yPos=0, double theta = 0)
{


    Mat rotateMe = getRotationMatrix2D(Point2f(image.cols/2, image.rows/2),theta,1);
    warpAffine(image, image, rotateMe, image.size());

    for (int i = 0; i<image.rows; ++i)
    {

        double* workspaceRowPointer = workspace.ptr<double>(i + xPos); //use xPos here
        const double* imageRowPointer = image.ptr<double>(i);
        for (int j = 0; j<image.cols/3; ++j)
        {
            workspaceRowPointer[j+yPos] = imageRowPointer[j]; //use yPos here
        }

    }



}


















