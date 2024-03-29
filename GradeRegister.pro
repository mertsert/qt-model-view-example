QT += widgets sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
        src/dbmanager.cpp \
        src/mainwindow.cpp \
        src/models/grade.cpp \
        src/models/student.cpp \
        src/models/teacher.cpp \
        src/views/display.cpp \
        src/views/edit.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/dbmanager.h \
    src/mainwindow.h \
    src/models/grade.h \
    src/models/student.h \
    src/models/teacher.h \
    src/views/display.h \
    src/views/edit.h
