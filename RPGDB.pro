QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    DB/DatabaseManager.cpp \
    DB/DatabaseUtils.cpp \
    QT/mainwindow.cpp \
    QT/resourcecontainer.cpp \
    QT/actorform.cpp \
    Models/ActorType.cpp

HEADERS += \
    DB/DatabaseManager.h \
    DB/DatabaseUtils.h \
    QT/mainwindow.h \
    QT/resourcecontainer.h \
    QT/actorform.h \
    Models/ActorType.h

FORMS += \
    QT/mainwindow.ui \
    QT/resourcecontainer.ui \
    QT/actorform.ui

TRANSLATIONS += \
    rpgdb_ja_JP.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
