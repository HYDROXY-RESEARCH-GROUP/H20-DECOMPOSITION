# Android build system makefile for the 'minimal' C++/Hybrid example
# (examples/cxx/hybrid/minimal). See the accompanying README file for
# more information on how to use XSD/e with Android.
#
MY_XSDE_DIR := xsde

# Save the local path and include the XSD/e runtime library makefile.
#
MY_LOCAL_PATH := $(call my-dir)

include $(MY_LOCAL_PATH)/$(MY_XSDE_DIR)/libxsde/Android.mk

LOCAL_PATH := $(MY_LOCAL_PATH)

include $(CLEAR_VARS)

# Add the XSD/e runtime library to the include search list as well as
# link to the libxsde.a library.
#
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(MY_XSDE_DIR)/libxsde
LOCAL_STATIC_LIBRARIES := libxsde

LOCAL_MODULE := minimal
LOCAL_CPP_EXTENSION := .cxx
LOCAL_SRC_FILES := \
driver.cxx \
people.cxx \
people-pimpl.cxx \
people-pskel.cxx \
people-simpl.cxx \
people-sskel.cxx \

# Explicit dependency that tells the build system it should compile
# the schema before compiling C++ files.
#
$(LOCAL_PATH)/driver.cxx: $(LOCAL_PATH)/people.hxx

# XSD/e compiler pattern rules.
#
MY_XSDFLAGS := \
--no-stl \
--no-exceptions \
--no-iostream \
--generate-parser \
--generate-serializer \
--generate-aggregate

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(LOCAL_PATH)/$(MY_XSDE_DIR)/bin/xsde cxx-hybrid $(MY_XSDFLAGS) $<

include $(BUILD_SHARED_LIBRARY)
