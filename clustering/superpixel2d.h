#ifndef SUPERPIXEL2D_H
#define SUPERPIXEL2D_H

#include <opencv2/opencv.hpp>
#include <string.h>
#include "../features2D/featuremanager2d.h"
#include "slicsuperpixel.h"

namespace cvc
{
    //SEGMENTED IMAGE is 32SC1 -> accessed with <int>

    #ifndef SUPERPIXELSTRUCT_S
    #define SUPERPIXELSTRUCT_S
    //Forward Declarations
    #ifndef FEATURESTRUCT_S
    struct featureContainer;
    #endif

    /**
     * @brief
     * To hold superpixel structures.
     */
    struct singleSuperpixelStruct
    {
        bool exists;

        int superpixel_label; /**< TODO */
        std::vector<cv::Point2i> positions; /**< Position with respect to image*/
        int area; /**< Number of pixels in area */
        std::vector<int> neighbours; /**< Neighbourhood labels for each superpixel */
        int gt_label; /**< Ground truth label */
        int predicted_label; /**< Predicted Label */
        featureContainer features; /**< superpixel descriptor */

    };


    /**
     * @brief
     *
     */
    struct superpixelContainer
    {
        std::vector<singleSuperpixelStruct> nodes;
        int number;
        std::string method;

     };
    #endif

    class superpixel2d
    {
    public:
        std::string clustering_method;
        int numberSuperpixels;
        int Compactness;
        SLICSuperpixel slic;
    public:
        superpixel2d();


        //Load options. Will expand for multiple algorithms when possible
        void init(int number_of_superpixels, int compactness);

        //Currently only supporting slic. Return Segment Labelled Image
        cv::Mat calculateSlic(cv::Mat &img);

        //Pool keypoints in same superpixel
        void buildKeypointSuperpixelRelationship(std::vector<cv::KeyPoint> kps);

        //Pool Features and Labels
        void poolSuperpixelStuff();//Change signature at the time of implementation

        //Find pixel positions of a superpixel
        std::vector<cv::Point> getPositionsofSuperpixel(cv::Mat &segmented_image, int superpixel_number);



    };


}

#endif // SUPERPIXEL2D_H
