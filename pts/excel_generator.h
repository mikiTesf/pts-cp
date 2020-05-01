#ifndef EXCEL_GENERATOR_H
#define EXCEL_GENERATOR_H

#include "elder.h"

#include <xlsxwriter.h>
#include <string>
#include <vector>

namespace pts {

class ExcelGenerator
{
private:
    lxw_workbook *workbook;
    int lastRow;
public:
    ExcelGenerator();

    void insertCongregationName(lxw_worksheet*, std::string);

    void insertColumnsAndElderNames(lxw_worksheet*, std::vector<pts::Elder>);

    void insertTalkRow(lxw_worksheet*);

    void insertInstructionMessage(lxw_worksheet*);
};

} // end of namespace

#endif // EXCEL_GENERATOR_H
