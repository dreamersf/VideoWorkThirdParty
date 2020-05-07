#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T08:47:35
#
#-------------------------------------------------

QT       -= gui
QT -= core
QT -= network

TARGET = eXosip2
TEMPLATE = lib
macx{
    DEFINES+=HAVE_TIME_H
    DEFINES+=HAVE_STRUCT_TIMEVAL
    DEFINES+=HAVE_FCNTL_H
    INCLUDEPATH += /usr/include
INCLUDEPATH +=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/
    CONFIG(debug){
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_macx_debug
    LIBS += -L$$PWD/../../boguan28181/ec_rel/lib_macx_debug -losipparser2 -losip2
    LIBS+= -L/usr/lib -lpthread
    DEFINES += ENABLE_TRACE
    }else{
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_macx_release
    LIBS += -L$$PWD/../../boguan28181/ec_rel/lib_macx_release -losipparser2 -losip2 -lpthread
    }
}else{
unix{

    DEFINES+=HAVE_TIME_H
    DEFINES+=HAVE_STRUCT_TIMEVAL
    DEFINES+=HAVE_FCNTL_H
    INCLUDEPATH += /usr/include
INCLUDEPATH +=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/
    CONFIG(debug){
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_unix_ubuntu1432_debug
    LIBS += -L$$PWD/../../boguan28181/ec_rel/lib_unix_ubuntu1432_debug -losipparser2 -losip2
    LIBS+= -L/usr/lib -lpthread
    DEFINES += ENABLE_TRACE
    }else{
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_unix_ubuntu1432_release
    LIBS += -L$$PWD/../../boguan28181/ec_rel/lib_unix_ubuntu1432_release -losipparser2 -losip2 -lpthread
    }
}
win32{
    DEFINES -= UNICODE
    CONFIG(debug){
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_win32_mingw_debug
    LIBS += -L$$PWD/../../boguan28181/ec_rel/lib_win32_mingw_debug -losipparser2 -losip2 -lws2_32 -lAdvapi32 -lIPHLPAPI
    DEFINES += ENABLE_TRACE
    }else{
    DESTDIR = $$PWD/../../boguan28181/ec_rel/lib_win32_mingw_release
    LIBS += -L$$PWD/../../boguan28181/ec_rel/lib_win32_mingw_release -losipparser2 -losip2 -lws2_32 -lAdvapi32 -lIPHLPAPI
    }
}
}
INCLUDEPATH += $$PWD/../libosip2-4.0.0/include \
               $$PWD/include \
                $$PWD/

SOURCES +=  src/udp.c \
    src/sdp_offans.c \
    src/rijndael.c \
    src/misc.c \
    src/milenage.c \
    src/jsubscribe.c \
    src/jresponse.c \
    src/jrequest.c \
    src/jreg.c \
    src/jpublish.c \
    src/jpipe.c \
    src/jnotify.c \
    src/jevents.c \
    src/jdialog.c \
    src/jcallback.c \
    src/jcall.c \
    src/jauth.c \
    src/inet_ntop.c \
    src/eXutils.c \
    src/eXtransport.c \
    src/eXtl_udp.c \
    src/eXtl_tls.c \
    src/eXtl_tcp.c \
    src/eXtl_dtls.c \
    src/eXsubscription_api.c \
    src/eXregister_api.c \
    src/eXrefer_api.c \
    src/eXpublish_api.c \
    src/eXosip.c \
    src/eXoptions_api.c \
    src/eXmessage_api.c \
    src/eXinsubscription_api.c \
    src/eXconf.c \
    src/eXcall_api.c

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    platform/vsnet/eXosip2.def

DEF_FILE += \
    platform/vsnet/eXosip2.def
