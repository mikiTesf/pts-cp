#ifndef UPDATE_CONGREGATION_DIALOG_H
#define UPDATE_CONGREGATION_DIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class UpdateCongregationDialog;
}

class UpdateCongregationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateCongregationDialog(QWidget *parent = nullptr, QTableWidget* congregationsTable = nullptr);
    ~UpdateCongregationDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::UpdateCongregationDialog *ui;
    int selectedRow;
    std::string selectedCongregationName;
};

#endif // UPDATE_CONGREGATION_DIALOG_H
