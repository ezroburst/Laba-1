QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        tests.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AbstractFactory.h \
    CPP_AbstractFactory.h \
    CPP_ClassUnit.h \
    CPP_MethodUnit.h \
    CPP_PrintUnit.h \
    CSHARP_AbstractFactory.h \
    CSHARP_ClassUnit.h \
    CSHARP_MethodUnit.h \
    CSHARP_PrintUnit.h \
    ClassUnit.h \
    Configuration.h \
    JAVA_AbstractFactory.h \
    JAVA_ClassUnit.h \
    JAVA_MethodUnit.h \
    JAVA_PrintUnit.h \
    MethodUnit.h \
    PrintUnit.h \
    Unit.h \
    tests.h
