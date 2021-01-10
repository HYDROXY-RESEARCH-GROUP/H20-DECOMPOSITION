root := ../../..

include $(root)/build/config.make

dirs := generated-driver

ifeq ($(XSDE_IOSTREAM),y)

dirs +=         \
all             \
built-in        \
choice          \
recursive       \
reset           \
restriction     \
sequence        \
test-template   \
wildcard

ifeq ($(XSDE_EXCEPTIONS),y)
dirs += error-handling/exceptions
else
dirs += error-handling/codes
endif

ifeq ($(XSDE_REUSE_STYLE),tiein)
dirs +=         \
complex         \
enumeration     \
list            \
union
endif

ifeq ($(XSDE_POLYMORPHIC),y)
ifeq ($(XSDE_REUSE_STYLE),tiein)
dirs += polymorphism
endif
endif

endif # XSDE_IOSTREAM

ifeq ($(XSDE_SERIALIZER_VALIDATION),y)
dirs += validation
endif


.PHONY: _all $(dirs)

_all: $(dirs)

$(dirs):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
%.make:: ;

%:: $(dirs) ;
