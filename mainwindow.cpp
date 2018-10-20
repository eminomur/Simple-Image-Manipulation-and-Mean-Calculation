#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include "image.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include "thresholddialog.h"
#include "grayscaledialog.h"
#include "averageimagedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::about(this, "About Me", "Muhammed Emin ÖMÜR\nSoftware Engineering\n150308007");
}

void MainWindow::on_select_image_button_clicked()
{
    QString filter = "Image Files (*.bmp *.dib *.jpeg *.jpg *.jpe *.jp2 *.png *.pbm *.pgm *.ppm *.sr *.ras *.tiff *.tiff";
    QString selected_file_name = QFileDialog::getOpenFileName(this, "Select Image to Open", QDir::currentPath(), filter);

    if (selected_file_name == "") {
        return;
    }

    Image::initialize(selected_file_name.toStdString());
    ui->heigth_of_image_label->setText("Heigth: " + QString(std::to_string(Image::get_height()).c_str()));
    ui->width_of_image_label->setText("Width: " + QString(std::to_string(Image::get_height()).c_str()));
}

void MainWindow::on_show_current_image_button_clicked()
{
    if (Image::is_image_exist()) {
        cv::imshow("Pure Image", Image::get_pure_image());
    } else {
        QMessageBox::critical(this, "No Image", "You must choose an image first");
    }
}

void MainWindow::on_show_grayscale_button_clicked()
{
    if (Image::is_image_exist()) {
        cv::imshow("Grayscale Image", Image::get_grayscale_image());
    } else {
        QMessageBox::critical(this, "No Image", "You must choose an image first");
    }
}

void MainWindow::on_swap_red_and_green_bands_button_clicked()
{
    if (Image::is_image_exist()) {
        cv::imshow("Red and Green channels swapped", Image::get_red_and_green_swapped());
    } else {
        QMessageBox::critical(this, "No Image", "You must choose an image first");
    }
}


void MainWindow::on_swap_green_and_blue_bands_button_clicked()
{
    if (Image::is_image_exist()) {
        cv::imshow("Green and Blue channels swapped", Image::get_green_and_blue_swapped());
    } else {
        QMessageBox::critical(this, "No Image", "You must choose an image first");
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_add_or_subtract_intensity_button_clicked()
{
    if (!Image::is_image_exist()) {
        QMessageBox::critical(this, "No Image", "You must choose an image first");
        return;
    }
    GrayscaleDialog dialog;

    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_convert_to_binary_button_clicked()
{
    if (!Image::is_image_exist()) {
        QMessageBox::critical(this, "No Image", "You must choose an image first");
        return;
    }
    ThresholdDialog dialog;

    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_calculate_average_button_clicked()
{
    AverageImageDialog dialog;

    dialog.setModal(true);
    dialog.exec();
}
