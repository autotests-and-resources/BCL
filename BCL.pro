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

INCLUDEPATH += $${SUB_MAIN}/ $${SUB_FIELDS}/ $${SUB_STYLES}/ $${SUB_BUTTONS}/

HEADERS += \
	$${SUB_MAIN}/balutils.h \
	$${SUB_FIELDS}/fields.h \
	$${SUB_FIELDS}/fields_describe.h \
	$${SUB_MAIN}/coord.h \
	$${SUB_MAIN}/transform_coords.h \
	$${SUB_BUTTONS}/button.h \
	$${SUB_STYLES}/styles.h

SOURCES += \
	$${SUB_FIELDS}/fields_default.cpp \
	$${SUB_FIELDS}/fields_numbers.cpp \
	$${SUB_FIELDS}/fields_text.cpp \
	$${SUB_FIELDS}/fields_coords.cpp \
	$${SUB_STYLES}/styles_default.cpp \
	$${SUB_STYLES}/styles_button.cpp

DESTDIR = $${LIBS_PATH}/

unix {
	target.path = $${LIBS_PATH} #/usr/lib
	INSTALLS += target
}
