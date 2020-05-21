#include "excel_generator.h"
#include "congregation.h"
#include "elder.h"
#include "program.h"
#include "database.h"

#include <iostream>
#include <xlsxwriter.h>
#include <ctime>
#include <regex>

namespace pts {

ExcelGenerator::ExcelGenerator() {
    this->workbook = workbook_new("PTS.xlsx");
    this->lastRow = this->SECOND_ROW + pts::PTSDatabase::getDistinctProgramDates().size();
    this->allProgramDates = pts::PTSDatabase::getDistinctProgramDates();

    int row = FIRST_SCHEDULE_ROW;
    for (std::string date : pts::PTSDatabase::getDistinctProgramDates()) {
        this->dateRowMap[date] = row;
        ++row;
    }

    this->B_10_C_G_NTN = getCellStyle(true, 10, LXW_ALIGN_CENTER, true, LXW_BORDER_THIN, LXW_BORDER_THICK, LXW_BORDER_THIN);
    format_set_top(this->B_10_C_G_NTN, LXW_BORDER_THICK);
    this->B_10_C_G_TNN = getCellStyle(true, 10, LXW_ALIGN_CENTER, true, LXW_BORDER_THICK, LXW_BORDER_THIN, LXW_BORDER_THIN);
    format_set_top(this->B_10_C_G_TNN, LXW_BORDER_THICK);
    this->B_10_C_G_NTM = getCellStyle(true,  10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THIN,  LXW_BORDER_THICK, LXW_BORDER_MEDIUM);
    this->B_10_C_G_TNM = getCellStyle(true,  10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THICK, LXW_BORDER_THIN,  LXW_BORDER_MEDIUM);
    this->B_10_C_G_NNM = getCellStyle(true,  10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_MEDIUM);
    this->R_10_C_G_NTM = getCellStyle(false, 10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THIN,  LXW_BORDER_THICK, LXW_BORDER_MEDIUM);
    this->R_10_C_K_NTN = getCellStyle(false, 10, LXW_ALIGN_CENTER, false, LXW_BORDER_THIN,  LXW_BORDER_THICK, LXW_BORDER_THIN);
    this->R_10_L_G_NNM = getCellStyle(false, 10, LXW_ALIGN_LEFT,   true,  LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_MEDIUM);
    this->R_10_L_K_NTN = getCellStyle(false, 10, LXW_ALIGN_LEFT,   false, LXW_BORDER_THIN,  LXW_BORDER_THICK, LXW_BORDER_THIN);
    this->R_10_L_K_NNN = getCellStyle(false, 10, LXW_ALIGN_LEFT,   false, LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_THIN);
    this->R_10_C_G_NNM = getCellStyle(false, 10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_MEDIUM);
    this->R_10_C_G_TNM = getCellStyle(false, 10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THICK, LXW_BORDER_THIN,  LXW_BORDER_MEDIUM);
    this->R_10_C_K_NNN = getCellStyle(false, 10, LXW_ALIGN_CENTER, false, LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_THIN);
    this->R_10_C_K_TNN = getCellStyle(false, 10, LXW_ALIGN_CENTER, false, LXW_BORDER_THICK, LXW_BORDER_THIN,  LXW_BORDER_THIN);
    this->R_10_C_K_TNT = getCellStyle(false, 10, LXW_ALIGN_CENTER, false, LXW_BORDER_THICK, LXW_BORDER_THIN,  LXW_BORDER_THICK);
    this->R_10_C_K_NNT = getCellStyle(false, 10, LXW_ALIGN_CENTER, false, LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_THICK);
    this->R_10_C_G_NTT = getCellStyle(false, 10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THIN,  LXW_BORDER_THICK, LXW_BORDER_THICK);
    this->R_10_C_G_TNT = getCellStyle(false, 10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THICK, LXW_BORDER_THIN,  LXW_BORDER_THICK);
    this->R_10_L_G_NNT = getCellStyle(false, 10, LXW_ALIGN_LEFT,   true,  LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_THICK);
    this->R_10_C_G_NNT = getCellStyle(false, 10, LXW_ALIGN_CENTER, true,  LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_THICK);
    this->R_10_C_K_NTT = getCellStyle(false, 10, LXW_ALIGN_CENTER, false, LXW_BORDER_THIN,  LXW_BORDER_THICK, LXW_BORDER_THICK);
    this->R_10_L_K_NNT = getCellStyle(false, 10, LXW_ALIGN_LEFT,   false, LXW_BORDER_THIN,  LXW_BORDER_THIN,  LXW_BORDER_THICK);

    this->instructionMessageTitleFormat = workbook_add_format(this->workbook);
    format_set_bold(instructionMessageTitleFormat);
    format_set_font_size(instructionMessageTitleFormat, 11);
    format_set_underline(instructionMessageTitleFormat, LXW_UNDERLINE_SINGLE);

    this->instructionMessageFormat = workbook_add_format(this->workbook);
    format_set_font_size(instructionMessageFormat, 10);
};

lxw_workbook* ExcelGenerator::getWorkbook() {
    return this->workbook;
}

void ExcelGenerator::insertCongregationNameAndDefaultColumns(lxw_worksheet* sheet, std::string congName) {
    worksheet_merge_range(
                sheet,
                this->FIRST_ROW,
                this->WEEK_NUMBER_COLUMN,
                this->FIRST_ROW,
                this->PHONE_NUMBER_COLUMN,
                congName.c_str(),
                this->getCellStyle(this->FIRST_ROW, this->WEEK_NUMBER_COLUMN)
    );
    worksheet_write_string(sheet, this->SECOND_ROW, this->WEEK_NUMBER_COLUMN, "ሳምንት", this->getCellStyle(this->SECOND_ROW, this->WEEK_NUMBER_COLUMN));
    worksheet_write_string(sheet, this->SECOND_ROW, this->DATE_COLUMN, "ቀን", this->getCellStyle(this->SECOND_ROW, this->DATE_COLUMN));
    worksheet_write_string(sheet, this->SECOND_ROW, this->SPEAKER_COLUMN, "ተናጋሪ", this->getCellStyle(this->SECOND_ROW, this->SPEAKER_COLUMN));
    worksheet_write_string(sheet, this->SECOND_ROW, this->TALK_NUMBER_COLUMN, "የንግግር ቁ.", this->getCellStyle(this->SECOND_ROW, this->TALK_NUMBER_COLUMN));
    worksheet_write_string(sheet, this->SECOND_ROW, this->PHONE_NUMBER_COLUMN, "የሞባይል ስ.ቁ.", this->getCellStyle(this->SECOND_ROW, this->PHONE_NUMBER_COLUMN));
}

void ExcelGenerator::insertCongregationsForEldersGoingOut(lxw_worksheet* sheet) {
    std::string congregationName;
    std::map<int, int>::iterator elderColIterator;
    std::vector<pts::Program> talksByElder;

    for (elderColIterator = this->elderColumnMap.begin(); elderColIterator != this->elderColumnMap.end(); ++elderColIterator)
    {
        talksByElder = pts::PTSDatabase::getTalksByElder(elderColIterator->first);

        for (std::map<std::string, int>::iterator dateRowIterator = this->dateRowMap.begin(); dateRowIterator != this->dateRowMap.end(); ++dateRowIterator)
        {
            congregationName = this->getCongregationNameForTalkAtDate(dateRowIterator->first, talksByElder);
            worksheet_write_string(
                        sheet,
                        dateRowIterator->second,
                        elderColIterator->second,
                        congregationName.c_str(),
                        this->getCellStyle(dateRowIterator->second, elderColIterator->second));
        }
    }

    this->elderColumnMap.clear();
}

void ExcelGenerator::insertElderNamesAndCongregationsTheyGoTo(lxw_worksheet* sheet, int congregationId) {
    int col = this->PHONE_NUMBER_COLUMN + 1;

    std::vector<Elder> elders = pts::PTSDatabase::getAllEnabledEldersOfCongregation(congregationId);
    this->lastCol = this->PHONE_NUMBER_COLUMN + elders.size();
    std::string fullName;
    int talkNumber;

    for (pts::Elder elder : elders) {
        talkNumber = pts::PTSDatabase::getStorage().get<Talk>(elder.getTalkId()).getTalkNumber();
        fullName = elder.getFirstName() + " " + elder.getMiddleName() +
                "\n(ንግግር ቁ. " + std::to_string(talkNumber) + ")";

        worksheet_write_string(sheet, this->SECOND_ROW, col, fullName.c_str(), this->getCellStyle(this->SECOND_ROW, col));

        this->elderColumnMap[elder.getId()] = col;
        ++col;
    }

    worksheet_merge_range(sheet, this->FIRST_ROW, this->PHONE_NUMBER_COLUMN + 1, this->FIRST_ROW, col - 1, "ከጉባኤ የሚሄዱ", this->getCellStyle(this->FIRST_ROW, col));
    this->insertCongregationsForEldersGoingOut(sheet);
}

void ExcelGenerator::insertWeekNumberAndDates(lxw_worksheet* sheet, std::vector<std::string> dates) {
    int row = FIRST_SCHEDULE_ROW, weekNumber = 1;
    std::regex pattern(" [0-9:\\.]+");
    tm tm1;

    sscanf(dates[0].c_str(), "%4d-%2d-%2d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    int previousDateMonth = tm1.tm_mon;

    for (std::string date : dates) {
        sscanf(date.c_str(), "%4d-%2d-%2d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);

        if (tm1.tm_mon != previousDateMonth) {
            weekNumber = 1;
        }

        if (weekNumber == 1) {
            this->newWeekRows.push_back(row);
        }

        worksheet_write_number(sheet, row, this->WEEK_NUMBER_COLUMN, weekNumber, this->getCellStyle(row, this->WEEK_NUMBER_COLUMN));
        date = std::regex_replace(date, pattern, "");
        worksheet_write_string(sheet, row, this->DATE_COLUMN, date.c_str(), this->getCellStyle(row, this->DATE_COLUMN));

        previousDateMonth = tm1.tm_mon;
        ++row; ++weekNumber;
    }
}

void ExcelGenerator::insertSpeakersDetails(lxw_worksheet* sheet, std::vector<Program> programsForCongregation) {
    int row = this->FIRST_SCHEDULE_ROW;
    std::string elderFullName, elderPhoneNumber, talkNumber;

    for (Program program : programsForCongregation) {
        elderFullName = "", elderPhoneNumber = "", talkNumber = "";

        if (!program.getFree()) {
            pts::Elder elder = pts::PTSDatabase::getStorage().get<Elder>(program.getElderId());
            elderFullName = elder.getFirstName() + " " + elder.getMiddleName();
            elderPhoneNumber = elder.getPhoneNumber();
            talkNumber = std::to_string(
                        pts::PTSDatabase::getStorage().get<Talk>(elder.getTalkId()).getTalkNumber()
            );
        }

        worksheet_write_string(sheet, row, this->SPEAKER_COLUMN, elderFullName.c_str(), this->getCellStyle(row, this->SPEAKER_COLUMN));
        worksheet_write_string(sheet, row, this->TALK_NUMBER_COLUMN, talkNumber.c_str(), this->getCellStyle(row, this->TALK_NUMBER_COLUMN));
        worksheet_write_string(sheet, row, this->PHONE_NUMBER_COLUMN, elderPhoneNumber.c_str(), this->getCellStyle(row, this->PHONE_NUMBER_COLUMN));
        ++row;
    }
}

std::string ExcelGenerator::getCongregationNameForTalkAtDate(std::string date, std::vector<pts::Program> talksByElder) {
    for (pts::Program program : talksByElder) {
        if (program.getDate() == date) {
            return pts::PTSDatabase::getStorage().get<Congregation>(program.getCongregationId()).getName();
        }
    }

    return "";
}

void ExcelGenerator::insertInstructionMessage(lxw_worksheet* sheet) {
    int row = this->lastRow + 1;

    row++; worksheet_merge_range(sheet, row, this->WEEK_NUMBER_COLUMN, row, this->lastCol, "ለአስተባባሪው", this->instructionMessageTitleFormat);
    row++; worksheet_merge_range(sheet, row, this->WEEK_NUMBER_COLUMN, row, this->lastCol, "እባክህ ተጋባዥ ተናጋሪውን እጅግ ቢዘገይ እስከ ማክሰኞ ደውለህ አስታውሰው።", this->instructionMessageFormat);
    row++; worksheet_merge_range(sheet, row, this->WEEK_NUMBER_COLUMN, row, this->lastCol, "ይህን ፕሮግራም እንደደረሰህ እባክህ ከጉባኤህ ውስጥ ለተመደቡት ተናጋሪዎች ፎቶ ኮፒ አድርገህ መስጠትህን አትዘንጋ።", this->instructionMessageFormat);
    row++; worksheet_merge_range(sheet, row, this->WEEK_NUMBER_COLUMN, row, this->lastCol, "ለተናጋሪዎች", this->instructionMessageTitleFormat);
    row++; worksheet_merge_range(sheet, row, this->WEEK_NUMBER_COLUMN, row, this->lastCol, "1. ንግግሩ እንደደረሰህ ዝግጅትህን በማጠናቀቅ በፕሮግራምህ መሠረት ንግግርህን መስጠት ይጠበቅብሃል፡፡", this->instructionMessageFormat);
    row++; worksheet_merge_range(sheet, row, this->WEEK_NUMBER_COLUMN, row, this->lastCol, "2. ዝግጅት ስታደርግ ማስተካከያ የተደረገበትን ትምህርት ለመጠቀምህ እርግጠኛ ሁን።", this->instructionMessageFormat);
    row++; worksheet_merge_range(sheet, row, this->WEEK_NUMBER_COLUMN, row, this->lastCol, "3. ንግግር በምትሰጥበት ቀን የተለየ ፕሮግራም ካለህ እባክህ አስቀድመህ ንግግር ለምታቀርብበት ጉባኤ አስተባባሪ ንገር።", this->instructionMessageFormat);
}

lxw_format* ExcelGenerator::getCellStyle(
        bool boldFont,
        int fontSize,
        lxw_format_alignments horizontalAlignment,
        bool hasGrayBackground,
        lxw_format_borders rightBorderThickness,
        lxw_format_borders leftBorderThickness,
        lxw_format_borders bottomBorderThickness)
{
    lxw_format* format = workbook_add_format(this->workbook);

    if (boldFont) {
        format_set_bold(format);
    }

    format_set_font_size(format, fontSize);
    // by default all formats are vertically centered
    format_set_align(format, LXW_ALIGN_VERTICAL_CENTER);
    format_set_align(format, horizontalAlignment);

    if (hasGrayBackground) {
        format_set_bg_color(format, 0xBEBEBE);
    }

    format_set_right(format, rightBorderThickness);
    format_set_left(format, leftBorderThickness);
    format_set_bottom(format, bottomBorderThickness);

    return format;
}

lxw_format* ExcelGenerator::getCellStyle(int row, int col) {
    lxw_format* format;

    // Header formats (rows 1 and 2)
    if (row == this->FIRST_ROW) {
        if (col == 0) {
            format = this->B_10_C_G_NTN;
        } else {
            format = this->B_10_C_G_TNN;
        }
    } else if (row == this->SECOND_ROW) {
        if (col == this->WEEK_NUMBER_COLUMN) {
            format = this->B_10_C_G_NTM;
        } else if (col == this->lastCol) {
            format = this->B_10_C_G_TNM;
        } else {
            format = this->B_10_C_G_NNM;
        }
    } else if (row == this->lastRow) {
        if (this->isANewWeekRow(row)) {
            if (col == this->WEEK_NUMBER_COLUMN) {
                format = this->R_10_C_G_NTT;
            } else if (col == this->lastCol) {
                format = this->R_10_C_G_TNT;
            } else if ((col > this->WEEK_NUMBER_COLUMN) && (col < this->PHONE_NUMBER_COLUMN + 1)) {
                format = this->R_10_L_G_NNT;
            } else { // (col > this->PHONE_NUMBER_COLUMN) && (col < this->lastCol)
                format = this->R_10_C_G_NNT;
            }
        } else { // a normal week
            if (col == this->WEEK_NUMBER_COLUMN) {
                format = this->R_10_C_K_NTT;
            } else if (col == this->lastCol) {
                format = this->R_10_C_K_TNT;
            } else if ((col > this->WEEK_NUMBER_COLUMN) && (col < this->PHONE_NUMBER_COLUMN + 1)) {
                format = this->R_10_L_K_NNT;
            } else { // (col > this->PHONE_NUMBER_COLUMN) && (col < this->lastCol)
                format = this->R_10_C_K_NNT;
            }
        }
    } else { // all rows excluding the first, second and last rows
        if (this->isANewWeekRow(row)) {
            if (col == this->WEEK_NUMBER_COLUMN) {
                format = this->R_10_C_G_NTM;
            } else if (col == this->lastCol) {
                format = this->R_10_C_G_TNM;
            } else if ((col > this->WEEK_NUMBER_COLUMN) && (col < this->PHONE_NUMBER_COLUMN + 1)) {
                format = this->R_10_L_G_NNM;
            } else { // (col > this->PHONE_NUMBER_COLUMN) && (col < this->lastCol)
                format = this->R_10_C_G_NNM;
            }
        } else { // normal week
            if (col == this->WEEK_NUMBER_COLUMN) {
                format = this->R_10_C_K_NTN;
            } else if (col == this->lastCol) {
                format = this->R_10_C_K_TNN;
            } else if ((col > this->WEEK_NUMBER_COLUMN) && (col < this->PHONE_NUMBER_COLUMN + 1)) {
                format = this->R_10_L_K_NNN;
            } else { // (col > this->PHONE_NUMBER_COLUMN) && (col < this->lastCol)
                format = this->R_10_C_K_NNN;
            }
        }
    }

    return format;
}

bool ExcelGenerator::isANewWeekRow(int row) {
    return std::find(this->newWeekRows.begin(), this->newWeekRows.end(), row) != this->newWeekRows.end();
}

void ExcelGenerator::generateExcelDocument() {

    if (pts::PTSDatabase::getStorage().count<pts::Program>() != 0) {

        for (pts::Congregation congregation : pts::PTSDatabase::getAllCongregations()) {
            lxw_worksheet* worksheet = workbook_add_worksheet(this->workbook, congregation.getName().c_str());

            std::vector<Elder> elders = pts::PTSDatabase::getStorage()
                    .get_all<Elder>(where(c(&Elder::getCongregationId) = congregation.getId()));

            this->insertCongregationNameAndDefaultColumns(worksheet, congregation.getName().c_str());
            this->insertWeekNumberAndDates(worksheet, pts::PTSDatabase::getDistinctProgramDates());
            this->insertElderNamesAndCongregationsTheyGoTo(worksheet, congregation.getId());
            this->insertSpeakersDetails(worksheet, pts::PTSDatabase::getTalksForCongregation(congregation.getId()));
            this->insertInstructionMessage(worksheet);
        }

        workbook_close(this->workbook);
    }
}

}
