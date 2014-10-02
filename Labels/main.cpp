#include <iostream>
#include "annotationhandler.h"
#include <opencv2/opencv.hpp>

using namespace std;

//Global matrix to hold simplified class labels. Global to use in function "function"
cv::Mat ann_img_simple;

void function_handler(int event, int x, int y, int flags, void* param)
{
    //REturn Here
    switch(event)
    {
    case cv::EVENT_LBUTTONDOWN:
        cout<<"Left button clicked in coordinates"<<(int)ann_img_simple.at<uchar>(y,x)<<"with CTRL\n"<<endl;


    break;
    }
}


//Sample code to Print the class number on the annotation output
int main()
{




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

    //Loading the Annotation Image
    cv::Mat ann_img_unsimple = cv::imread("/home/prassanna/Development/Datasets/CamVid_new/Train/Annotations/0001TP_007290.png");

    //Creating the annotation object
    cvc::annotationHandler ann;

    //Now simplify labels
    ann_img_simple= ann.simplifyLabels(ann_img_unsimple, class_list);


    //Dummy points
    std::vector<cv::Point> pts(3, cv::Point(0,0));
    pts[1]=cv::Point(0,1);
    pts[2]=cv::Point(0,2);

    //Finding best label at these three points
    cout<<ann.modeLabel(ann_img_simple, pts, 31)<<endl;

    //Changing the label at (0,1)(0,2)(0,0) to be 30
    ann_img_simple = ann.labelAnnotation(ann_img_simple, pts, 30);
    cout<<(int)ann_img_simple.at<uchar>(1,0)<<endl; //Checking if updated

    //Finding best labels after change
    cout<<ann.modeLabel(ann_img_simple, pts, 31)<<endl;

    //build modified image
    ann_img_unsimple = ann.buildImageFromLabels(ann_img_simple, class_list);

    //Display modified annotations
    cv::imshow("Annotation Image", ann_img_unsimple);

    //Call function when a mouseclick event is fired.
    int parameter = 5;
    cv::setMouseCallback("Annotation Image",function_handler,&parameter);
    cv::waitKey();
    return 0;
} //SUCCESS

