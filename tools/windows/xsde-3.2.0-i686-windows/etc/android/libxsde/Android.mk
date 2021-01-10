# Android build system makefile for the XSD/e runtime library. See the 
# accompanying README file for more information on how to use XSD/e
# with Android.
#

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libxsde
LOCAL_CPP_EXTENSION := .cxx

$(LOCAL_PATH)/xsde/xsde-files.mk: LP := $(LOCAL_PATH)
$(LOCAL_PATH)/xsde/xsde-files.mk: $(LOCAL_PATH)/../config/config.make
	@echo "updating XSD/e configuration"
	@rm -f $(LP)/xsde/xsde-files.mk $(LP)/xsde/config.h
	@$(MAKE) -s -C $(LP)

-include $(LOCAL_PATH)/xsde/xsde-files.mk

include $(BUILD_STATIC_LIBRARY)
