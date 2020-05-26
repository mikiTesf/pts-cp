#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QTableWidget>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_addCongragationButton_clicked();
    void on_congregationNameTextField_returnPressed();
    void on_addTalkButton_clicked();
    void on_tabWidget_tabBarClicked(int index);
    void on_deleteCongregationButton_clicked();
    void on_updateTalkButton_clicked();
    void on_deleteTalkButton_clicked();
    void on_updataeCongregationButton_clicked();
    void on_addElderButton_clicked();
    void on_deleteElderButton_clicked();
    void on_updateElderButton_clicked();
    void on_talkTable_cellClicked(int row, int column);
    void on_congregationTable_cellClicked(int row, int column);
    void on_elderTable_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    void refreshAndShowEldersList();
    void refreshAndShowTalksList();
    void refreshAndShowCongregationsList();
    void refreshCongregationsComboBox();
    void refreshTalksComboBox();
    QTableWidget* getCongregationTable();
    QTableWidget* getTalkTable();
    QTableWidget* getElderTable();
    void toggleUpdateAndDeleteButtons(bool);
};

#endif // MAINWINDOW_H
