#include "database.h"
#include "elder.h"
#include "constants.h"
#include "form_validation.h"

#include "update_elder_dialog.h"
#include "ui_update_elder_dialog.h"

#include <QTableWidget>
#include <QMessageBox>
#include <QCheckBox>
#include <iostream>

UpdateElderDialog::UpdateElderDialog(QWidget *parent, QTableWidget* eldersTable) :
    QDialog(parent),
    ui(new Ui::UpdateElderDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Update Elder Details");

    this->selectedRow = eldersTable->selectionModel()->currentIndex().row();
    this->selectedFirstName = eldersTable->model()->index(this->selectedRow, 1).data().toString();
    this->selectedMiddleName = eldersTable->model()->index(this->selectedRow, 2).data().toString();
    this->selectedLastName = eldersTable->model()->index(this->selectedRow, 3).data().toString();
    this->selectedPhoneNumber = eldersTable->model()->index(this->selectedRow, 4).data().toString();
    this->selectedTalkNumber = eldersTable->model()->index(this->selectedRow, 5).data().toInt();
    this->selectedCongregationName = eldersTable->model()->index(this->selectedRow, 6).data().toString();

    QCheckBox *cb = qobject_cast<QCheckBox *>(eldersTable->cellWidget(this->selectedRow, 7));
    this->elderEnabledStatus = cb->isChecked();

    this->ui->newFirstNameLineEdit->setText(this->selectedFirstName);
    this->ui->newMiddleNameLineEdit->setText(this->selectedMiddleName);
    this->ui->newLastNameLineEdit->setText(this->selectedLastName);
    this->ui->newPhoneNumberLineEdit->setText(this->selectedPhoneNumber);

    this->refreshCongregationsComboBox();
    int index = this->ui->newCongregationComboBox->findData(selectedCongregationName);
    this->ui->newCongregationComboBox->setCurrentIndex(index);

    this->refreshTalksComboBox();
    index = this->ui->newTalkNumberComboBox->findData(this->selectedTalkNumber);
    this->ui->newTalkNumberComboBox->setCurrentIndex(index);

    this->ui->newEnabledStatusCheckbox->setChecked(this->elderEnabledStatus);
}

UpdateElderDialog::~UpdateElderDialog()
{
    delete ui;
}

void UpdateElderDialog::refreshCongregationsComboBox()
{
    this->ui->newCongregationComboBox->clear();

    for (auto &congregation : pts::PTSDatabase::getAllCongregations()) {
        this->ui->newCongregationComboBox->addItem(QString::fromStdString(congregation.getName()), QString::fromStdString(congregation.getName()));
    }
}

void UpdateElderDialog::refreshTalksComboBox()
{
    this->ui->newTalkNumberComboBox->clear();

    QString talkNumberPlusTitle;

    for (auto &talk : pts::PTSDatabase::getAllTalks()) {
        talkNumberPlusTitle = QString::fromStdString(std::to_string(talk.getTalkNumber()) + " — " + talk.getTalkTitle());
        this->ui->newTalkNumberComboBox->addItem(talkNumberPlusTitle, talk.getTalkNumber());
    }
}

void UpdateElderDialog::on_buttonBox_accepted()
{
    std::string newFirstName = this->ui->newFirstNameLineEdit->text().toStdString();
    std::string newMiddleName = this->ui->newMiddleNameLineEdit->text().toStdString();
    std::string newLastName = this->ui->newLastNameLineEdit->text().toStdString();
    std::string newPhoneNumber = this->ui->newPhoneNumberLineEdit->text().toStdString();
    std::string newlySelectedTalk = this->ui->newTalkNumberComboBox->currentText().toStdString();
    std::string newlySelectedCongregation = this->ui->newCongregationComboBox->currentText().toStdString();
    bool newElderEnabledStatus = this->ui->newEnabledStatusCheckbox->isChecked();

    int indexOfDash = newlySelectedTalk.find_first_of(" —");
    int talkNumber = std::atoi(newlySelectedTalk.substr(0, indexOfDash).c_str());
    int newTalkId = pts::PTSDatabase::getTalkByTalkNumber(talkNumber).at(0).getId();

    int newCongregationId = pts::PTSDatabase::getCongregationByName(newlySelectedCongregation).at(0).getId();

    if (pts::form_validation::elderDetailsAreValid(
                this, this->selectedTalkNumber, newFirstName, newMiddleName, newLastName, newPhoneNumber))
    {
        pts::Elder elder = pts::PTSDatabase::getElderByPhoneNumber(this->selectedPhoneNumber.toStdString());
        elder.setFirstName(newFirstName);
        elder.setMiddleName(newMiddleName);
        elder.setLastName(newLastName);
        elder.setPhoneNumber(newPhoneNumber);
        elder.setTalkId(newTalkId);
        elder.setCongregationId(newCongregationId);
        elder.setEnabled(newElderEnabledStatus);

        pts::PTSDatabase::getStorage().update<pts::Elder>(elder);
    }
}
