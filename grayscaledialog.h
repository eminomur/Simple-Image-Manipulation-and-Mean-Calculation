#ifndef GRAYSCALEDIALOG_H
#define GRAYSCALEDIALOG_H

#include <QDialog>

namespace Ui {
class GrayscaleDialog;
}

class GrayscaleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GrayscaleDialog(QWidget *parent = nullptr);
    ~GrayscaleDialog();

private slots:
    void on_input_button_clicked();

private:
    Ui::GrayscaleDialog *ui;
};

#endif // GRAYSCALEDIALOG_H
