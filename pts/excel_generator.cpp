#include "excel_generator.h"
#include "elder.h"

#include <xlsxwriter.h>

namespace pts {

ExcelGenerator::ExcelGenerator() {
    this->workbook = workbook_new("PTS.xlsx");
    this->lastRow = 0;
};

lxw_workbook* ExcelGenerator::getWorkbook() {
    return this->workbook;
}

void ExcelGenerator::insertCongregationName(lxw_worksheet* sheet, std::string congName) {
    lxw_format* bold = workbook_add_format(this->workbook);
    format_set_bold(bold);
    worksheet_merge_range(sheet, 0, 0, 0, 4, congName.c_str(), bold);
}

void ExcelGenerator::insertColumnsAndElderNames(lxw_worksheet* sheet, std::vector<pts::Elder> elders) {
    int row = 1, col = 0;
    lxw_format* bold = workbook_add_format(this->workbook);
    format_set_bold(bold);

    worksheet_write_string(sheet, row, col++, "ሳምንት", bold);
    worksheet_write_string(sheet, row, col++, "ቀን", bold);
    worksheet_write_string(sheet, row, col++, "ተናጋሪ", bold);
    worksheet_write_string(sheet, row, col++, "የንግግር ቁ.", bold);
    worksheet_write_string(sheet, row, col++, "የሞባይል ስ.ቁ.", bold);

    std::string fullName;

    for (pts::Elder elder : elders) {
        fullName = elder.getFirstName() + " " + elder.getMiddleName();
        worksheet_write_string(sheet, row, col++, fullName.c_str(), bold);
    }

    worksheet_merge_range(sheet, 0, 5, 0, col - 1, "ከጉባኤ የሚሄዱ", bold);
}

void ExcelGenerator::insertTalkRow(lxw_worksheet* sheet) {
    // Set this->lastRow to help the `insertInstructionMessage(...)` function indetermining where to
    // put the message. Doing this is neccessary as the span of the schedule is not always the same
}

void ExcelGenerator::insertInstructionMessage(lxw_worksheet* sheet) {
    int row = this->lastRow + 1;
    lxw_format* bold = workbook_add_format(this->workbook);
    format_set_bold(bold);

    row++; worksheet_merge_range(sheet, row, 0, row, 7, "ለአስተባባሪው", bold);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "እባክህ ተጋባዥ ተናጋሪውን እጅግ ቢዘገይ እስከ ማክሰኞ ደውለህ አስታውሰው።", NULL);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "ይህን ፕሮግራም እንደደረሰህ እባክህ ከጉባኤህ ውስጥ ለተመደቡት ተናጋሪዎች ፎቶ ኮፒ አድርገህ መስጠትህን አትዘንጋ።", NULL);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "ለተናጋሪዎች", bold);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "1. ንግግሩ እንደደረሰህ ዝግጅትህን በማጠናቀቅ በፕሮግራምህ መሠረት ንግግርህን መስጠት ይጠበቅብሃል፡፡", NULL);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "2. ዝግጅት ስታደርግ ማስተካከያ የተደረገበትን ትምህርት ለመጠቀምህ እርግጠኛ ሁን።", NULL);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "3. ንግግር በምትሰጥበት ቀን የተለየ ፕሮግራም ካለህ እባክህ አስቀድመህ ንግግር ለምታቀርብበት ጉባኤ አስተባባሪ ንገር።", NULL);
}

}
