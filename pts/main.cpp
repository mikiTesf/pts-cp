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
    excelGenerator.generateExcelDocument();
    std::cout << "saving workbook..." << std::endl;
    workbook_close(workbook);

    return 0;
}
