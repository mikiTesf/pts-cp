#ifndef FORM_VALIDATION_H
#define FORM_VALIDATION_H

#include "constants.h"
#include "database.h"

#include <QWidget>
#include <QMessageBox>

#include <string>
#include <regex>

namespace pts {

namespace form_validation {

static bool containsSpecialCharacters(std::string someString) {
    return someString.length() != std::regex_replace
            (someString, std::regex(pts::constants::SPECIAL_CHARACTERS_PATTERN), "").length();
}

static bool isEmpty(std::string someString) {
    bool isEmpty = std::regex_replace(someString, std::regex("[\\s]*"), "").length() == 0;
    return isEmpty;
}

static bool validPhoneNumber(std::string phoneNumber)
{
    return std::regex_match(phoneNumber, std::regex(pts::constants::PHONE_NUMBER_PATTERN));
}

static bool elderDetailsAreValid(
        QWidget* parentWindow,
        int selectedTalkNumber,
        std::string newFirstName,
        std::string newMiddleName,
        std::string newLastName,
        std::string newPhoneNumber)
{
    if (
            (containsSpecialCharacters(newFirstName)  || isEmpty(newFirstName))  ||
            (containsSpecialCharacters(newMiddleName) || isEmpty(newMiddleName)) ||
            (containsSpecialCharacters(newLastName) || isEmpty(newLastName)))
    {
        QMessageBox::warning(parentWindow, "Incomplete Elder Name", "Elder name is incomplete or has special characters.");
        return false;
    }

    if (!validPhoneNumber(newPhoneNumber) || isEmpty(newPhoneNumber))
    {
        QMessageBox::warning(parentWindow, "Invalid Phone Number", "Phone number is invalid.");
        return false;
    }

    int talkNumber = pts::PTSDatabase::getTalkByTalkNumber(selectedTalkNumber).at(0).getTalkNumber();

    if (!pts::PTSDatabase::getEldersByTalkNumber(talkNumber).empty()) {
        if (QMessageBox::question(
                    parentWindow,
                    "Duplicate Assignment",
                    "This talk is already assigned to an elder. Continue?") == QMessageBox::StandardButton::No)
        {
            return false;
        }
    }

    return true;
}

static bool congregationDetailsAreValid(QWidget* parentWindow, std::string congregationName) {
    if (isEmpty(congregationName))
    {
        QMessageBox::warning(parentWindow, "Congregation Name Left Empty", "You left the congregation name field empty.");
        return false;
    }

    // Numbers may be part of a congregation's name (never encountered one before but just in case)
    if (containsSpecialCharacters(congregationName))
    {
        QMessageBox::warning(parentWindow, "Invalid Congregation Name", "The name inserted contains invalid characters.");
        return false;
    }

    if (!pts::PTSDatabase::getCongregationByName(congregationName).empty())
    {
        QMessageBox::warning(parentWindow, "Duplicate Entry", "\"" + QString::fromStdString(congregationName) + "\" already exists.");
        return false;
    }

    return true;
}

static bool talkDetailsAreValid(QWidget* parentWindow, std::string insertedTitle, int talkNumber) {
    if (isEmpty(insertedTitle))
    {
        QMessageBox::warning(
                    parentWindow,
                    "Talk Title Empty",
                    "You left the title field empty.");
        return false;
    }

    // Numbers like 1914, 144000 may be part of the talk title so the regex used in
    // `containsSpecialCharacters(std::string)` doesn't match digits
    if (containsSpecialCharacters(insertedTitle))
    {
        QMessageBox::warning(
                    parentWindow,
                    "Invalid Talk Title",
                    "The title inserted contains invalid characters.");
        return false;
    }

    if (talkNumber <= 0) {
        QMessageBox::warning(parentWindow, "Invalid Talk Number", QString::number(talkNumber) + " is not a valid talk number.");
        return false;
    }

    if (!pts::PTSDatabase::getTalkByTalkNumber(talkNumber).empty())
    {
        QMessageBox::warning(parentWindow, "Duplicate Found", "A talk with talk number " + QString::number(talkNumber) + " already exists.");
        return false;
    }

    return true;
}

} // end of namespace form_validation

} // end of namespace pts

#endif // FORM_VALIDATION_H
