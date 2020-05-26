#include "database.h"
#include "congregation.h"
#include "constants.h"
#include "form_validation.h"

#include "update_congregation_dialog.h"
#include "ui_update_congregation_dialog.h"

#include <QTableWidget>
#include <QMessageBox>

using pts::constants::SPECIAL_CHARACTERS_PATTERN;

UpdateCongregationDialog::UpdateCongregationDialog(QWidget *parent, QTableWidget* congregationsTable) :
    QDialog(parent),
    ui(new Ui::UpdateCongregationDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Update Congregation Details");

    this->selectedRow = congregationsTable->selectionModel()->currentIndex().row();
    this->selectedCongregationName = congregationsTable->model()->index(this->selectedRow, 1).data().toString().toStdString();

    this->ui->newCongregationNameLineEdit->setText(QString::fromStdString(this->selectedCongregationName));
}

UpdateCongregationDialog::~UpdateCongregationDialog()
{
    delete ui;
}

void UpdateCongregationDialog::on_buttonBox_accepted()
{
    int congId = pts::PTSDatabase::getCongregationByName(this->selectedCongregationName).at(0).getId();
    std::string newCongregationName = this->ui->newCongregationNameLineEdit->text().toStdString();

    if (pts::form_validation::congregationDetailsAreValid(this, newCongregationName)) {
        pts::PTSDatabase::getStorage().update<pts::Congregation>(pts::Congregation(congId, newCongregationName));
    }
}
