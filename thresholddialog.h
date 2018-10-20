#ifndef THRESHOLDDIALOG_H
#define THRESHOLDDIALOG_H

#include <QDialog>

namespace Ui {
class ThresholdDialog;
}

class ThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdDialog(QWidget *parent = nullptr);
    ~ThresholdDialog();

private slots:
    void on_input_button_clicked();

private:
    Ui::ThresholdDialog *ui;
};

#endif // THRESHOLDDIALOG_H
