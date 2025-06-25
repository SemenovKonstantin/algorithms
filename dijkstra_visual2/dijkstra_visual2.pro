QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    graphwidget.cpp

HEADERS += \
    graphwidget.h

FORMS += \
    graphwidget.ui

DESTDIR = $$PWD/build
OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
UI_DIR = $$DESTDIR/ui
RCC_DIR = $$DESTDIR/rcc

!exists($$DESTDIR):system(mkdir -p $$DESTDIR)