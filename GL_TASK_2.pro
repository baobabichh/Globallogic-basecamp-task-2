QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += stc/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/CheckBoxController.cpp \
    src/Date.cpp \
    src/Errorable.cpp \
    src/FileAction.cpp \
    src/FileInfo.cpp \
    src/FileInfoDisplayer.cpp \
    src/FileSystemTraveler.cpp \
    src/Main.cpp \
    src/MainWindow.cpp \
    src/StateMachine.cpp \
    src/XMLFileTravelerQImpl.cpp \
    src/XMLFileWriter.cpp

HEADERS += \
    src/CheckBoxController.h \
    src/Date.h \
    src/Errorable.h \
    src/FileAction.h \
    src/FileInfo.h \
    src/FileInfoDisplayer.h \
    src/FileSystemTraveler.h \
    src/IFileSystemTraveler.h \
    src/IXMLFileTraveler.h \
    src/MainWindow.h \
    src/StateMachine.h \
    src/XMLFileStructure.h \
    src/XMLFileTravelerQImpl.h \
    src/XMLFileWriter.h

FORMS += \
    src/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
