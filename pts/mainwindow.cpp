#include "database.h"
#include "elder.h"
#include "constants.h"
#include "form_validation.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "update_talk_dialog.h"
#include "update_congregation_dialog.h"
#include "update_elder_dialog.h"

#include <QMessageBox>
#include <QCheckBox>
#include <regex>

using pts::PTSDatabase;
using pts::Congregation;
using pts::Elder;
using pts::Talk;

using pts::constants::SPECIAL_CHARACTERS_PATTERN;
using pts::constants::PHONE_NUMBER_PATTERN;

using sqlite_orm::where;
using sqlite_orm::c;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Public Talk Scheduler");
    refreshAndShowCongregationsList();
    refreshAndShowTalksList();
    refreshAndShowEldersList();

    ui->congregationTable->setColumnWidth(0, this->width() / 5);
    ui->congregationTable->horizontalHeader()->setStretchLastSection(true);
    ui->talkTable->setColumnWidth(0, this->width() / 4);
    ui->talkTable->horizontalHeader()->setStretchLastSection(true);
    ui->elderTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->congregationTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->talkTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->elderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->toggleUpdateAndDeleteButtons(false);

    connect(this->ui->elderTable, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_talkTable_cellClicked()));
    connect(this->ui->talkTable, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_talkTable_cellClicked()));
    connect(this->ui->congregationTable, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_talkTable_cellClicked()));

    this->showMaximized();
}

void MainWindow::toggleUpdateAndDeleteButtons(bool state) {
    this->ui->deleteTalkButton->setEnabled(state);
    this->ui->updateTalkButton->setEnabled(state);

    this->ui->deleteCongregationButton->setEnabled(state);
    this->ui->updateCongregationButton->setEnabled(state);

    this->ui->deleteElderButton->setEnabled(state);
    this->ui->updateElderButton->setEnabled(state);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTableWidget* MainWindow::getCongregationTable() {
    return this->ui->congregationTable;
}

QTableWidget* MainWindow::getTalkTable() {
    return this->ui->talkTable;
}

QTableWidget* MainWindow::getElderTable() {
    return this->ui->elderTable;
}

void MainWindow::on_addCongragationButton_clicked()
{
    QString congregationName = this->ui->congregationNameTextField->text();

    if (pts::form_validation::congregationDetailsAreValid(this, congregationName.toStdString()))
    {
        Congregation congregation = Congregation(congregationName.toStdString());
        PTSDatabase::save(congregation);

        this->ui->congregationNameTextField->clear();
        refreshAndShowCongregationsList();
    }
}

void MainWindow::on_congregationNameTextField_returnPressed()
{
    on_addCongragationButton_clicked();
}

void MainWindow::on_addTalkButton_clicked()
{
    QString insertedTitle = this->ui->talkTitleTextField->text();
    int talkNumber = this->ui->talkNumberSpinner->value();

    if (pts::form_validation::talkDetailsAreValid(this, insertedTitle.toStdString(), talkNumber))
    {
        pts::Talk talk = pts::Talk(insertedTitle.toStdString(), talkNumber);
        PTSDatabase::save(talk);
        this->ui->talkTitleTextField->clear();
        this->ui->talkNumberSpinner->clear();
        refreshAndShowTalksList();
    }
}

void MainWindow::refreshAndShowCongregationsList()
{
    auto congTable = this->ui->congregationTable;
    auto allCongregations = PTSDatabase::getAllCongregations();
    congTable->clear();
    congTable->setRowCount(allCongregations.size());
    congTable->setColumnCount(2);
    congTable->verticalHeader()->setVisible(false);

    QStringList headers;
    headers << "#" << "Name" ;

    congTable->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (auto &cong: allCongregations) {
        QString id = QString::number(cong.getId());
        congTable->setItem(row, 0,  new QTableWidgetItem(id));
        congTable->setItem(row, 1,  new QTableWidgetItem(cong.getName().c_str()));
        row++;
    }

}

void MainWindow::refreshAndShowTalksList()
{
    auto talksTable = this->ui->talkTable;
    auto allTalks = PTSDatabase::getAllTalks();
    talksTable->clear();
    talksTable->setRowCount(allTalks.size());
    talksTable->setColumnCount(2);
    talksTable->verticalHeader()->setVisible(false);

    QStringList headers;
    headers << "Talk Number" << "Title";

    talksTable->setHorizontalHeaderLabels(headers);

    int row = 0;
    for(auto &talk: allTalks) {
        QString talkNumber = QString::number(talk.getTalkNumber());
        talksTable->setItem(row, 0,  new QTableWidgetItem(talkNumber));
        talksTable->setItem(row, 1,  new QTableWidgetItem(talk.getTalkTitle().c_str()));
        row++;
    }
}

void MainWindow::refreshAndShowEldersList()
{
    // first the ComboBoxes that are part of adding a new Elder must be refreshed
    refreshCongregationsComboBox();
    refreshTalksComboBox();

    auto elderTable = this->ui->elderTable;
    auto allElders = PTSDatabase::getAllElders();
    elderTable->clear();
    elderTable->setRowCount(allElders.size());
    elderTable->setColumnCount(8);
    elderTable->verticalHeader()->setVisible(false);

    QStringList headers;
    headers << "#" << "First Name" << "Middle Name" << "Last Name" << "Phone Number" << "Talk Number" << "Congregation" << "Enabled";

    elderTable->setHorizontalHeaderLabels(headers);

    int row = 0;
    std::string str;

    for (auto &elder : allElders) {
        elderTable->setItem(row, 0, new QTableWidgetItem(QString::number(elder.getId())));
        elderTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(elder.getFirstName())));
        elderTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(elder.getMiddleName())));
        elderTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(elder.getLastName())));
        elderTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(elder.getPhoneNumber())));

        str = std::to_string(PTSDatabase::getStorage().get<Talk>(elder.getTalkId()).getTalkNumber());
        elderTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(str)));
        str = PTSDatabase::getStorage().get<Congregation>(elder.getCongregationId()).getName();
        elderTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(str)));

        QCheckBox *checkBoxItem = new QCheckBox();

        if (elder.getEnabled()) {
            checkBoxItem->setCheckState(Qt::Checked);
        } else {
            checkBoxItem->setCheckState(Qt::Unchecked);
        }

        elderTable->setCellWidget(row, 7, checkBoxItem);
        row++;
    }
}

