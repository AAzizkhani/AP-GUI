QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editaccount.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mention.cpp \
    search.cpp \
    signup.cpp \
    src/Date.cpp \
    src/anonymousUser.cpp \
    src/baseUser.cpp \
    src/organisationUser.cpp \
    src/personalUser.cpp \
    src/tweet.cpp \
    src/twitterak.cpp \
    useraccount.cpp \
    windowper.cpp

HEADERS += \
    editaccount.h \
    includes/Date.h \
    includes/anonymousUser.h \
    includes/baseUser.h \
    includes/organisationUser.h \
    includes/personalUser.h \
    includes/tweet.h \
    includes/tweetInfo.h \
    includes/twitterak.h \
    login.h \
    mainwindow.h \
    mention.h \
    search.h \
    signup.h \
    useraccount.h \
    windowper.h

FORMS += \
    editaccount.ui \
    login.ui \
    mainwindow.ui \
    mention.ui \
    search.ui \
    signup.ui \
    useraccount.ui \
    windowper.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resours/Recours.qrc
