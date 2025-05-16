#include "semcv.h"
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " output.png" << std::endl;
        return 1;
    }
    std::string output_path = argv[1];

    cv::Mat original = semcv::generate_gradient_image();

    std::vector<double> gammas = {1.8, 2.0, 2.2, 2.4, 2.6};

    const int imgWidth = original.cols;
    const int imgHeight = original.rows;

    const int numImages = 1 + static_cast<int>(gammas.size());
    const int collageWidth = imgWidth;
    const int collageHeight = imgHeight * numImages;


    cv::Mat collage(collageHeight, collageWidth, CV_8UC1, cv::Scalar(0));


    cv::Rect roiOriginal(0, 0, imgWidth, imgHeight);
    original.copyTo(collage(roiOriginal));


    for (int i = 0; i < gammas.size(); i++) {
        cv::Mat gammaImg = semcv::gamma_correction(original, gammas[i]);
        cv::Rect roiGamma(0, (i + 1) * imgHeight, imgWidth, imgHeight);
        gammaImg.copyTo(collage(roiGamma));
    }

    if (!cv::imwrite(output_path, collage)) {
        std::cerr << "Error saving the file " << output_path << std::endl;
        return 1;
    }
    std::cout << "The collage was successfully saved in " << output_path << std::endl;
    return 0;
}
