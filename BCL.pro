QT += core gui
CONFIG += c++11

TARGET = BCL
TEMPLATE = lib

include( BCL.pri )

CONFIG += c++11 console
CONFIG -= app_bundle

SUB_MAIN = $${SRC_PATH}
SUB_FIELDS = $${SRC_PATH}/fields
SUB_STYLES = $${SRC_PATH}/styles
SUB_BUTTONS = $${SRC_PATH}/buttons
SUB_DIR = $${SRC_PATH}/dir

#INCLUDEPATH += $${INC_PATH}
#$${SUB_MAIN}/ $${SUB_FIELDS}/ $${SUB_STYLES}/ $${SUB_BUTTONS}/ $${SUB_DIR}/

HEADERS += \
        $${INC_PATH}/BCL.h \
        $${INC_PATH}/fields.h \
        $${INC_PATH}/fields_describe.h \
        $${INC_PATH}/coord.h \
        $${INC_PATH}/transform_coords.h \
        $${INC_PATH}/button.h \
        $${INC_PATH}/styles.h \
        $${INC_PATH}/dir.h \

SOURCES += \
        $${SUB_FIELDS}/fields_default.cpp \
        $${SUB_FIELDS}/fields_numbers.cpp \
        $${SUB_FIELDS}/fields_text.cpp \
        $${SUB_FIELDS}/fields_coords.cpp \
        $${SUB_BUTTONS}/button.cpp \
        $${SUB_STYLES}/styles_default.cpp \
        $${SUB_STYLES}/styles_button.cpp \
        $${SUB_DIR}/dir.cpp

DESTDIR = $${LIBS_PATH}/

unix {
        target.path = $${LIBS_PATH} #/usr/lib
        INSTALLS += target
}
