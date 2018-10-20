#include "averageimagedialog.h"
#include "ui_averageimagedialog.h"
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "image.h"

AverageImageDialog::AverageImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AverageImageDialog)
{
    ui->setupUi(this);
    ui->number_of_items_selected_label->setText("0 items selected");
}

AverageImageDialog::~AverageImageDialog()
{
    delete ui;
}

void AverageImageDialog::on_delete_the_latest_added_item_button_clicked()
{
    if (list_of_image_locations.size() != 0) {
        list_of_image_locations.pop();
        set_message_in_label();
    }
}

void AverageImageDialog::set_message_in_label()
{
    std::string message = " items selected";
    ui->number_of_items_selected_label->setText((std::to_string(list_of_image_locations.size()) + message).c_str());
}

void AverageImageDialog::on_clean_all_button_clicked()
{
    while (!list_of_image_locations.empty()) {
        list_of_image_locations.pop();
    }
    ui->number_of_items_selected_label->setText("0 items selected");
}

void AverageImageDialog::on_add_new_item_button_clicked()
{
    QString filter = "Image Files (*.bmp *.dib *.jpeg *.jpg *.jpe *.jp2 *.png *.pbm *.pgm *.ppm *.sr *.ras *.tiff *.tiff";
    QString selected_file_name = QFileDialog::getOpenFileName(this, "Select Image to Open", QDir::currentPath(), filter);

    if (selected_file_name == "") {
        return;
    }

    list_of_image_locations.push(selected_file_name.toStdString());
    set_message_in_label();
}

void AverageImageDialog::on_calculate_button_clicked()
{
    if (list_of_image_locations.size() == 0) {
        QMessageBox::critical(this, "No Image", "You have chosen no image");
    } else if (list_of_image_locations.size() == 1) {
        QMessageBox::critical(this, "Insufficient Image", "You have to choose at least 2 images");
    } else {
        this->close();
        cv::imshow("Average of Selected Images", Image::get_average_of_given_images(list_of_image_locations));
    }
}
