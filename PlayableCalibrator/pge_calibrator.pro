# SMBX64 Playble Character Sprite Calibrator, a free tool for playable srite design
# This is a part of the Platformer Game Engine by Wohlstand, a free platform for game making
# Copyright (c) 2014 Vitaly Novichkov <admin@wohlnet.ru>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#-------------------------------------------------
#
# Project created by QtCreator 2014-04-05T21:35:05
#
#-------------------------------------------------

QT       += gui widgets

DESTDIR = ../bin

static: {
release:OBJECTS_DIR = ../bin/_build/calibrator/_release/.obj
release:MOC_DIR     = ../bin/_build/calibrator/_release/.moc
release:RCC_DIR     = ../bin/_build/calibrator/_release/.rcc
release:UI_DIR      = ../bin/_build/calibrator/_release/.ui

debug:OBJECTS_DIR   = ../bin/_build/calibrator/_debug/.obj
debug:MOC_DIR       = ../bin/_build/calibrator/_debug/.moc
debug:RCC_DIR       = ../bin/_build/calibrator/_debug/.rcc
debug:UI_DIR        = ../bin/_build/calibrator/_debug/.ui
} else {
release:OBJECTS_DIR = ../bin/_build/_dynamic/calibrator/_release/.obj
release:MOC_DIR     = ../bin/_build/_dynamic/calibrator/_release/.moc
release:RCC_DIR     = ../bin/_build/_dynamic/calibrator/_release/.rcc
release:UI_DIR      = ../bin/_build/_dynamic/calibrator/_release/.ui

debug:OBJECTS_DIR   = ../bin/_build/_dynamic/calibrator/_debug/.obj
debug:MOC_DIR       = ../bin/_build/_dynamic/calibrator/_debug/.moc
debug:RCC_DIR       = ../bin/_build/_dynamic/calibrator/_debug/.rcc
debug:UI_DIR        = ../bin/_build/_dynamic/calibrator/_debug/.ui
}

TARGET = pge_calibrator
TEMPLATE = app
CONFIG += static

RC_FILE = _resourses/caltool.rc

QMAKE_CFLAGS += -Wno-sign-compare

SOURCES += main.cpp\
        calibrationmain.cpp \
    frame_matrix/matrix.cpp \
    about/about.cpp \
    animator/animate.cpp \
    animator/animationedit.cpp \
    frame_matrix/MatrixScene.cpp \
    ../_Libs/EasyBMP/EasyBMP.cpp \
    ../_Libs/giflib/dgif_lib.c \
    ../_Libs/giflib/egif_lib.c \
    ../_Libs/giflib/gif_err.c \
    ../_Libs/giflib/gif_font.c \
    ../_Libs/giflib/gif_hash.c \
    ../_Libs/giflib/gifalloc.c \
    ../_Libs/giflib/quantize.c \
    main/files_io.cpp \
    main/globals.cpp \
    main/graphics.cpp \
    main/settings.cpp \
    image_calibration/image_calibrator.cpp \
    animator/SpriteScene.cpp \
    main/mw.cpp \
    animator/AnimationScene.cpp

HEADERS  += calibrationmain.h \
    frame_matrix/matrix.h \
    about/about.h \
    animator/aniFrames.h \
    animator/animate.h \
    animator/animationedit.h \
    animator/AnimationScene.h \
    frame_matrix/MatrixScene.h \
    animator/SpriteScene.h \
    ../_Libs/EasyBMP/EasyBMP.h \
    ../_Libs/EasyBMP/EasyBMP_BMP.h \
    ../_Libs/EasyBMP/EasyBMP_DataStructures.h \
    ../_Libs/EasyBMP/EasyBMP_VariousBMPutilities.h \
    ../_Libs/giflib/gif_hash.h \
    ../_Libs/giflib/gif_lib.h \
    ../_Libs/giflib/gif_lib_private.h \
    main/globals.h \
    main/graphics.h \
    version.h \
    image_calibration/image_calibrator.h \
    main/mw.h

FORMS    += calibrationmain.ui \
    about/about.ui \
    animator/animate.ui \
    animator/animationedit.ui \
    frame_matrix/matrix.ui \
    image_calibration/image_calibrator.ui

RESOURCES += \
    _resourses/images.qrc

OTHER_FILES += \
    caltool.rc \
    calibrator.ico \
    _resourses/caltool.rc
