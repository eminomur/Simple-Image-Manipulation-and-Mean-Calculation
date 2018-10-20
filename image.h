#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <stack>
#include <opencv2/core.hpp>

class Image
{
public:
    // Following functions initializes class values
    static void initialize();
    static bool initialize(std::string image_directory);

    // Following functions are only used to return member private objects
    static cv::Mat& get_pure_image();
    static cv::Mat& get_grayscale_image();
    static cv::Mat& get_red_and_green_swapped();
    static cv::Mat& get_green_and_blue_swapped();

    // Following functions will first calculate the result according to given input
    // then return an object
    static cv::Mat get_new_grayscale_image(int value);
    static cv::Mat get_binary_scale_according_to_threshold_value(int threshold);

    // Following functions are used to fill width and height labels in main window
    static int get_width();
    static int get_height();

    // Returns true if pure_image member object includes elements in its array,
    // otherwise it returns false
    static bool is_image_exist();

    // According to arguments, following function calculates
    // the average of images and returns it
    static cv::Mat get_average_of_given_images(std::stack<std::string>& image_location_list);
private:
    Image() = default;
    ~Image() = default;

    // Following functions are used to initialize grayscale_image,
    // red_and_green_swapped and green_and_blue_swapped member variables
    static void grayscale_format();
    static void swap_red_and_green();
    static void swap_green_and_blue();

    static cv::Mat pure_image;
    static cv::Mat grayscale_image;
    static cv::Mat red_and_green_swapped;
    static cv::Mat green_and_blue_swapped;

    // Creates a lookup table and returns it
    static std::vector<uchar> get_grayscale_lookup_table(int value);

    // Following function takes an image as argument and returns it
    // as a grayscale image
    static cv::Mat grayscale_format(const cv::Mat& image);

    // This function applies interpolation techniques to given image
    // According to given image, applied interpolation technique is either
    // INTER_AREA (for image shrinking) or INTER_CUBIC (for image enlarging)
    // At least for now returned image's resolution values are constant (300 x 300)
    static cv::Mat resize_image(const cv::Mat& image);

    static cv::Mat calculate_average(std::vector<cv::Mat>& image_list);
};

#endif // IMAGE_H
