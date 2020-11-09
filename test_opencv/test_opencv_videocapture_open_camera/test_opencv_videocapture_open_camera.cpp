#include "opencv2/opencv.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    cv::String keys =
        "{ @camera_id | | ID of the video capturing device to open }"
        "{ help       | | Print usage                              }";

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Open a camera for video capturing");

    if (parser.has("help"))
    {
        parser.printMessage();
        return EXIT_SUCCESS;
    }

    int camera_id{ parser.get<int>(0) };

    if (!parser.check())
    {
        parser.printErrors();
        parser.printMessage();
        return EXIT_FAILURE;
    }

    cv::VideoCapture video_capture(camera_id, cv::CAP_ANY);

    if (!video_capture.isOpened())
    {
        std::cerr << "[FATAL] Cannot open the camera ID=" << camera_id << '\n';
        return EXIT_FAILURE;
    }

    std::cout << "[INFO] Opened the camera ID=" << camera_id << '\n';

    cv::String camera_window{ "Camera" };
    cv::namedWindow(camera_window, cv::WINDOW_NORMAL);
    constexpr int k_no_key_pressed{ -1 };

    while (cv::waitKey(5) == k_no_key_pressed)
    {
        cv::Mat frame;
        video_capture >> frame;

        if (frame.empty())
        {
            std::cerr << "[ERROR] Empty frame" << "\n";
        }
        else
        {
            cv::imshow(camera_window, frame);
        }
    }

    return EXIT_SUCCESS;
}