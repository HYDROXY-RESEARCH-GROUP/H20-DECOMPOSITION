root := ../../../../..

include $(root)/build/config.make

dirs := binary boolean byte date-time float int integer qname short \
string uri

ifeq ($(XSDE_IOSTREAM),y)
ifeq ($(XSDE_EXCEPTIONS),y)
ifeq ($(XSDE_REUSE_STYLE),tiein)
dirs += any-type
endif
endif
endif

ifeq ($(XSDE_LONGLONG),y)
dirs += long-long
else
dirs += long
endif

.PHONY: all $(dirs)

all: $(dirs)

$(dirs):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
%.make:: ;

%:: $(dirs) ;
