#include "featuremanager2d.h"

#include <opencv2/features2d.hpp>
#include <opencv2/nonfree.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>

namespace cvc
{

//Init it all
featureManager2D::featureManager2D()
{

}

void featureManager2D::init(std::vector<std::string> &feature_names)
{
    for(int i =0;i<feature_names.size();i++)
    {
        if(boost::iequals(feature_names[i], "SIFT"))
        {
            this->featureDescribeModes.push_back(0); //SIFT
            this->featureDescriptorObjects.push_back(this);
        }
    }



}

//Untested
cv::Mat featureManager2D::concatenateFeatures(featureContainer &fc)
{
    cv::Mat finalDescriptor = fc.descriptors[0].desc.clone();
    for(int i=1;i<fc.descriptors.size();i++)
    {
            cv::hconcat(finalDescriptor, fc.descriptors[i].desc, finalDescriptor);
    }

    return finalDescriptor;

}

featureContainer featureManager2D::calculateFeatures(cv::Mat &img)
{
    featureContainer allFeatures;
    for(int i=0;i<this->featureDescribeModes.size(); i++)
    {
        //Define the Features that need to go into singleFeatureStruct and then put them in

        singleFeatureStruct descriptor;
//        std::vector<cv::KeyPoint> kps; /**< Keypoints */
//        cv::Mat desc;/**< Descriptor */
//        bool isBow; /**< Is it a bag of words Descriptor? */
//        std::string descriptor_name; /**< eg. names = SIFT; SURF; */
//        std::string pooling_method; /**< eg. Mean */

        //EARLY INITIALIZATION
        descriptor.isBow=false;
        descriptor.pooling_method="Mean";


        if(featureDescribeModes[i]==0) //SIFT
        {
            //Descriptor Specific Initialization
            descriptor.descriptor_name = "SIFT";
            descriptor.kps = this->featureDescriptorObjects[i]->calculateKeypoints(img);
            descriptor.desc=this->featureDescriptorObjects[i]->calculateDescriptors(descriptor.kps, img);
            descriptor.keypoint_map=this->featureDescriptorObjects[i]->buildKeypointMap(img, descriptor.kps);
        }

        allFeatures.descriptors.push_back(descriptor);
    }


    return allFeatures;


}

//KEYPOINT MAP is CV_32SC1 -> accessor is <int>
cv::Mat featureManager2D::buildKeypointMap(cv::Mat &img, std::vector<cv::KeyPoint> &kps)
{
    cv::Mat keypointMap = cv::Mat( img.size(), CV_32SC1, cv::Scalar(-1));
    for(int i=0;i<kps.size();i++)
    {
        cv::Point pt = kps[i].pt;
        keypointMap.at<int>(pt) = i;
    }

    return keypointMap;
}

std::vector<cv::KeyPoint> featureManager2D::calculateKeypoints(cv::Mat &img)
{
    std::vector<cv::KeyPoint> kps;

    cv::Ptr<cv::FeatureDetector> detector = cv::FeatureDetector::create("Dense");
    detector->detect(img, kps);

    return kps;

}

cv::Mat featureManager2D::calculateDescriptors(std::vector<cv::KeyPoint> &keypoint_vector, cv::Mat &img)
{
    cv::Mat desc;
    cv::Mat image_gray;
    cv::cvtColor(img, image_gray, cv::COLOR_BGR2GRAY);

    cv::SiftDescriptorExtractor extractor;
    extractor.compute(img, keypoint_vector, desc);
    return desc;

}

cv::Mat featureManager2D::poolDescriptors(std::vector<cv::Point> &points, cv::Mat &keypointMapImage, cv::Mat &descriptors)
{
    cv::Mat tempDescriptor = cv::Mat::zeros(1,descriptors.cols, CV_32FC1);

    int count = 0;
    for(int i=0;i<points.size();i++)
    {
        int kp_value = keypointMapImage.at<int>(points[i]);
        if(kp_value>=0)
        {
            count ++;
            tempDescriptor+=descriptors.row(kp_value);

        }
    }

    return (tempDescriptor/count);

}

featureContainer featureManager2D::poolAllDescriptors(std::vector<cv::Point> &points, featureContainer &fc)
{
    featureContainer tempFeatures;
    for(int i=0; i<fc.descriptors.size();i++)
    {
        singleFeatureStruct single_container = fc.descriptors[i];
        single_container.desc = this->poolDescriptors(points, fc.descriptors[i].keypoint_map, fc.descriptors[i].desc).clone();
        tempFeatures.descriptors.push_back(single_container);
    }

    return tempFeatures;

}


}


