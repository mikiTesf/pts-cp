#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

using  pts::PTSDatabase;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Public Talk Scheduler");
    refreshAndShowCongregationsList();
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

void MainWindow::refreshAndShowEldersList(){

}

void MainWindow::refreshAndShowTalksList(){


    auto talksTable = this->ui->tableWidget;
    auto allTalks = PTSDatabase::getAllTalks();
    talksTable->clear();
    talksTable->setRowCount(allTalks.size());
    talksTable->setColumnCount(2);
    talksTable->verticalHeader()->setVisible(false);

    QStringList headers;
    headers <<"Talk Number"<<"Title";

    talksTable->setHorizontalHeaderLabels(headers);

    int index = 0;
    for(auto &talk: allTalks) {
        QString talkNumber = QVariant(talk.getTalkNumber()).toString();
        talksTable->setItem(index, 0,  new QTableWidgetItem(talkNumber));
        talksTable->setItem(index, 1,  new QTableWidgetItem(talk.getTalkTitle().c_str()));
        index++;
    }
}

void MainWindow::refreshAndShowCongregationsList(){

    auto congTable = this->ui->congregationTable;
    auto allCongregations = PTSDatabase::getAllCongregations();
    congTable->clear();
    congTable->setRowCount(allCongregations.size());
    congTable->setColumnCount(2);
    congTable->verticalHeader()->setVisible(false);

    QStringList headers;
    headers <<"#"<<"Name";

    congTable->setHorizontalHeaderLabels(headers);

    int index = 0;
    for(auto &cong: allCongregations) {
        QString id = QVariant(cong.getId()).toString();
        congTable->setItem(index, 0,  new QTableWidgetItem(id));
        congTable->setItem(index, 1,  new QTableWidgetItem(cong.getName().c_str()));
        index++;
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
    }

}
