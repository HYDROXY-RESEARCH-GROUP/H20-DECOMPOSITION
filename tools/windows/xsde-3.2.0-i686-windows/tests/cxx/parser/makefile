root := ../../..

include $(root)/build/config.make

dirs := generated-impl duplicate

ifeq ($(XSDE_IOSTREAM),y)
ifeq ($(XSDE_EXCEPTIONS),y)
dirs += \
built-in       \
recursive      \
test-template  \
union

ifeq ($(XSDE_REUSE_STYLE),tiein)
dirs += \
enumeration    \
list
endif

endif # EXCEPTIONS

ifeq ($(XSDE_POLYMORPHIC),y)
ifeq ($(XSDE_REUSE_STYLE),tiein)
dirs += polymorphism
endif
endif

dirs += reset

endif # IOSTREAM

ifeq ($(XSDE_PARSER_VALIDATION),y)
dirs += validation

ifeq ($(XSDE_IOSTREAM),y)

ifeq ($(XSDE_EXCEPTIONS),y)
dirs += error-handling/exceptions
else
dirs += error-handling/codes
endif

ifeq ($(XSDE_EXCEPTIONS),y)
dirs += name-clash/inheritance
endif

endif
endif


.PHONY: all $(dirs)

all: $(dirs)

$(dirs):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
%.make:: ;

%:: $(dirs) ;
