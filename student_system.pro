#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T19:22:25
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = student_system
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
    person.cpp \
    course.cpp \
    logindialog.cpp \
    studentmanage.cpp \
    teachermanage.cpp \
    manage.cpp \
    childwidget.cpp \
    stu_selected.cpp \
    tea_course.cpp \
    stu_optional.cpp \
    add_course.cpp \
    course_student.cpp \
    changepw.cpp \
    inquiredialog.cpp

HEADERS += \
        mainwindow.h \
    person.h \
    course.h \
    logindialog.h \
    studentmanage.h \
    teachermanage.h \
    manage.h \
    childwidget.h \
    stu_selected.h \
    tea_course.h \
    stu_optional.h \
    add_course.h \
    course_student.h \
    changepw.h \
    inquiredialog.h

FORMS += \
        mainwindow.ui \
    logindialog.ui \
    studentmanage.ui \
    teachermanage.ui \
    childwidget.ui \
    postwidget.ui \
    add_course.ui \
    changepw.ui \
    inquiredialog.ui

DISTFILES += \
    readme.txt \
    teacher.txt \
    student.txt \
    files/readme.txt \
    files/student.txt \
    files/teacher.txt \
    files/password.txt

STATECHARTS +=

RESOURCES += \
    manage_system.qrc
