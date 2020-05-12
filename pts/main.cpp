#include "constants.h"
#include "mainwindow.h"
#include "database.h"

#include "excel_generator.h"
#include "elder.h"

#include <QApplication>
#include <iostream>
#include <vector>

using namespace pts;
using sqlite_orm::where;
using sqlite_orm::c;

int main(int argc, char *argv[])
{
//    // initialize database
//    PTSDatabase::init();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//    //return 0;

    pts::ExcelGenerator excelGenerator;
    lxw_workbook* workbook = excelGenerator.getWorkbook();

    for (auto congregation : pts::PTSDatabase::getAllCongregations()) {
        lxw_worksheet* worksheet = workbook_add_worksheet(workbook, congregation.getName().c_str());

        std::vector<Elder> elders = pts::PTSDatabase::getStorage()
                .get_all<Elder>(where(c(&Elder::getCongregationId) = congregation.getId()));

        std::cout << "inserting congregation name...(" << congregation.getName() << ")" << std::endl;
        excelGenerator.insertCongregationNameAndDefaultColumns(worksheet, congregation.getName().c_str());
        std::cout << "inserting columns and elders names..." << std::endl;
        excelGenerator.insertNamesOfEldersGoingOut(worksheet, congregation.getId());
        std::cout << "Inserting week numbers and dates" << std::endl;
        excelGenerator.insertWeekNumberAndDates(worksheet, pts::PTSDatabase::getDistinctProgramDates());
        std::cout << "inserting speaker details..." << std::endl;
        excelGenerator.insertSpeakersDetails(worksheet, pts::PTSDatabase::getTalksForCongregation(congregation.getId()));
        std::cout << "inserting congregation names for elders leaving...(" << congregation.getName() << ")" << std::endl;
        excelGenerator.insertCongregationsForElderGoingOut(worksheet, congregation.getId());
        std::cout << "inserting instruction messages..." << std::endl;
        excelGenerator.insertInstructionMessage(worksheet);
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

    std::cout << "saving workbook..." << std::endl;
    workbook_close(workbook);

    return 0;
}
