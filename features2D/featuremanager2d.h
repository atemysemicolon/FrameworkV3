#ifndef FEATUREMANAGER2D_H
#define FEATUREMANAGER2D_H

#include <opencv2/opencv.hpp>

namespace cvc
{
    #ifndef FEATURESTRUCT_S
    #define FEATURESTRUCT_S

    struct singleFeatureStruct
    {
        std::vector<cv::KeyPoint> kps; /**< Keypoints */
        cv::Mat keypoint_map;
        cv::Mat desc;/**< Descriptor */
        bool isBow; /**< Is it a bag of words Descriptor? */
        std::string descriptor_name; /**< eg. names = SIFT; SURF; */
        std::string pooling_method; /**< eg. Adding */

        void copySingleFeatureStruct(singleFeatureStruct &feature)
        {
            kps = feature.kps;
            desc = feature.desc.clone();
            isBow = feature.isBow;
            descriptor_name = feature.descriptor_name;
            pooling_method = feature.pooling_method;
        }

    };


    struct featureContainer
    {
        std::vector<singleFeatureStruct> descriptors; //Multiple kind of descriptors (Different names)
        cv::Mat concatenatedDescriptor;

        void copyFeatureContainer(featureContainer &features)
        {
            descriptors = features.descriptors;
            concatenatedDescriptor = features.concatenatedDescriptor.clone();
        }

    };
    #endif


    //While Manager, also implements SIFT by default
    class featureManager2D
    {
    private:
        std::vector<int> featureDescribeModes;
        std::vector<featureManager2D *> featureDescriptorObjects;

    public:
        featureManager2D();

        //initialize all class stuff stuff
        void init(std::vector<std::string> &feature_names);

        //Concatenate the Different Kinds of features. Has to be done in the end.
        cv::Mat concatenateFeatures(featureContainer &fc);

        //Get all Features and put them in a container. Internally populates singleFeatureStruct with feature descriptors
        featureContainer calculateFeatures(cv::Mat &img);

        //Build Keypoint Map
        virtual cv::Mat buildKeypointMap(cv::Mat &img, std::vector<cv::KeyPoint> &kps);

        //Calculate necessary Keypoints in the image
        virtual std::vector<cv::KeyPoint> calculateKeypoints(cv::Mat &img);

        //Calculate all descriptors corresponding to keypoints
        virtual cv::Mat calculateDescriptors(std::vector<cv::KeyPoint> &keypoint_vector, cv::Mat &img);

        //Pool descriptors to return a (set of) descriptor(s) per superpixel. Returns pooled Descriptor
        virtual cv::Mat poolDescriptors(std::vector<cv::Point> &points, cv::Mat &keypointMapImage, cv::Mat &descriptors);

        //Pool all descriptors(eg. SIFT, SURF, HOG) for a set of points
        virtual featureContainer poolAllDescriptors(std::vector<cv::Point> &points, featureContainer &fc);

    };


}

#endif // FEATUREMANAGER2D_H
