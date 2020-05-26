#ifndef UPDATE_ELDER_DIALOG_H
#define UPDATE_ELDER_DIALOG_H

#include <QDialog>
#include <QTableWidget>

#include <QString>

namespace Ui {
class UpdateElderDialog;
}

class UpdateElderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateElderDialog(QWidget *parent = nullptr, QTableWidget* eldersTable = nullptr);
    ~UpdateElderDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::UpdateElderDialog *ui;
    int selectedRow;
    QString selectedFirstName;
    QString selectedMiddleName;
    QString selectedLastName;
    QString selectedPhoneNumber;
    int selectedTalkNumber;
    QString selectedCongregationName;
    bool elderEnabledStatus;

    void refreshTalksComboBox();
    void refreshCongregationsComboBox();
};

#endif // UPDATE_ELDER_DIALOG_H
