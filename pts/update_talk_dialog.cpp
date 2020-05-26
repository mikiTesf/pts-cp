#include "database.h"
#include "constants.h"
#include "form_validation.h"

#include "update_talk_dialog.h"
#include "ui_update_talk_dialog.h"

#include <QString>
#include <QMessageBox>
#include <regex>
#include <iostream>

using pts::constants::SPECIAL_CHARACTERS_PATTERN;

UpdateTalkDialog::UpdateTalkDialog(QWidget *parent, QTableWidget* talkTableWidget) :
    QDialog(parent),
    ui(new Ui::UpdateTalkDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("Update Talk Details"));

    this->selectedRow = talkTableWidget->selectionModel()->currentIndex().row();
    this->selectedTalkNumber = talkTableWidget->model()->index(this->selectedRow, 0).data().toInt();
    this->selectedTalkTitle = talkTableWidget->model()->index(this->selectedRow, 1).data().toString().toStdString();

    this->ui->newTalkNumberSpinBox->setValue(selectedTalkNumber);
    this->ui->newTalkTitleLineEdit->setText(QString::fromStdString(selectedTalkTitle));
}

UpdateTalkDialog::~UpdateTalkDialog()
{
    delete ui;
}

void UpdateTalkDialog::on_buttonBox_accepted()
{
    int talkId = pts::PTSDatabase::getTalkByTalkNumber(this->selectedTalkNumber).at(0).getId();
    int talkNumber = this->ui->newTalkNumberSpinBox->value();
    std::string talkTitle = this->ui->newTalkTitleLineEdit->text().toStdString();

    if (pts::form_validation::talkDetailsAreValid(this, talkTitle, talkNumber)) {
        pts::PTSDatabase::getStorage().update<pts::Talk>(pts::Talk(talkId, talkNumber, talkTitle));
    }
}
