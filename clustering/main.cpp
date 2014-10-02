#include <iostream>
#include <opencv2/opencv.hpp>

#include "superpixel2d.h"
#include "../Labels/annotationhandler.h"
#include "../features2D/featuremanager2d.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;



    std::vector<cv::Vec3b> class_list(32, cv::Vec3b(0,0,0));

    //Initializing with CamVid class labels
    class_list[0] = cv::Vec3b(64,128,64);
    class_list[1] = cv::Vec3b(128,0,192);
    class_list[2] = cv::Vec3b(192,128,0);
    class_list[3] = cv::Vec3b(64,128,0);
    class_list[4] = cv::Vec3b(0,0,128);
    class_list[5] = cv::Vec3b(128,0,64);
    class_list[6] = cv::Vec3b(192,0,64);
    class_list[7] = cv::Vec3b(64,128,192);
    class_list[8] = cv::Vec3b(128,192,192);
    class_list[9] = cv::Vec3b(128,64,64);
    class_list[10] = cv::Vec3b(192,0,128);
    class_list[11] = cv::Vec3b(64,0,192);
    class_list[12] = cv::Vec3b(64,128,128);
    class_list[13] = cv::Vec3b(192,0,192);
    class_list[14] = cv::Vec3b(64,64,128);
    class_list[15] = cv::Vec3b(128,192,64);
    class_list[16] = cv::Vec3b(0,64,64);
    class_list[17] = cv::Vec3b(128,64,128);
    class_list[18] = cv::Vec3b(192,128,128);
    class_list[19] = cv::Vec3b(192,0,0);
    class_list[20] = cv::Vec3b(128,128,192);
    class_list[21] = cv::Vec3b(128,128,128);
    class_list[22] = cv::Vec3b(192,128,64);
    class_list[23] = cv::Vec3b(0,0,64);
    class_list[24] = cv::Vec3b(0,64,64);
    class_list[25] = cv::Vec3b(128,64,192);
    class_list[26] = cv::Vec3b(0,128,128);
    class_list[27] = cv::Vec3b(192,128,192);
    class_list[28] = cv::Vec3b(64,0,64);
    class_list[29] = cv::Vec3b(0,192,192);
    class_list[30] = cv::Vec3b(0,0,0);
    class_list[31] = cv::Vec3b(0,192,64);

    cv::Mat img = cv::imread("/home/prassanna/Development/Datasets/CamVid_new/Train/Images/0001TP_007290.png");
    cv::Mat annotation = cv::imread("/home/prassanna/Development/Datasets/CamVid_new/Train/Annotations/0001TP_007290.png");

    //Superpixel Object
    cvc::superpixel2d sup;
    sup.init(100,10);
    cv::Mat segmented_image = sup.calculateSlic(img);

    //AnnotationHandler Object
    cvc::annotationHandler ann;
    cv::Mat simplified_ann= ann.simplifyLabels(annotation, class_list);

    //FeatureManager object
    std::vector<std::string> features_need(1,"SIFT");
    cvc::featureManager2D feature_manager;
    feature_manager.init(features_need);
    cvc::featureContainer fc = feature_manager.calculateFeatures(img);



        //TO COMPLETE. LEFT OFF HERE
    cvc::superpixelContainer superpixels;
    superpixels.method="SLIC";
    cv::Mat descriptors_pooled;
    for(int i=0;i<sup.numberSuperpixels;i++)
    {

        std::vector<cv::Point> points = sup.getPositionsofSuperpixel(segmented_image, i);
        int best_label = ann.modeLabel(simplified_ann, points, 32);
        cv::Mat descriptor_pooled_single = feature_manager.poolDescriptors(points, fc.descriptors[0].keypoint_map, fc.descriptors[0].desc);
        if(descriptors_pooled.empty())
            descriptors_pooled = descriptor_pooled_single.clone();
        else
            descriptors_pooled.push_back(descriptor_pooled_single);

    }

    std::cout<<descriptors_pooled<<std::endl;
    std::cout<<descriptors_pooled.rows<<", "<<descriptors_pooled.cols<<std::endl;




    cv::waitKey(0);


    return 0;
}

