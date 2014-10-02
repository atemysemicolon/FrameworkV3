#include "annotationhandler.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

namespace cvc
{
annotationHandler::annotationHandler()
{
    isSimplified = false;
}

cv::Mat annotationHandler::simplifyLabels(cv::Mat &ann_img_unsimplified, std::vector<cv::Vec3b> &class_list)
{
    cv::Mat annotation_simplified = cv::Mat(ann_img_unsimplified.size(), CV_8UC(1), cv::Scalar(0));

    for(int x=0;x<ann_img_unsimplified.cols; x++)
        for(int y=0;y<ann_img_unsimplified.rows;y++)
        {
            cv::Vec3b color = ann_img_unsimplified.at<cv::Vec3b>(y,x);
            for(int k=0;k<class_list.size();k++)
            {
                if ( class_list[k] == color )
                {
                    annotation_simplified.at<uchar>(y,x) = k;
                    break;
                }
            }
        }

    return annotation_simplified;

}

int annotationHandler::modeLabel(cv::Mat &ann_img_simplified, std::vector<cv::Point> &pt, int max_number_labels)
{
    std::vector<int>counts(max_number_labels, 0);
    for(int i=0;i<pt.size();i++)
    {
        int num=ann_img_simplified.at<uchar>(pt[i]);
        counts[num]++;
    }

    int max_count=0;
    int max;
    for(int j=0;j<counts.size();j++)
        if(max>=counts[j])
        {
            max_count=counts[j];
            max = j;
        }

    return max;


}


//The matrix img_simplfied will have to built before
cv::Mat annotationHandler::labelAnnotation(cv::Mat &img_simplified, std::vector<cv::Point> &points, int label)
{
    for(int ctr=0;ctr<points.size();ctr++)
    {
        img_simplified.at<uchar>(points[ctr]) = label;
    }

    return img_simplified;

}


//Returns a label-colour based image
cv::Mat annotationHandler::buildImageFromLabels(cv::Mat &simplified_ann_img, std::vector<cv::Vec3b> &class_list)
{
    cv::Mat ann_img_unsimplified = cv::Mat::zeros(simplified_ann_img.rows, simplified_ann_img.cols, CV_8UC(3));
    for(int x=0;x<ann_img_unsimplified.cols; x++)
        for(int y=0;y<ann_img_unsimplified.rows;y++)
        {
            ann_img_unsimplified.at<cv::Vec3b>(y,x) = class_list[simplified_ann_img.at<uchar>(y,x)];
        }

    return ann_img_unsimplified;

}


}
