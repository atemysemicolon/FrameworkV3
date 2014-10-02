#ifndef ANNOTATIONHANDLER_H
#define ANNOTATIONHANDLER_H

#include <iostream>
#include <opencv2/opencv.hpp>


namespace cvc
{

    class annotationHandler
    {

        //All annotations have to be unsigned. 8UC3->Unsimplified. 8UC1->simplfied
    private:
        cv::Mat annotation_image;
        bool isSimplified;
    public:

        annotationHandler();

        void test()
        {
            std::cout<<"TEST"<<std::endl;
        }


        //Simplify labels based on class_list
        cv::Mat simplifyLabels(cv::Mat &ann_img_unsimplified, std::vector<cv::Vec3b> &class_list);

        //Find the most frequent label amongst the points
        int modeLabel(cv::Mat &ann_img_simplified, std::vector<cv::Point> &pt, int max_number_labels);

        //Label a superpixel. Input needs to be the superpixel points
        cv::Mat labelAnnotation(cv::Mat &img_simplified, std::vector<cv::Point> &points, int label);

        //Return a colour image for the annotations
        cv::Mat buildImageFromLabels(cv::Mat &simplified_ann_img, std::vector<cv::Vec3b> &class_list);

    };


}

#endif // ANNOTATIONHANDLER_H
