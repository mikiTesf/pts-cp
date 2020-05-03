#include "excel_generator.h"
#include "congregation.h"
#include "elder.h"
#include "program.h"
#include "database.h"

#include <xlsxwriter.h>
#include <ctime>
#include <regex>

namespace pts {

ExcelGenerator::ExcelGenerator() {
    this->workbook = workbook_new("PTS.xlsx");
    this->lastRow = 0;

    int row = FIRST_SCHEDULE_ROW;
    for (std::string date : pts::PTSDatabase::getDistinctProgramDates()) {
        this->dateRowMap[date] = row;
        ++row;
    }

    this->bold10Centered = workbook_add_format(this->workbook);
    format_set_bold(this->bold10Centered);
    format_set_font_size(this->bold10Centered, 10);
    format_set_align(this->bold10Centered, LXW_ALIGN_CENTER);
    format_set_align(this->bold10Centered, LXW_ALIGN_VERTICAL_CENTER);

    this->regular10left = workbook_add_format(this->workbook);
    format_set_font_size(this->regular10left, 10);
    format_set_align(this->regular10left, LXW_ALIGN_LEFT);
    format_set_align(this->regular10left, LXW_ALIGN_VERTICAL_CENTER);

    this->regular10center = workbook_add_format(this->workbook);
    format_set_font_size(this->regular10center, 10);
    format_set_align(this->regular10center, LXW_ALIGN_CENTER);
    format_set_align(this->regular10center, LXW_ALIGN_VERTICAL_CENTER);
};

lxw_workbook* ExcelGenerator::getWorkbook() {
    return this->workbook;
}

void ExcelGenerator::insertCongregationName(lxw_worksheet* sheet, std::string congName) {
    worksheet_merge_range(sheet, 0, 0, 0, 4, congName.c_str(), this->bold10Centered);
}

void ExcelGenerator::insertColumnsAndElderNames(lxw_worksheet* sheet, int congregationId) {
    int row = 1, col = 0;

    worksheet_write_string(sheet, row, col++, "ሳምንት", this->bold10Centered);
    worksheet_write_string(sheet, row, col++, "ቀን", this->bold10Centered);
    worksheet_write_string(sheet, row, col++, "ተናጋሪ", this->bold10Centered);
    worksheet_write_string(sheet, row, col++, "የንግግር ቁ.", this->bold10Centered);
    worksheet_write_string(sheet, row, col++, "የሞባይል ስ.ቁ.", this->bold10Centered);

    std::vector<Elder> elders = pts::PTSDatabase::getAllEnabledEldersOfCongregation(congregationId);
    std::string fullName;
    int talkNumber;

    for (pts::Elder elder : elders) {
        talkNumber = pts::PTSDatabase::getStorage().get<Talk>(elder.getTalkId()).getTalkNumber();
        fullName = elder.getFirstName() + " " + elder.getMiddleName() +
                "\n(ንግግር ቁ. " + std::to_string(talkNumber) + ")";
        worksheet_write_string(sheet, row, col, fullName.c_str(), bold10Centered);
        this->elderColumnMap[elder.getId()] = col;
        ++col;
    }

    worksheet_merge_range(sheet, 0, 5, 0, col - 1, "ከጉባኤ የሚሄዱ", bold10Centered);
}

void ExcelGenerator::insertWeekNumberAndDates(lxw_worksheet* sheet, std::vector<std::string> dates) {
    int row = FIRST_SCHEDULE_ROW, weekNumber = 1;
    std::regex pattern(" [0-9:\\.]+");
    tm tm1;

    sscanf(dates[0].c_str(),"%4d-%2d-%2d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    int previousDateMonth = tm1.tm_mon;

    for (std::string date : dates) {
        sscanf(date.c_str(),"%4d-%2d-%2d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);

        if (tm1.tm_mon != previousDateMonth) { weekNumber = 1; }

        worksheet_write_number(sheet, row, 0, weekNumber, this->regular10center);
        date = std::regex_replace(date, pattern, "");
        worksheet_write_string(sheet, row, 1, date.c_str(), this->regular10left);

        previousDateMonth = tm1.tm_mon;
        ++row; ++weekNumber;
    }

    this->lastRow = row;
}

void ExcelGenerator::insertSpeakersDetails(lxw_worksheet* sheet, std::vector<Program> programsForCongregation) {
    int row = FIRST_SCHEDULE_ROW, col = 2;

    for (Program program : programsForCongregation) {
        if (!program.getFree()) {
            pts::Elder elder = pts::PTSDatabase::getStorage().get<Elder>(program.getElderId());
            pts::Talk talk = pts::PTSDatabase::getStorage().get<Talk>(elder.getTalkId());
            std::string elderFullName = elder.getFirstName() + " " + elder.getMiddleName();

            worksheet_write_string(sheet, row, col    , elderFullName.c_str(), this->regular10left);
            worksheet_write_number(sheet, row, col + 1, talk.getTalkNumber(), this->regular10left);
            worksheet_write_string(sheet, row, col + 2, elder.getPhoneNumber().c_str(), this->regular10left);
        }
        ++row;
    }
}

void ExcelGenerator::insertCongregationsForElderGoingOut(lxw_worksheet* sheet, int congregationId) {
    int row, col;
    std::string congregationName;

    for (Elder elder : pts::PTSDatabase::getAllEnabledEldersOfCongregation(congregationId)) {
        std::vector<pts::Program> programs = pts::PTSDatabase::getTalksByElder(elder.getId());
        col = this->elderColumnMap.at(elder.getId());

        for (Program program : programs) {
            row = this->dateRowMap.at(program.getDate());
            congregationName = pts::PTSDatabase::getStorage().get<pts::Congregation>(program.getCongregationId()).getName();
            worksheet_write_string(sheet, row, col, congregationName.c_str(), this->regular10center);
        }
    }
}

void ExcelGenerator::insertInstructionMessage(lxw_worksheet* sheet) {
    int row = this->lastRow;
    lxw_format* bold11 = workbook_add_format(this->workbook);
    format_set_bold(bold11);
    format_set_font_size(bold11, 11);

    lxw_format* regular10 = workbook_add_format(this->workbook);
    format_set_font_size(regular10, 10);

    row++; worksheet_merge_range(sheet, row, 0, row, 7, "ለአስተባባሪው", bold11);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "እባክህ ተጋባዥ ተናጋሪውን እጅግ ቢዘገይ እስከ ማክሰኞ ደውለህ አስታውሰው።", regular10);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "ይህን ፕሮግራም እንደደረሰህ እባክህ ከጉባኤህ ውስጥ ለተመደቡት ተናጋሪዎች ፎቶ ኮፒ አድርገህ መስጠትህን አትዘንጋ።", regular10);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "ለተናጋሪዎች", bold11);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "1. ንግግሩ እንደደረሰህ ዝግጅትህን በማጠናቀቅ በፕሮግራምህ መሠረት ንግግርህን መስጠት ይጠበቅብሃል፡፡", regular10);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "2. ዝግጅት ስታደርግ ማስተካከያ የተደረገበትን ትምህርት ለመጠቀምህ እርግጠኛ ሁን።", regular10);
    row++; worksheet_merge_range(sheet, row, 0, row, 7, "3. ንግግር በምትሰጥበት ቀን የተለየ ፕሮግራም ካለህ እባክህ አስቀድመህ ንግግር ለምታቀርብበት ጉባኤ አስተባባሪ ንገር።", regular10);
}

}
