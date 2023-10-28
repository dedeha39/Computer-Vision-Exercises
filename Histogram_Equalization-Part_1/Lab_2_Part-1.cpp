// ****************************
// Name = Ismail Deha
// Surname = Kose
// Student ID = 2072544
// Task = Lab 2_Part 1
// ****************************


#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

//Struced variables to return histograms in Histogram function
struct MatResults {
    Mat histImage_b;
    Mat histImage_g;
    Mat histImage_r;
};

//Show histogram
MatResults Histogram(int argc, char** argv, cv::Mat src){
    MatResults results; //Structed variables
    vector<Mat> bgr_planes;
    split(src, bgr_planes);
    int histSize = 256; //Set the range of values

    //the upper boundary is exclusive
    float range[] = { 0, 256 }; 
    const float* histRange[] = { range };

    bool uniform = true, accumulate = false; //To make same sized to each bins

    //The histogram values are calculated for each channel by using calcHist().
    Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate);
    
    //The histogram so its values fall in the range indicated by the parameters entered by using normalize().
    //Create an image to display the histograms
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    results.histImage_b = Mat(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    results.histImage_g = Mat(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    results.histImage_r = Mat(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    normalize(b_hist, b_hist, 0, results.histImage_b.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, results.histImage_g.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, results.histImage_r.rows, NORM_MINMAX, -1, Mat());

    //1D Histogram, it is accessed to bins
    for (int i = 1; i < histSize; i++)
    {
        line(results.histImage_b, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
            Scalar(255, 0, 0), 2, 8, 0);
        line(results.histImage_g, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
            Scalar(0, 255, 0), 2, 8, 0);
        line(results.histImage_r, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
            Scalar(0, 0, 255), 2, 8, 0);
    }

    return results;
}

//Image Equalizzation function
 Mat Equalization( void* userdata) {
    cv::Mat image = *(cv::Mat*)userdata; // Get image
    vector<Mat> channels;
    split(image, channels); //split image to channels as B,G,R
    Mat B, G, R; // Channels

    //Three channels are equalized using equalizeHist()
    equalizeHist(channels[0], B);
    equalizeHist(channels[1], G);
    equalizeHist(channels[2], R);

    //Equalized channels are merged
    vector<Mat> combined;
    combined.push_back(B);
    combined.push_back(G);
    combined.push_back(R);

    //To return image, it is converted as Mat variable
    Mat result;
    merge(combined, result);
    return result;

}
 
 //Image Luminance Equalizzation function
Mat Luminance_equalization(void* userdata) {

    cv::Mat image = *(cv::Mat*)userdata; // Get image
    Mat channels[3];
    cvtColor(image, image, COLOR_BGR2Lab); //Changed the color space which is desied
    split(image, channels); //split image to channels
    Mat equalized_L;
    equalizeHist(channels[0], equalized_L); // Just equalized the L color
    vector<Mat> merged_channels{ equalized_L, channels[1], channels[2] }; // Merged equalized and other colors
    
    //To return image, it is converted as Mat variable
    Mat result;
    merge(merged_channels, result);
    cvtColor(result, result, COLOR_Lab2BGR); //To display image returned back own color space
    return result;
}

int main(int argc, char** argv)
{
    Mat src = imread("countryside.jpg"); //Get image

    //Showed original image histograms and itself
    MatResults results = Histogram(argc, argv, src);
    Mat histImage_b = results.histImage_b;
    Mat histImage_g = results.histImage_g;
    Mat histImage_r = results.histImage_r;
    imshow("Source Image", src);
    imwrite("Outputs/Source_Image.jpg", src);
    imshow("Source Image Histogram_B ", histImage_b);
    imshow("Source Image Histogram_G", histImage_g);
    imshow("Source Image Histogram_R", histImage_r);

    //Showed Equalized image histograms and itself
    Mat equalization_image= Equalization((void*)&src);
    MatResults results_1 = Histogram(argc, argv, equalization_image);
    Mat histEqualization_b = results_1.histImage_b;
    Mat histEqualization_g = results_1.histImage_g;
    Mat histEqualization_r = results_1.histImage_r;
    imshow("Equalization Image", equalization_image);
    imwrite("Outputs/Equalization_Image.jpg", src);
    imshow("Equalization Histogram_B", histEqualization_b);
    imshow("Equalization Histogram_G", histEqualization_g);
    imshow("Equalization Histogram_R", histEqualization_r);

    //Showed Lumaiance Equalized image histograms and itself
    Mat luminance_equalization_image = Luminance_equalization((void*)&src);
    MatResults results_2 = Histogram(argc, argv, luminance_equalization_image);
    Mat histLuminance_b = results_2.histImage_b;
    Mat histLuminance_g = results_2.histImage_g;
    Mat histLuminance_r = results_2.histImage_r;
    imshow("Luminance Equalization Image", luminance_equalization_image);
    
    imshow("Luminance Equalization Histogram_B", histLuminance_b);
    imshow("Luminance Equalization Histogram_G", histLuminance_g);
    imshow("Luminance Equalization Histogram_R", histLuminance_r);
    imwrite("Outputs/Luminance_Equalization_Image.jpg", luminance_equalization_image);
    waitKey(0);
    return EXIT_SUCCESS;
}