#-------------------------------------------------
#
# Project created by QtCreator 2019-11-19T23:27:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pts
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        congregation.cpp \
        elder.cpp \
        main.cpp \
        mainwindow.cpp \
        program.cpp \
        excel_generator.cpp \
        talk.cpp \
        update_congregation_dialog.cpp \
        update_elder_dialog.cpp \
        update_talk_dialog.cpp

HEADERS += \
        congregation.h \
        constants.h \
        database.h \
        elder.h \
        form_validation.h \
        mainwindow.h \
        program.h \
        excel_generator.h \
        sqlite_orm/sqlite_orm.h \
        talk.h \
        update_congregation_dialog.h \
        update_elder_dialog.h \
        update_talk_dialog.h

LIBS += -ldl -lsqlite3 -lxlsxwriter

FORMS += \
        mainwindow.ui \
        update_congregation_dialog.ui \
        update_elder_dialog.ui \
        update_talk_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sample data/randomCSV.py \
    sample data/random_congs.csv \
    sample data/random_elders.csv \
    sample data/random_titles.csv \
    sample data/text/congs.txt \
    sample data/text/names.txt \
    sample data/text/words.txt
