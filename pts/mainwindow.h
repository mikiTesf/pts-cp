#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>

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

    void refreshAndShowEldersList();

    void refreshAndShowTalksList();

    void refreshAndShowCongregationsList();

    void refreshCongregationsComboBox();

    void refreshTalksComboBox();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
