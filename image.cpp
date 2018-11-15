#include "image.h"
#include <string>
#include <cmath>
#include <vector>
#include <stack>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat Image::pure_image;
cv::Mat Image::grayscale_image;
cv::Mat Image::red_and_green_swapped;
cv::Mat Image::green_and_blue_swapped;

void Image::initialize()
{
    pure_image.release();
    grayscale_image.release();
    red_and_green_swapped.release();
    green_and_blue_swapped.release();
}

bool Image::initialize(std::string image_directory)
{
    pure_image = cv::imread(image_directory, cv::IMREAD_COLOR);

    if (pure_image.data == nullptr) {
        return false;
    }

    // When a new image is loaded, other image formats are initialized automatically
    grayscale_format();
    swap_red_and_green();
    swap_green_and_blue();

    return true;
}

void Image::grayscale_format()
{
    // This is equivalent to
    // cv::imread(image_destination, cv::IMREAD_GRAYSCALE)
    grayscale_image = cv::Mat(cv::Size(pure_image.cols, pure_image.rows), CV_8UC1);
    uchar blue, green, red;

    for (int i = 0; i < pure_image.rows; ++i) {
        for (int j = 0; j < pure_image.cols; ++j) {
            blue = pure_image.at<cv::Vec3b>(i, j)[0];
            green = pure_image.at<cv::Vec3b>(i, j)[1];
            red = pure_image.at<cv::Vec3b>(i, j)[2];

            grayscale_image.at<uchar>(i, j) = static_cast<uchar>(std::round(blue * 0.114)) +
                                              static_cast<uchar>(std::round(green * 0.587)) +
                                              static_cast<uchar>(std::round(red * 0.299));
        }
    }
}

void Image::swap_red_and_green()
{
    red_and_green_swapped = cv::Mat(cv::Size(pure_image.cols, pure_image.rows), pure_image.type());

    for (int i = 0; i < pure_image.rows; ++i) {
        for (int j = 0; j < pure_image.cols; ++j) {
            red_and_green_swapped.at<cv::Vec3b>(i, j)[0] = pure_image.at<cv::Vec3b>(i, j)[0];
            red_and_green_swapped.at<cv::Vec3b>(i, j)[1] = pure_image.at<cv::Vec3b>(i, j)[2];
            red_and_green_swapped.at<cv::Vec3b>(i, j)[2] = pure_image.at<cv::Vec3b>(i, j)[1];
        }
    }
}

void Image::swap_green_and_blue()
{
    green_and_blue_swapped = cv::Mat(cv::Size(pure_image.cols, pure_image.rows), pure_image.type());

    for (int i = 0; i < pure_image.rows; ++i) {
        for (int j = 0; j < pure_image.cols; ++j) {
            green_and_blue_swapped.at<cv::Vec3b>(i, j)[0] = pure_image.at<cv::Vec3b>(i, j)[1];
            green_and_blue_swapped.at<cv::Vec3b>(i, j)[1] = pure_image.at<cv::Vec3b>(i, j)[0];
            green_and_blue_swapped.at<cv::Vec3b>(i, j)[2] = pure_image.at<cv::Vec3b>(i, j)[2];
        }
    }
}

cv::Mat& Image::get_pure_image()
{
    return pure_image;
}

cv::Mat& Image::get_grayscale_image()
{
    return grayscale_image;
}

cv::Mat& Image::get_red_and_green_swapped()
{
    return red_and_green_swapped;
}

cv::Mat& Image::get_green_and_blue_swapped()
{
    return green_and_blue_swapped;
}

cv::Mat Image::get_new_grayscale_image(int value)
{
    cv::Mat new_grayscale_image = grayscale_image.clone();
    std::vector<uchar> grayscale_lookup_table = get_grayscale_lookup_table(value);

    for (int i = 0; i < new_grayscale_image.rows; ++i) {
        for (int j = 0; j < new_grayscale_image.cols; ++j) {
            new_grayscale_image.at<uchar>(i, j) = grayscale_lookup_table[new_grayscale_image.at<uchar>(i, j)];
        }
    }

    return new_grayscale_image;
}

cv::Mat Image::get_binary_scale_according_to_threshold_value(int threshold)
{
    cv::Mat binary_image(cv::Size(grayscale_image.cols, grayscale_image.rows), grayscale_image.type());

    for (int i = 0; i < grayscale_image.rows; ++i) {
        for (int j = 0; j < grayscale_image.cols; ++j) {
            if (grayscale_image.at<uchar>(i, j) < threshold) {
                binary_image.at<uchar>(i, j) = 0;
            } else {
                binary_image.at<uchar>(i, j) = 255;
            }
        }
    }

    return binary_image;
}

int Image::get_width()
{
    return pure_image.cols;
}

int Image::get_height()
{
    return pure_image.rows;
}

bool Image::is_image_exist()
{
    return !pure_image.empty();
}

std::vector<uchar> Image::get_grayscale_lookup_table(int value)
{
    std::vector<uchar> lookup_table;

    for (int i = 0; i < 256; ++i) {
        lookup_table.push_back(static_cast<uchar>(i + value));
    }

    return lookup_table;
}

cv::Mat Image::get_average_of_given_images(std::stack<std::string>& image_location_list)
{
    std::vector<cv::Mat> list_of_grayscale_images_to_be_calculated;

    while (!image_location_list.empty()) {
        list_of_grayscale_images_to_be_calculated.push_back(resize_image(grayscale_format(cv::imread(image_location_list.top()))));
        image_location_list.pop();
    }

    return calculate_average(list_of_grayscale_images_to_be_calculated);
}

cv::Mat Image::grayscale_format(const cv::Mat& image)
{
    cv::Mat new_image(cv::Size(image.cols, image.rows), CV_8UC1);
    uchar blue, green, red;

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            blue = image.at<cv::Vec3b>(i, j)[0];
            green = image.at<cv::Vec3b>(i, j)[1];
            red = image.at<cv::Vec3b>(i, j)[2];

            new_image.at<uchar>(i, j) = static_cast<uchar>(std::round(blue * 0.114)) +
                                        static_cast<uchar>(std::round(green * 0.587)) +
                                        static_cast<uchar>(std::round(red * 0.299));
        }
    }

    return new_image;
}

cv::Mat Image::resize_image(const cv::Mat& image)
{
    cv::Mat result_image;

    if (image.rows * image.cols < 300 * 300) {
        cv::resize(image, result_image, cv::Size(300, 300), 0, 0, cv::INTER_CUBIC);
    } else if (image.rows * image.cols > 300 * 300) {
        cv::resize(image, result_image, cv::Size(300, 300), 0, 0, cv::INTER_AREA);
    }

    return result_image;
}

cv::Mat Image::calculate_average(std::vector<cv::Mat>& image_list)
{
    // 300 is a constant value for width and heigth values
    cv::Mat average_image(300, 300, CV_8UC1);
    int row, column;
    unsigned int index;
    double average;

    for (row = 0; row < 300; ++row) {
        for (column = 0; column < 300; ++column) {
            for (index = 0, average = 0; index < image_list.size(); ++ index) {
                average += image_list[index].at<uchar>(row, column);
            }
            average_image.at<uchar>(row, column) = static_cast<uchar>(average / image_list.size());
        }
    }

    return average_image;
}
