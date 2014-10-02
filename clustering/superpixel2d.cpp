#include "superpixel2d.h"


namespace cvc
{

superpixel2d::superpixel2d()
{
}

void superpixel2d::init(int number_of_superpixels, int compactness)
{
    this->numberSuperpixels = number_of_superpixels;
    this->Compactness = compactness;
    this->clustering_method = "SLIC";


}

Mat superpixel2d::calculateSlic(Mat &img)
{
    slic.init(img, this->numberSuperpixels, this->Compactness);
    slic.generateSuperPixels();
    cv::Mat superpixel_labels = slic.getClustersIndex();

    //Finding number of superpixels generated
    double min, max;
    cv::minMaxLoc(superpixel_labels, &min, &max);
    this->numberSuperpixels = (int) max + 1;

    return superpixel_labels;

}

void superpixel2d::buildKeypointSuperpixelRelationship(std::vector<KeyPoint> kps)
{

}

void superpixel2d::poolSuperpixelStuff()
{

}

std::vector<Point> superpixel2d::getPositionsofSuperpixel(Mat &segmented_image, int superpixel_number)
{

    std::vector<cv::Point> points;

    for(int y=0;y<segmented_image.rows; y++)
        for(int x=0;x<segmented_image.cols; x++)
            if(segmented_image.at<int>(y,x)==superpixel_number) //Because segmented_image is CV_32SC1
            {
                cv::Point p;
                p.x=x;
                p.y=y;
                points.push_back(p);
            }


    return points;
}


}
