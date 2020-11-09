#include "opencv2/opencv.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    cv::String keys =
        "{ @image_file | <none> | Name of image file to be loaded }"
        "{ help        |        | Print usage                     }";

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Load an image from a file");

    if (parser.has("help"))
    {
        parser.printMessage();
        return EXIT_SUCCESS;
    }

    cv::String image_file{ parser.get<cv::String>(0) };

    if (!parser.check())
    {
        parser.printErrors();
        parser.printMessage();
        return EXIT_FAILURE;
    }

    cv::Mat image = cv::imread(image_file, cv::IMREAD_UNCHANGED);

    if (image.empty())
    {
        std::cerr << "[FATAL] Cannot load the image from " << image_file << '\n';
        return EXIT_FAILURE;
    }

    std::cout << "[INFO] Loaded the image from " << image_file << '\n';

    cv::imshow("Image", image);
    cv::waitKey();

    return EXIT_SUCCESS;
}