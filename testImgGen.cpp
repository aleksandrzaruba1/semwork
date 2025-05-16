#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>


struct TypeInfo {
    std::string name;
    int depth;
};

int main() {
    std::string folder = "D:\\SLP\\cv\\misis2025s-3-kozin-v-v\\task01-01\\testImages";
    std::string inputImagePath = folder + "\\cat.jpg";
    cv::Mat original = cv::imread(inputImagePath, cv::IMREAD_COLOR);
    if (original.empty()) {
        std::cerr << "Error: Unable to open image: " << inputImagePath << std::endl;
        return 1;
    }

    // Get image dimensions
    int width = original.cols;
    int height = original.rows;


    std::vector<TypeInfo> types = {
        {"uint08", CV_8U},
        {"sint08", CV_8S},
        {"uint16", CV_16U},
        {"sint16", CV_16S},
        {"sint32", CV_32S},
        {"real32", CV_32F},
        {"real64", CV_64F}
    };

    // File extensions to use for saving images
    std::vector<std::string> extensions = {"png", "tiff", "jpg"};

    // Process for both grayscale (1 channel) and color (3 channels)
    for (int channels : {1, 3}) {
        cv::Mat channelImage;
        if (channels == 1) {
            // Convert to grayscale
            cv::cvtColor(original, channelImage, cv::COLOR_BGR2GRAY);
        } else {
            // Keep the color image as is (3 channels)
            channelImage = original;
        }

        // For each type conversion
        for (const auto &typeInfo : types) {
            // Create a new Mat with the desired depth and the same number of channels
            int targetType = CV_MAKETYPE(typeInfo.depth, channels);
            cv::Mat converted;

            // Convert the image to the new type
            channelImage.convertTo(converted, targetType);

            // Build the filename prefix: "WWWWxHHHH.C.TYPE"
            std::ostringstream oss;
            oss << std::setw(4) << std::setfill('0') << width
                << "x"
                << std::setw(4) << std::setfill('0') << height
                << "."
                << channels
                << "."
                << typeInfo.name;
            std::string baseName = oss.str();

            // Save the image in each file format (png, tiff, jpg)
            for (const auto &ext : extensions) {
                std::string filename = folder + "\\" + baseName + "." + ext;
                if (cv::imwrite(filename, converted)) {
                    std::cout << "Saved: " << filename << std::endl;
                    std::cout << converted.depth() << std::endl;
                } else {
                    std::cerr << "Failed to write image: " << filename << std::endl;
                }
            }
        }
    }

    return 0;
}
