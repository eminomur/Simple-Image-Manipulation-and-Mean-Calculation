#ifndef AVERAGEIMAGEDIALOG_H
#define AVERAGEIMAGEDIALOG_H

#include <QDialog>
#include <string>
#include <stack>

namespace Ui {
class AverageImageDialog;
}

class AverageImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AverageImageDialog(QWidget *parent = nullptr);
    ~AverageImageDialog();

private slots:
    void on_delete_the_latest_added_item_button_clicked();

    void on_clean_all_button_clicked();

    void on_add_new_item_button_clicked();

    void on_calculate_button_clicked();

private:
    Ui::AverageImageDialog *ui;
    std::stack<std::string> list_of_image_locations;

    void set_message_in_label();
};

#endif // AVERAGEIMAGEDIALOG_H
