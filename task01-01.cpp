#include <iostream>
#include "semcv.h"
#include <opencv2/imgcodecs.hpp>

namespace fs = std::filesystem;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: task01-01 <path_to_lst_file>" << std::endl;
        return 1;
    }

    fs::path lst_path(argv[1]);
    std::vector<fs::path> file_paths;
    try {
        file_paths = semcv::get_list_of_file_paths(lst_path);
    } catch (const std::exception &ex) {
        std::cerr << "error reading lst " << ex.what() << std::endl;
        return 1;
    }

    for (const auto &file: file_paths) {
        cv::Mat img = cv::imread(file.string(), cv::IMREAD_UNCHANGED);
        if (img.empty()) {
            std::cout << file.filename().string() << "\t" << "bad, cannot load image" << std::endl;
            continue;
        }
        std::string desc = semcv::strid_from_mat(img);

        std::string base = file.stem().string();
        if (base == desc) {
            std::cout << file.filename().string() << "\tgood" << std::endl;
        } else {
            std::cout << file.filename().string() << "\t" << "bad, should be " << desc << std::endl;
        }
    }

    return 0;
}
