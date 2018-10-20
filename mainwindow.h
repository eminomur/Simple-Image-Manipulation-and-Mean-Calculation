#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionInfo_triggered();

    void on_select_image_button_clicked();

    void on_show_current_image_button_clicked();

    void on_show_grayscale_button_clicked();

    void on_swap_red_and_green_bands_button_clicked();

    void on_swap_green_and_blue_bands_button_clicked();

    void on_actionExit_triggered();

    void on_add_or_subtract_intensity_button_clicked();

    void on_convert_to_binary_button_clicked();

    void on_calculate_average_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
