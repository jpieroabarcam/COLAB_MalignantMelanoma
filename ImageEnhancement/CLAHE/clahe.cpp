#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <vector>       // std::vector
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char** argv)
{
    // READ RGB color image and convert it to Lab
    const char * filename = argc >=2 ? argv[1] : "lena.jpg";

    cv::Mat bgr_image = cv::imread(filename);

    if (bgr_image.empty())
    {
	return -1;
    } 

    cv::Mat lab_image;
    cv::cvtColor(bgr_image, lab_image, cv::COLOR_BGR2Lab);

    // Extract the L channel
    std::vector<cv::Mat> lab_planes(3);
    cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

    // apply the CLAHE algorithm to the L channel
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(4);
    cv::Mat dst;
    clahe->apply(lab_planes[0], dst);

    // Merge the the color planes back into an Lab image
    dst.copyTo(lab_planes[0]);
    cv::merge(lab_planes, lab_image);

   // convert back to RGB
   cv::Mat image_clahe;
   cv::cvtColor(lab_image, image_clahe,cv::COLOR_Lab2BGR);

   // display the results  (you might also want to see lab_planes[0] before and after).
   imwrite( "../image_original.jpg", gray_image );
   imwrite( "../image_CLAHE.jpg", gray_image );   
   
}
