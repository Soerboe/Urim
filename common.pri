# Modified version of common.pri from https://github.com/MrCrazyID/QtCreator_SubDirExample

CONFIG += c++11

# [Usage for this macro]
# These two functions sets up the dependencies for libraries that are build with
# this project. Specify the lib you need to depend on in the variable "DEPENDENCY_PROJECT".
TARGET_DIRECTORY_NAME = 0
TARGET_PATH = 0
LIB_PATH = 0

# Setup the Dependencies
for(dep, DEPENDENCY_PROJECT) {
    TARGET_NAME = $${dep}
    #message($${TARGET}.depends = $${TARGET_NAME})
    $${TARGET}.depends += $${TARGET_NAME}
}
# Setup the actual library dependencies
for(dep, DEPENDENCY_PROJECT) {
    TARGET_NAME = $${dep}
    TARGET_PATH = $${PWD}/$${TARGET_NAME}
    LIB_PATH = $${OUT_PWD}/../$${TARGET_NAME}
    #message(Depending target \"$${TARGET_NAME}\" source path: $${TARGET_PATH})
    #message(Depending target \"$${TARGET_NAME}\" compiled path: $${LIB_PATH})

    win32:CONFIG(release, debug|release): LIBS += -L$${LIB_PATH}/release/ -l$${TARGET_NAME}
    else:win32:CONFIG(debug, debug|release): LIBS += -L$${LIB_PATH}/debug/ -l$${TARGET_NAME}
    else:unix: LIBS += -L$${LIB_PATH}/ -l$${TARGET_NAME}

    # Adds the wanted lib to the project.
    INCLUDEPATH += $${TARGET_PATH}
    #message(INCLUDEPATH: $${INCLUDEPATH})

    # Adds a dependpath to the project
    # This forces a rebuild if the headers change
    DEPENDPATH += $${TARGET_PATH}
    #message(DEPENDPATH: $${DEPENDPATH})

    #Pre target
    PRE_TARGETDEPS += $${TARGET_PATH}
    #message(PRE_TARGETDEPS: $${PRE_TARGETDEPS})
}
