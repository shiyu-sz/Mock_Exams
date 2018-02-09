#-------------------------------------------------
#
# Project created by QtCreator 2016-06-11T14:17:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

TARGET = examination_manage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        examination.cpp \
    qtsql_operation.cpp \
    File_Operations.cpp \
    result.cpp

HEADERS  += mainwindow.h \
    examination.h \
    main.h \
    qtsql_operation.h \
    File_Operations.h \
    result.h

FORMS    += mainwindow.ui \
    examination.ui \
    result.ui

RESOURCES +=

OTHER_FILES += \
    app.rc

RC_FILE+=app.rc
