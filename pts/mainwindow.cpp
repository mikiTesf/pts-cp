#include "database.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

using  pts::PTSDatabase;

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addCongragationButton_clicked()
{
    //TODO add validation here
    QString congregationName = this->ui->congregationNameTextField->text();
    pts::Congregation congregation = pts::Congregation(congregationName.toUtf8().toStdString());
    PTSDatabase::save(congregation);
    this->ui->congregationNameTextField->clear();
    refreshAndShowTalksList();
    refreshAndShowCongregationsList();

}

void MainWindow::on_congregationNameTextField_returnPressed()
{
    on_addCongragationButton_clicked();
}

void MainWindow::on_addTalkButton_clicked()
{
    //TODO add validation for duplicateshere here
    QString talkTitle = this->ui->talkTitleTextField->text();
    int talkNumber = this->ui->talkNumberSpinner->value();
    pts::Talk talk = pts::Talk(talkTitle.toUtf8().toStdString(), talkNumber);
    PTSDatabase::save(talk);
    this->ui->talkTitleTextField->clear();
    this->ui->talkNumberSpinner->clear();
    refreshAndShowTalksList();
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
        QString id = QVariant(cong.getId()).toString();
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
    headers <<"Talk Number"<<"Title";

    talksTable->setHorizontalHeaderLabels(headers);

    int row = 0;
    for(auto &talk: allTalks) {
        QString talkNumber = QVariant(talk.getTalkNumber()).toString();
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
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    auto elderTable = this->ui->elderTable;
    auto allElders = PTSDatabase::getAllElders();
    elderTable->clear();
    elderTable->setRowCount(allElders.size());
    elderTable->setColumnCount(7);
    // first_name, middle_name, last_name, phone_number, talk_id, congregation_id, enabled
    elderTable->verticalHeader()->setVisible(false);

    QStringList headers;
    headers << "First Name" << "Middle Name" << "Last Name" << "Phone Number" << "Talk Number" << "Congregation" << "Enabled";

    elderTable->setHorizontalHeaderLabels(headers);

    int row = 0;
    std::string str;
    for(auto &elder: allElders) {
        elderTable->setItem(row, 0,  new QTableWidgetItem(QString::fromStdString(elder.getFirstName())));
        elderTable->setItem(row, 1,  new QTableWidgetItem(QString::fromStdString(elder.getMiddleName())));
        elderTable->setItem(row, 2,  new QTableWidgetItem(QString::fromStdString(elder.getLastName())));
        elderTable->setItem(row, 3,  new QTableWidgetItem(QString::fromStdString(elder.getPhoneNumber())));

        str = std::to_string(PTSDatabase::getTalk(elder.getTalkId()).getTalkNumber());
        elderTable->setItem(row, 4,  new QTableWidgetItem(QString::fromStdString(str)));
        str = PTSDatabase::getCongregation (elder.getCongregationId()).getName();
        elderTable->setItem(row, 5,  new QTableWidgetItem(QString::fromStdString(str)));

        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        if (elder.getEnabled()) {
            checkBoxItem->setCheckState(Qt::Checked);
        } else {
            checkBoxItem->setCheckState(Qt::Unchecked);
        }
        elderTable->setItem(row, 6, checkBoxItem);
        row++;
    }
}

void MainWindow::refreshCongregationsComboBox()
{
    ui->congregationsComboBox->clear();

    QStringList congregationsList;
    auto allCongregations = PTSDatabase::getAllCongregations();

    for (auto &congregation : allCongregations) {
        congregationsList << (QString::fromStdString(congregation.getName()));
    }

    ui->congregationsComboBox->addItems(congregationsList);
}

void MainWindow::refreshTalksComboBox()
{
    ui->talksComboBox->clear();

    QStringList talksList;
    QString talkNumberPlusTitle;
    auto allTalks = PTSDatabase::getAllTalks();

    for (auto &talk : allTalks) {
        talkNumberPlusTitle = QString::fromStdString(std::to_string(talk.getTalkNumber()) + " — " + talk.getTalkTitle());
        talksList << talkNumberPlusTitle;
    }

    ui->talksComboBox->addItems(talksList);
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

}
