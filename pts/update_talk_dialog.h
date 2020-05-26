#ifndef UPDATE_TALK_DIALOG_H
#define UPDATE_TALK_DIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <string>

namespace Ui {
class UpdateTalkDialog;
}

class UpdateTalkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateTalkDialog(QWidget *parent = nullptr, QTableWidget* talkTableWidget = nullptr);
    ~UpdateTalkDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::UpdateTalkDialog *ui;
    int selectedRow;
    int selectedTalkNumber;
    std::string selectedTalkTitle;
};

#endif // UPDATE_TALK_DIALOG_H
