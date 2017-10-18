#-------------------------------------------------
#
# Project created by QtCreator 2017-04-26T16:52:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jobber
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /usr/local/include/
LIBS += -L/usr/local/lib -lpqxx -lpq
#QMAKE_CXXFLAGS += -lpqxx -lpq
SOURCES += main.cpp\
        mainwindow.cpp \
    connectpsql.cpp \
    psql.cpp \
    newcity.cpp \
    newstatus.cpp \
    showcities.cpp \
    showstatuses.cpp \
    viewjobs.cpp \
    newjob.cpp \
    newcountry.cpp \
    showcountries.cpp \
    spesificjobs.cpp

HEADERS  += mainwindow.h \
    connectpsql.h \
    psql.h \
    newcity.h \
    newstatus.h \
    showcities.h \
    showstatuses.h \
    viewjobs.h \
    newjob.h \
    newcountry.h \
    showcountries.h \
    spesificjobs.h

FORMS    += mainwindow.ui \
    connectpsql.ui \
    newcity.ui \
    newstatus.ui \
    showcities.ui \
    showstatuses.ui \
    viewjobs.ui \
    newjob.ui \
    newcountry.ui \
    showcountries.ui \
    spesificjobs.ui
