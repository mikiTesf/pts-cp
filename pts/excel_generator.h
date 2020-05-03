#ifndef EXCEL_GENERATOR_H
#define EXCEL_GENERATOR_H

#include "elder.h"
#include "program.h"

#include <xlsxwriter.h>
#include <string>
#include <vector>
#include <map>

namespace pts {

class ExcelGenerator
{
private:
    lxw_workbook *workbook;
    const int FIRST_SCHEDULE_ROW = 2;
    int lastRow;
    // The map below (`elderColumnMap`) is used to identify on which column the elder of a
    // congregation is so that, later, when the congregation to which the elder is going to
    // go to are placedit will be easier to know where to put them.
    std::map<int, int> elderColumnMap;
    // The following map (`dateRowMap`) is important to identify the row that a date is on. Using the date
    // in a pts::Program object, and paired with the map above (`elderColumnMap`), the task of finding the
    // cell at which the congregation that an elder will be going to is placed becomes easy.
    std::map<std::string, int> dateRowMap;
public:
    ExcelGenerator();

    lxw_workbook* getWorkbook();

    void insertCongregationName(lxw_worksheet*, std::string);

    void insertColumnsAndElderNames(lxw_worksheet*, int);

    void insertWeekNumberAndDates(lxw_worksheet*, std::vector<std::string>);

    void insertSpeakersDetails(lxw_worksheet*, std::vector<pts::Program>);

    void insertCongregationsForElderGoingOut(lxw_worksheet*, int);

    void insertInstructionMessage(lxw_worksheet*);
};

} // end of namespace

#endif // EXCEL_GENERATOR_H
