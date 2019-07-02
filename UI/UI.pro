#-------------------------------------------------
#
# Project created by QtCreator 2018-06-19T19:24:32
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    changepw.cpp \
    childwidget.cpp \
    course_student.cpp \
    logindialog.cpp \
    manage.cpp \
    stu_optional.cpp \
    stu_selected.cpp \
    studentmanage.cpp \
    tea_course.cpp \
    teachermanage.cpp \
    client.cpp

HEADERS += \
        mainwindow.h \
    changepw.h \
    childwidget.h \
    course_student.h \
    logindialog.h \
    manage.h \
    stu_optional.h \
    stu_selected.h \
    studentmanage.h \
    tea_course.h \
    teachermanage.h \
    client.h

FORMS += \
        mainwindow.ui \
    changepw.ui \
    childwidget.ui \
    logindialog.ui \
    mainwindow.ui \
    studentmanage.ui \
    teachermanage.ui \
    client.ui

RESOURCES += \
    images.qrc
