TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -O3
QMAKE_CFLAGS_RELEASE    = -O3

INCLUDEPATH += ./include/
QMAKE_CXXFLAGS += -stdlib=libc++

SOURCES += main.cpp \

HEADERS += \
    include/numbers.h \
    include/format_int.h \
    include/humanize/format_int.h \
    include/humanize/numbers.h \
    include/math/matrix.h \
    include/humanize/time.h \
    include/math/math.h \
    include/misc./color.h \
    include/misc./string_utils.h \
    include/misc./log.h \
    include/misc./rng.h \
    include/misc./array_util.h \
    include/misc./monte_carlo.h \
    include/network/net.h
