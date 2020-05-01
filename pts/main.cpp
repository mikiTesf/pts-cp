#include "constants.h"
#include "mainwindow.h"
#include "database.h"

#include "excel_generator.h"
#include "elder.h"

#include <QApplication>
#include <iostream>
#include <vector>

using namespace pts;

int main(int argc, char *argv[])
{
//    // initialize database
//    PTSDatabase::init();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//    //return 0;

    const std::string CONG_NAME = "Addis Sefer";

    lxw_workbook* workbook = workbook_new("PTS.xlsx");
    lxw_worksheet* worksheet = workbook_add_worksheet(workbook, CONG_NAME.c_str());

    Elder James("James", "Jasper", "Gerund", "0222", 1, 1, true);
    Elder Jones("Jones", "Jerud", "Jerk", "0111", 1, 1, true);
    Elder Jonah("Clark", "Click", "Cunt", "0333", 1, 1, true);

    std::vector<Elder> elders = {James, Jones, Jonah};

    pts::ExcelGenerator excelGenerator;

    std::cout << "inserting congregation name..." << std::endl;
    excelGenerator.insertCongregationName(worksheet, CONG_NAME.c_str());
    std::cout << "inserting columns and elders names..." << std::endl;
    excelGenerator.insertColumnsAndElderNames(worksheet, elders);
    std::cout << "inserting instruction messages..." << std::endl;
    excelGenerator.insertInstructionMessage(worksheet);
    std::cout << "saving workbook..." << std::endl;
    workbook_close(workbook);

    return 0;
}
