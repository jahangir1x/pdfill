QT       += core gui pdf widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += /usr/include/poppler/qt6
LIBS += -lpoppler-qt6

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/infodb.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pdfhandler.cpp

HEADERS += \
    src/infodb.h \
    src/mainwindow.h \
    src/pdfhandler.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
