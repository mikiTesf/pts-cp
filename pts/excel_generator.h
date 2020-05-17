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
    int lastCol;
    std::vector<std::string> allProgramDates;
    std::vector<int> newWeekRows;
    // The map below (`elderColumnMap`) is used to identify on which column the elder of a
    // congregation is so that, later, when the congregation to which the elder is going to
    // go to are placedit will be easier to know where to put them.
    std::map<int, int> elderColumnMap;
    // The following map (`dateRowMap`) is important to identify the row that a date is on. Using the date
    // in a pts::Program object, and paired with the map above (`elderColumnMap`), the task of finding the
    // cell at which the congregation that an elder will be going to is placed becomes easy.
    std::map<std::string, int> dateRowMap;
    // see the table below the following declaration to understand the naming scheme used
    lxw_format
    *B_10_C_G_NTN, *B_10_C_G_TNN, *B_10_C_G_NTM, *B_10_C_G_TNM, *B_10_C_G_NNM,
    *R_10_C_G_NTM, *R_10_C_K_NTN, *R_10_L_G_NNM, *R_10_L_K_NTN, *R_10_L_K_NNN,
    *R_10_C_G_NNM, *R_10_C_G_TNM, *R_10_C_K_NNN, *R_10_C_K_TNN, *R_10_C_K_TNT,
    *R_10_C_K_NNT, *R_10_C_G_NTT, *R_10_C_G_TNT, *R_10_L_G_NNT, *R_10_C_G_NNT,
    *R_10_C_K_NTT, *R_10_L_K_NNT;

    /*

    The following table describes what the letters and numbers in the `lxw_format*` variable names above mean.

    +---------------------------+----------+-----------------------+
    | criteria*                 | values   | meaning               |
    +---------------------------+----------+-----------------------+
    | font weight               | B, R     | Bold or Regular       |
    | font size                 | [1-9]+   | Any non-zero digit    |
    | alignmemnt                | C, L     | Center or Left        |
    | background color          | G, K     | Grey or blanK         |
    | border thickness - right  | N, T, M  | thiN, Thick or Medium |
    | border thickness - left   | N, T, M  | thiN, Thick or Medium |
    | border thickness - bottom | N, T, M  | thiN, Thick or Medium |
    +---------------------------+----------+-----------------------+
    * The criteria are listed in order of their appearance in the names of the formats

    */

    // other non-standard formats
    lxw_format *instructionMessageTitleFormat, *instructionMessageFormat;
    // Common row and column indices
    const int FIRST_ROW = 0;
    const int SECOND_ROW = 1;
    const int WEEK_NUMBER_COLUMN = 0;
    const int DATE_COLUMN = 1;
    const int SPEAKER_COLUMN = 2;
    const int TALK_NUMBER_COLUMN = 3;
    const int PHONE_NUMBER_COLUMN = 4;
    // Functions
    void insertCongregationsForEldersGoingOut(lxw_worksheet*);
    void insertCongregationNameAndDefaultColumns(lxw_worksheet*, std::string);
    void insertElderNamesAndCongregationsTheyGoTo(lxw_worksheet*, int);
    void insertWeekNumberAndDates(lxw_worksheet*, std::vector<std::string>);
    void insertSpeakersDetails(lxw_worksheet*, std::vector<pts::Program>);
    void insertInstructionMessage(lxw_worksheet*);
    lxw_format* getCellStyle(
            bool boldFont,
            int fontSize,
            lxw_format_alignments horizontalAlignment,
            bool hasGrayBackground,
            lxw_format_borders rightBorderThickness,
            lxw_format_borders leftBorderThickness,
            lxw_format_borders bottomBorderThickness);
    std::string getCongregationNameForTalkAtDate(std::string date, std::vector<pts::Program> talksByElder);
    lxw_format* getCellStyle(int row, int col);
    bool isANewWeekRow(int row);
public:
    ExcelGenerator();
    lxw_workbook* getWorkbook();
    // pulls all data direcly from the database
    void generateExcelDocument();
};

} // end of namespace

#endif // EXCEL_GENERATOR_H
