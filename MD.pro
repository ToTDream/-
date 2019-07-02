#-------------------------------------------------
#
# Project created by QtCreator 2018-05-30T19:25:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MD
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
    add_course.cpp \
    changepw.cpp \
    childwidget.cpp \
    course.cpp \
    course_student.cpp \
    logindialog.cpp \
    manage.cpp \
    person.cpp \
    sort_template.cpp \
    stu_optional.cpp \
    stu_selected.cpp \
    studentmanage.cpp \
    tea_course.cpp \
    teachermanage.cpp

HEADERS += \
        mainwindow.h \
    add_course.h \
    changepw.h \
    childwidget.h \
    course.h \
    course_student.h \
    logindialog.h \
    manage.h \
    person.h \
    sort_template.h \
    stu_optional.h \
    stu_selected.h \
    studentmanage.h \
    tea_course.h \
    teachermanage.h

FORMS += \
        mainwindow.ui \
    add_course.ui \
    changepw.ui \
    childwidget.ui \
    logindialog.ui \
    postwidget.ui \
    studentmanage.ui \
    teachermanage.ui

RESOURCES += \
    file.qrc \
    file.qrc

SUBDIRS += \
    MD.pro

DISTFILES += \
    MD.pro.user \
    file.qrc.autosave
