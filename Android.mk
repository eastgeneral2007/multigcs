LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := main

BASE_DIR = .
LOCAL_CFLAGS := -DANDROID -DBASE_DIR="\"$(BASE_DIR)\"" -DANDROID -DSDLGL -DSDL2 -DUSE_FILE32API

SDL_PATH := ../SDL2
SDL_IMAGE_PATH := ../SDL2_image

CURL_PATH := ../libprebuilt/libcurl
LIBXML2_PATH := ../libxml2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/$(SDL_IMAGE_PATH) $(LOCAL_PATH)/$(CURL_PATH)/inc $(LOCAL_PATH)/$(LIBXML2_PATH)/include \
 $(LOCAL_PATH)/Common $(LOCAL_PATH)/screens $(LOCAL_PATH)/net $(LOCAL_PATH)/tcl $(LOCAL_PATH)/draw $(LOCAL_PATH)/mavlink $(LOCAL_PATH)/gps $(LOCAL_PATH)/mwi21 $(LOCAL_PATH)/simplebgc $(LOCAL_PATH)/brugi $(LOCAL_PATH)/jeti $(LOCAL_PATH)/openpilot $(LOCAL_PATH)/frsky $(LOCAL_PATH)/tracker $(LOCAL_PATH)/minizip

LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
 main.c serial.c draw/draw.c draw/videocapture.c geomag70.c \
 net/htmlget.c \
 minizip/ioapi.c minizip/unzip.c \
 screens/screen_rcflow.c screens/screen_keyboard.c screens/screen_filesystem.c screens/screen_device.c screens/screen_baud.c screens/screen_model.c screens/screen_cli.c screens/screen_baseflightcli.c screens/screen_background.c screens/screen_wpedit.c screens/screen_hud.c screens/screen_map.c screens/screen_calibration.c screens/screen_fms.c screens/screen_system.c screens/screen_mavlink_menu.c screens/screen_brugi.c screens/screen_tracker.c screens/screen_mwi_menu.c screens/screen_openpilot_menu.c screens/screen_graph.c screens/screen_telemetry.c \
 mavlink/my_mavlink.c gps/my_gps.c mwi21/mwi21.c jeti/jeti.c openpilot/openpilot.c openpilot/openpilot_xml.c frsky/frsky.c tracker/tracker.c simplebgc/simplebgc.c brugi/brugi.c net/savepng.c net/webserv.c net/webclient.c logging.c \
 draw/android_gles.c draw/glesa_draw.c \
 gps/jni_gps.c



LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image libxml2

LOCAL_LDLIBS := -lGLESv1_CM -llog -lz
#LOCAL_LDLIBS := -lGLESv2 -llog -lEGL

include $(BUILD_SHARED_LIBRARY)