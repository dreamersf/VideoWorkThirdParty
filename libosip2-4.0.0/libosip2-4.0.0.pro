#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T08:47:35
#
#-------------------------------------------------

QT       -= gui
QT -= core
QT -= network

TARGET = osip2
TEMPLATE = lib

macx{
DEFINES += HAVE_FCNTL_H
        DEFINES+=HAVE_TIME_H
        DEFINES+=HAVE_STRUCT_TIMEVAL
        DEFINES+=HAVE_CONFIG_H
#    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/
INCLUDEPATH +=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/
    CONFIG(debug){
        DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_macx_debug
        DEFINES += ENABLE_TRACE
        LIBS += -L$$PWD/../../boguan28181/ec_rel/lib_macx_debug -losipparser2 -lpthread
        }else{
        DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_macx_release
        LIBS += -L$$PWD/../../boguan28181/ec_rel/lib_macx_release -losipparser2
    }
    LIBS += -L/usr/lib -lpthread
}else{

unix{
DEFINES += HAVE_FCNTL_H
    CONFIG(debug){
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_unix_ubuntu1432_debug
    DEFINES += ENABLE_TRACE
    }else{
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_unix_ubuntu1432_release
    }
    LIBS += -lpthread
}
win32{
    DEFINES -= UNICODE
    CONFIG(debug){
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_win32_mingw_debug
    DEFINES += ENABLE_TRACE
    }else{
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_win32_mingw_release
    }
    LIBS += -lws2_32 -lAdvapi32
}
}

INCLUDEPATH += $$PWD/include

SOURCES += src/osip2/port_thread.c \
    src/osip2/port_sema.c \
    src/osip2/port_fifo.c \
    src/osip2/port_condv.c \
    src/osip2/osip_transaction.c \
    src/osip2/osip_time.c \
    src/osip2/osip_event.c \
    src/osip2/osip_dialog.c \
    src/osip2/osip.c \
    src/osip2/nist_fsm.c \
    src/osip2/nist.c \
    src/osip2/nict_fsm.c \
    src/osip2/nict.c \
    src/osip2/ist_fsm.c \
    src/osip2/ist.c \
    src/osip2/ict_fsm.c \
    src/osip2/ict.c \
    src/osip2/fsm_misc.c


unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    include/osip2/osip_time.h \
    include/osip2/osip_mt.h \
    include/osip2/osip_fifo.h \
    include/osip2/osip_dialog.h \
    include/osip2/osip_condv.h \
    include/osip2/osip.h \
    include/osip2/internal.h

OTHER_FILES += \
    platform/vsnet/osip2.def
DEF_FILE += \
    platform/vsnet/osip2.def
