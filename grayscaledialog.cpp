#include "grayscaledialog.h"
#include "ui_grayscaledialog.h"
#include "image.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <QMessageBox>

GrayscaleDialog::GrayscaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GrayscaleDialog)
{
    ui->setupUi(this);
}

GrayscaleDialog::~GrayscaleDialog()
{
    delete ui;
}

void GrayscaleDialog::on_input_button_clicked()
{
    int value = this->ui->enter_value_spinbox->text().toInt();

    // If value is equal to zero since there will be no difference between new image and current grayscale image
    // there is no need to calculate everything
    if (value != 0) {
        cv::imshow("New Grayscale Image", Image::get_new_grayscale_image(value));
    }

    this->close();
}
