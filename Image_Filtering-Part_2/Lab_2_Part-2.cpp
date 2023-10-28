// ****************************
// Name = Ismail Deha
// Surname = Kose
// Student ID = 2072544
// Task = Lab 2_Part 2
// ****************************


#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main() {
    Mat image = imread("portello-noisy.png", IMREAD_COLOR);
    Mat imageClone = image.clone();
    Mat imageClone2 = image.clone();
    Mat imageClone3 = image.clone();
    // kernel size to be used in filters
    int kernel_size = 1;

    // create a window for median filters
    namedWindow("MedianBlur_Filter", 1);

    // create a trackbar for kernel size on median window
    createTrackbar("Kernel\nSize", "MedianBlur_Filter", &kernel_size, 51);

    // shows original image
    imshow("Original Image", image);

    // resets the value of kernel size
    int kernel_size_Gaussian = 1;

    // a new window for gaussian filter
    namedWindow("GaussianBlur_Filter", 1);

    // create track bar for kernel size parameter
    createTrackbar("Kernel\nSize", "GaussianBlur_Filter", &kernel_size_Gaussian, 101);

    // create a track bar for sigma parameter. trackbar does not take double value so I took int and divided it into 100
    // the sigma value is the /100 of the value in trackbar
    int sigma_trackbar = 100; // 100 = 1
    createTrackbar("Sigma\n/100", "GaussianBlur_Filter", &sigma_trackbar, 1000);

    // resets the value of kernel size
    int kernel_size_Bilateral = 1;

    // new window for bilateral
    namedWindow("Bilateral_Filter", 1);

    createTrackbar("Kernel\nSize", "Bilateral_Filter", &kernel_size_Bilateral, 101);

    // create trackbars for sigma_range and sigma_space. Like in the gaussian, trackbar values are divided into 100 in function
    int sigma_range_trackbar = 1;
    createTrackbar("Sigma\nRange\n/100", "Bilateral_Filter", &sigma_range_trackbar, 100000); // /100
    int sigma_space_trackbar = 1;
    createTrackbar("Sigma\nSpace\n/100", "Bilateral_Filter", &sigma_space_trackbar, 100000); // /100

    cout << "\nPress ESC to close the program...\n";
    cout << "\nPress P to save each window separately...\n";

    while (true)
    {
        // checks the kernel size and corrects it to be an odd value. If it is even, adds 1 to it
        if (kernel_size % 2 == 0)
            kernel_size = kernel_size + 1; // kernel size needs to be odd, add it 1 if it is even

        // medianblur function
        medianBlur(image, imageClone, kernel_size);

        // shows the median blur applied image
        imshow("MedianBlur_Filter", imageClone);

        // checks the kernel size and corrects it to be an odd value. If it is even, adds 1 to it
        if (kernel_size_Gaussian % 2 == 0)
            kernel_size_Gaussian = kernel_size_Gaussian + 1; // kernel size needs to be odd, add it 1 if it is even

        // GaussianBlur function with the values from trackbars
        GaussianBlur(image, imageClone2, Size(kernel_size_Gaussian, kernel_size_Gaussian), sigma_trackbar / 100, sigma_trackbar / 100);

        // shows gaussian applied image
        imshow("GaussianBlur_Filter", imageClone2);

        // bilateral filter with the values from trackbar. sigma_range and sigma_space are divided into 100 before applied
        bilateralFilter(image, imageClone3, kernel_size_Bilateral, sigma_range_trackbar / 100, sigma_space_trackbar / 100);

        // shows the bilateral filter applied image
        imshow("Bilateral_Filter", imageClone3);

        // wait for "esc" and "P" keys
        int iKey = waitKey(100);
        if (iKey == 27)
        {
            break;
        }
        
        if (iKey == 80 || iKey == 112)
        {
            imwrite("Outputs/MedianBlur_Filter.jpg", imageClone);
            imwrite("Outputs/GaussianBlur_Filter.jpg", imageClone2);
            imwrite("Outputs/Bilateral_Filter.jpg", imageClone3);
        }

    }
    destroyAllWindows();
}
