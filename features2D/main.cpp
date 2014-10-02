#include <iostream>
#include <opencv2/opencv.hpp>
#include "featuremanager2d.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    cv::Mat img = cv::imread("/home/prassanna/Development/DataTest/Lenna.png");
    cv::imshow("Image", img);
    std::vector<std::string> features_needed;
    features_needed.push_back("SIFT");

    cvc::featureManager2D awesomeness;
    awesomeness.init(features_needed);

    cvc::featureContainer fc = awesomeness.calculateFeatures(img);

    //cout<<fc.descriptors[0].desc<<endl;

    //cv::Mat kpimg=awesomeness.buildKeypointMap(img, fc.descriptors[0].kps);
    //cout<<fc.descriptors[0].keypoint_map<<endl;


    std::vector<cv::Point> pts (6,cv::Point(0,0));
    pts[1] = cv::Point(0,1);
    pts[2] = cv::Point(0,2);
    pts[3] = cv::Point(0,3);
    pts[4] = cv::Point(0,4);
    pts[5] = cv::Point(0,5);

    fc = awesomeness.poolAllDescriptors(pts, fc);
    cout<<fc.descriptors[0].desc<<endl;

    //TODO
    //1.find superpixel points given a sup
    cv::waitKey();

    return 0;

}

