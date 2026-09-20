LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_MODULE := AcceptEULA
LOCAL_SRC_FILES := main.cpp

LOCAL_CFLAGS := \
    -O2 \
    -mfloat-abi=softfp \
    -DNDEBUG \
    -std=c++17 \
    -ffunction-sections \
    -fdata-sections

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)

LOCAL_LDLIBS := -llog

LOCAL_LDFLAGS := \
    -Wl,--gc-sections \
    -Wl,--strip-unneeded

include $(BUILD_SHARED_LIBRARY)
