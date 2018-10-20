#include "thresholddialog.h"
#include "ui_thresholddialog.h"
#include "image.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <QMessageBox>

ThresholdDialog::ThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdDialog)
{
    ui->setupUi(this);
}

ThresholdDialog::~ThresholdDialog()
{
    delete ui;
}

void ThresholdDialog::on_input_button_clicked()
{
    int value = this->ui->enter_value_spinbox->text().toInt();

    // If value is equal to zero since there will be no difference between new image and binary scale image
    // there is no need to recalculate everything
    if (value != 0) {
        cv::imshow("Threshold Image", Image::get_binary_scale_according_to_threshold_value(value));
    }

    this->close();
}
