QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    case.cpp \
    cooler.cpp \
    dataloader.cpp \
    graphicscard.cpp \
    hdd.cpp \
    main.cpp \
    modelviewwidget.cpp \
    motherboard.cpp \
    mymodel.cpp \
    power.cpp \
    processor.cpp \
    ram.cpp \
    ssd.cpp \
    tabform.cpp \
    test.cpp \
    testbox.cpp

HEADERS += \
    Element.h \
    case.h \
    cooler.h \
    dataloader.h \
    graphicscard.h \
    hdd.h \
    modelviewwidget.h \
    motherboard.h \
    mymodel.h \
    power.h \
    processor.h \
    ram.h \
    ssd.h \
    tabform.h \
    test.h \
    testbox.h

FORMS += \
    tabform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
