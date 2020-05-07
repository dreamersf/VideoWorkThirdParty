#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T08:47:35
#
#-------------------------------------------------

QT       -= gui
QT -= core
QT -= network

TARGET = osipparser2
TEMPLATE = lib
#CONFIG += staticlib
macx{
DEFINES += HAVE_FCNTL_H
#    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/
INCLUDEPATH +=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/
    CONFIG(debug){
        DESTDIR = $$PWD/../../gbt28181/ec_rel/lib_macx_debug
        DEFINES += ENABLE_TRACE
        }else{
        DESTDIR = $$PWD/../../gbt28181/ec_rel/lib_macx_release
    }
    LIBS += -L/usr/lib -lpthread
}else{

unix{
DEFINES += HAVE_FCNTL_H
    CONFIG(debug){
    DESTDIR = $$PWD/../../gbt28181/ec_rel/lib_unix_ubuntu1432
    DEFINES += ENABLE_TRACE
    }else{
    DESTDIR = $$PWD/../../gbt28181/ec_rel/lib_unix_ubuntu1432_release
    }
    LIBS += -lpthread
}
win32{
    DEFINES -= UNICODE
    CONFIG(debug){
    DESTDIR = $$PWD/../../gbt28181/ec_rel/lib_win32_mingw_debug
    DEFINES += ENABLE_TRACE
    }else{
    DESTDIR = $$PWD/../../gbt28181/ec_rel/lib_win32_mingw_release
    }
    LIBS += -lws2_32 -lAdvapi32
}
}


DEFINES += ENABLE_TRACE
INCLUDEPATH += $$PWD/include

SOURCES +=  src/osipparser2/sdp_message.c \
    src/osipparser2/sdp_accessor.c \
    src/osipparser2/osip_www_authenticate.c \
    src/osipparser2/osip_via.c \
    src/osipparser2/osip_uri.c \
    src/osipparser2/osip_to.c \
    src/osipparser2/osip_route.c \
    src/osipparser2/osip_record_route.c \
    src/osipparser2/osip_proxy_authorization.c \
    src/osipparser2/osip_proxy_authentication_info.c \
    src/osipparser2/osip_proxy_authenticate.c \
    src/osipparser2/osip_port.c \
    src/osipparser2/osip_parser_cfg.c \
    src/osipparser2/osip_mime_version.c \
    src/osipparser2/osip_message_to_str.c \
    src/osipparser2/osip_message_parse.c \
    src/osipparser2/osip_message.c \
    src/osipparser2/osip_md5c.c \
    src/osipparser2/osip_list.c \
    src/osipparser2/osip_header.c \
    src/osipparser2/osip_from.c \
    src/osipparser2/osip_error_info.c \
    src/osipparser2/osip_cseq.c \
    src/osipparser2/osip_content_type.c \
    src/osipparser2/osip_content_length.c \
    src/osipparser2/osip_content_encoding.c \
    src/osipparser2/osip_content_disposition.c \
    src/osipparser2/osip_contact.c \
    src/osipparser2/osip_call_info.c \
    src/osipparser2/osip_call_id.c \
    src/osipparser2/osip_body.c \
    src/osipparser2/osip_authorization.c \
    src/osipparser2/osip_authentication_info.c \
    src/osipparser2/osip_allow.c \
    src/osipparser2/osip_alert_info.c \
    src/osipparser2/osip_accept_language.c \
    src/osipparser2/osip_accept_encoding.c \
    src/osipparser2/osip_accept.c

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    include/osipparser2/sdp_message.h \
    include/osipparser2/osip_uri.h \
    include/osipparser2/osip_port.h \
    include/osipparser2/osip_parser.h \
    include/osipparser2/osip_message.h \
    include/osipparser2/osip_md5.h \
    include/osipparser2/osip_list.h \
    include/osipparser2/osip_headers.h \
    include/osipparser2/osip_const.h \
    include/osipparser2/osip_body.h \
    include/osipparser2/internal.h \
    include/osipparser2/headers/osip_www_authenticate.h \
    include/osipparser2/headers/osip_via.h \
    include/osipparser2/headers/osip_to.h \
    include/osipparser2/headers/osip_route.h \
    include/osipparser2/headers/osip_record_route.h \
    include/osipparser2/headers/osip_proxy_authorization.h \
    include/osipparser2/headers/osip_proxy_authentication_info.h \
    include/osipparser2/headers/osip_proxy_authenticate.h \
    include/osipparser2/headers/osip_mime_version.h \
    include/osipparser2/headers/osip_header.h \
    include/osipparser2/headers/osip_from.h \
    include/osipparser2/headers/osip_error_info.h \
    include/osipparser2/headers/osip_cseq.h \
    include/osipparser2/headers/osip_content_type.h \
    include/osipparser2/headers/osip_content_length.h \
    include/osipparser2/headers/osip_content_encoding.h \
    include/osipparser2/headers/osip_content_disposition.h \
    include/osipparser2/headers/osip_contact.h \
    include/osipparser2/headers/osip_call_info.h \
    include/osipparser2/headers/osip_call_id.h \
    include/osipparser2/headers/osip_authorization.h \
    include/osipparser2/headers/osip_authentication_info.h \
    include/osipparser2/headers/osip_allow.h \
    include/osipparser2/headers/osip_alert_info.h \
    include/osipparser2/headers/osip_accept_language.h \
    include/osipparser2/headers/osip_accept_encoding.h \
    include/osipparser2/headers/osip_accept.h

OTHER_FILES += \
    platform/vsnet/osipparser2.def
DEF_FILE += \
        platform/vsnet/osipparser2.def