void MainWindow::refreshCongregationsComboBox()
{
    ui->congregationsComboBox->clear();

    for (auto &congregation : PTSDatabase::getAllCongregations()) {
        ui->congregationsComboBox->addItem(QString::fromStdString(congregation.getName()), QString::fromStdString(congregation.getName()));
    }
}

void MainWindow::refreshTalksComboBox()
{
    ui->talksComboBox->clear();

    QString talkNumberPlusTitle;

    for (auto &talk : PTSDatabase::getAllTalks()) {
        talkNumberPlusTitle = QString::fromStdString(std::to_string(talk.getTalkNumber()) + " — " + talk.getTalkTitle());
        this->ui->talksComboBox->addItem(talkNumberPlusTitle, talk.getTalkNumber());
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch (index) {
        case 0:
            refreshAndShowCongregationsList();
            break;
        case 1:
            refreshAndShowTalksList();
            break;
        case 2:
            refreshAndShowEldersList();
            break;
    }

    this->toggleUpdateAndDeleteButtons(false);
}

void MainWindow::on_deleteCongregationButton_clicked()
{
    int selectedRow = ui->congregationTable->selectedItems().first()->row();
    std::string congregationName = this->ui->congregationTable->item(selectedRow, 1)->text().toStdString();

    auto congregations = PTSDatabase::getStorage().get_all<Congregation>(where(c(&Congregation::getName) = congregationName));

    if (congregations.size() == 0) return;

    int congregationID = congregations[0].getId();
    auto eldersInCongregation = PTSDatabase::getStorage()
            .get_all<Elder>(where(c(&Elder::getCongregationId) = congregationID));

    std::string messageBoxContent = "Delete " + congregations[0].getName() + "? ";

    if (eldersInCongregation.size() != 0) {
        messageBoxContent += "The following elder(s) will also be deleted:\n";
        for (Elder &elder : eldersInCongregation) {
            messageBoxContent += "    • " + elder.getFirstName() + " " + elder.getMiddleName() + " " + elder.getLastName() + "\n";
        }
    }

    auto choice = QMessageBox::question(this, "Are you sure?", QString::fromUtf8(messageBoxContent.c_str()));

    if (choice == QMessageBox::Yes) {
        PTSDatabase::getStorage().remove<Congregation>(congregationID);

        for (Elder &elder : eldersInCongregation) {
            PTSDatabase::getStorage().remove<Elder>(elder.getId());
        }

        refreshAndShowCongregationsList();
        messageBoxContent = "\"" + congregationName + "\" deleted.";
        QMessageBox::information(this, "Success!", QString::fromUtf8(messageBoxContent.c_str()));
    }
}

void MainWindow::on_updateTalkButton_clicked()
{
    UpdateTalkDialog(this, this->ui->talkTable).exec();
    this->refreshAndShowTalksList();
    this->toggleUpdateAndDeleteButtons(false);
}

void MainWindow::on_deleteTalkButton_clicked()
{
    int selectedTalkRow = this->ui->talkTable->selectionModel()->currentIndex().row();
    int selectedTalkNumber = this->ui->talkTable->model()->index(selectedTalkRow, 0).data().toInt();
    pts::Talk talk = pts::PTSDatabase::getTalkByTalkNumber(selectedTalkNumber).at(0);

    if (QMessageBox::question(
                this,
                "Are you sure?",
                "Delete \"" + QString::fromStdString(talk.getTalkTitle()) + "\"?") == QMessageBox::StandardButton::Yes)
    {
        pts::PTSDatabase::getStorage().remove<pts::Talk>(talk.getId());
        this->refreshAndShowTalksList();
    }
}

void MainWindow::on_updataeCongregationButton_clicked()
{
    UpdateCongregationDialog(this, this->ui->congregationTable).exec();
    this->refreshAndShowCongregationsList();
    this->toggleUpdateAndDeleteButtons(false);
}

void MainWindow::on_addElderButton_clicked()
{
    std::string newFirstName = this->ui->firstNameLineEdit->text().toStdString();
    std::string newMiddleName = this->ui->middleNameLineEdit->text().toStdString();
    std::string newLastName = this->ui->lastNameLineEdit->text().toStdString();
    std::string newPhoneNumber = this->ui->phoneNumberLineEdit->text().toStdString();
    std::string selectedTalkInComboBox = this->ui->talksComboBox->currentText().toStdString();
    selectedTalkInComboBox = selectedTalkInComboBox.substr(0, selectedTalkInComboBox.find_first_of(" "));

    pts::Talk talk = pts::PTSDatabase::getTalkByTalkNumber(std::atoi(selectedTalkInComboBox.c_str())).at(0);
    pts::Congregation congregation = pts::PTSDatabase::getCongregationByName(
                this->ui->congregationsComboBox->currentText().toStdString()).at(0);

    if (pts::form_validation::elderDetailsAreValid(
                this, std::atoi(selectedTalkInComboBox.c_str()), newFirstName, newMiddleName, newLastName, newPhoneNumber))
    {
        pts::Elder elder(newFirstName, newMiddleName, newLastName, newPhoneNumber, talk.getId(), congregation.getId(), true);
        pts::PTSDatabase::save(elder);
        this->refreshAndShowEldersList();
        // clear fields
        this->ui->firstNameLineEdit->clear();
        this->ui->middleNameLineEdit->clear();
        this->ui->lastNameLineEdit->clear();
        this->ui->phoneNumberLineEdit->clear();
    }
}

void MainWindow::on_deleteElderButton_clicked()
{
    int selectedElderRow = this->ui->elderTable->selectionModel()->currentIndex().row();
    std::string selectedElderFullName =
            this->ui->elderTable->model()->index(selectedElderRow, 1).data().toString().toStdString()
            + " " +
            this->ui->elderTable->model()->index(selectedElderRow, 2).data().toString().toStdString();
    std::string selectedElderPhoneNumber = this->ui->elderTable->model()->index(selectedElderRow, 4).data().toString().toStdString();

    if (QMessageBox::question(
                this,
                "Are you sure?",
                "Delete \"" + QString::fromStdString(selectedElderFullName) + "\"?") == QMessageBox::StandardButton::Yes)
    {
        pts::PTSDatabase::removeElderByPhoneNumber(selectedElderPhoneNumber);
        this->refreshAndShowEldersList();
    }
}

void MainWindow::on_updateElderButton_clicked()
{
    UpdateElderDialog(this, this->ui->elderTable).exec();
    this->refreshAndShowEldersList();
    this->toggleUpdateAndDeleteButtons(false);
}

void MainWindow::on_talkTable_cellClicked(int row, int column)
{
    this->ui->deleteTalkButton->setEnabled(true);
    this->ui->updateTalkButton->setEnabled(true);
}

void MainWindow::on_congregationTable_cellClicked(int row, int column)
{
    this->ui->deleteCongregationButton->setEnabled(true);
    this->ui->updateCongregationButton->setEnabled(true);
}

void MainWindow::on_elderTable_cellClicked(int row, int column)
{
    this->ui->deleteElderButton->setEnabled(true);
    this->ui->updateElderButton->setEnabled(true);
}
