TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle

INCLUDEPATH += ./include/
QMAKE_CXXFLAGS += -stdlib=libc++

SOURCES += main.cpp

HEADERS += \
    include/numbers.h \
    include/format_int.h \
    include/humanize/format_int.h \
    include/humanize/numbers.h \
    include/math/matrix.h \
    include/humanize/time.h
