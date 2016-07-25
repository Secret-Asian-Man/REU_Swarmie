#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching/stitcher.hpp>
#include <vector>
#include <ctime>

#define imgDest "/home/david/Desktop/panoTestPictures/panoTestLowResTransFast/"
#define testPanoJpgDir "/home/david/Desktop/testPano.jpg"

int main(int argc, char *argv[])
{

    std::cout<<"Starting.............."<<std::endl<<std::endl;

    cv::Stitcher stitcher = cv::Stitcher::createDefault(1); // 1/true = try to use gpu

    std::vector<cv::Mat> panoSet;
    cv::Stitcher::Status status;
    cv::Mat finalPano;

    std::clock_t beginTime = std::clock();

    //    panoSet.push_back(cv::imread(imgDest "image0.jpg"));
    //    panoSet.push_back(cv::imread(imgDest "image1.jpg"));
    //    panoSet.push_back(cv::imread(testPanoJpgDir));

    //    panoSet.push_back(cv::imread(imgDest "image2.jpg"));
//        panoSet.push_back(cv::imread(imgDest "image3.jpg"));
//        panoSet.push_back(cv::imread(imgDest "image4.jpg"));
//        panoSet.push_back(cv::imread(imgDest "image5.jpg"));
//        panoSet.push_back(cv::imread(imgDest "image6.jpg"));
//        panoSet.push_back(cv::imread(imgDest "image7.jpg"));
//    panoSet.push_back(cv::imread(imgDest "image8.jpg"));
//    panoSet.push_back(cv::imread(imgDest "image9.jpg"));
//    panoSet.push_back(cv::imread(imgDest "image10.jpg"));
//    panoSet.push_back(cv::imread(imgDest "image11.jpg"));
//    panoSet.push_back(cv::imread(imgDest "image12.jpg"));
//    panoSet.push_back(cv::imread(imgDest "image13.jpg"));
//    panoSet.push_back(cv::imread(imgDest "image14.jpg"));
    panoSet.push_back(cv::imread(imgDest "image15.jpg"));
    panoSet.push_back(cv::imread(imgDest "image16.jpg"));
    //    panoSet.push_back(cv::imread(imgDest "image17.jpg"));
    //    panoSet.push_back(cv::imread(imgDest "image18.jpg"));
    //    panoSet.push_back(cv::imread(imgDest "image19.jpg"));
    //    panoSet.push_back(cv::imread(imgDest "image20.jpg"));

    //options
    //stitcher.setWarper(new cv::detail::PlaneWarper());
    //    stitcher.setFeaturesFinder(new cv::detail::SurfFeaturesFinder(1000,3,4,3,4));
    stitcher.setRegistrationResol(0.1); /// 0.6
    stitcher.setSeamEstimationResol(0.1);   /// 0.1
    stitcher.setCompositingResol(0.6);   //1
    stitcher.setPanoConfidenceThresh(1);   //1
    stitcher.setWaveCorrection(true);
    stitcher.setWaveCorrectKind(cv::detail::WAVE_CORRECT_HORIZ);
    stitcher.setFeaturesMatcher(new cv::detail::BestOf2NearestMatcher(false,0.3));
    stitcher.setBundleAdjuster(new cv::detail::BundleAdjusterRay());
    stitcher.estimateTransform(panoSet);
    stitcher.composePanorama(panoSet, finalPano);



    std::cout<<"Stitching.............."<<std::endl<<std::endl;
    status = stitcher.stitch(panoSet, finalPano);













    if(cv::Stitcher::OK == status)
    {
        std::cout<<"Writing.............."<<std::endl<<std::endl;
        cv::imwrite("/home/david/Desktop/testPano.jpg",finalPano);
    }
    else
        std::cout<<"!!!!!!!!!!!!!!CRITICAL FAILURE!!!!!!!!!!!!!!"<<std::endl<<std::endl;

    std::clock_t endTime = std::clock();

    std::cout<<"Finished!"<<std::endl<<std::endl;
    std::cout<<"Time elapsed: "<<double(endTime - beginTime)/1000000<<" seconds"<<std::endl<<std::endl;




    return 0;
}
