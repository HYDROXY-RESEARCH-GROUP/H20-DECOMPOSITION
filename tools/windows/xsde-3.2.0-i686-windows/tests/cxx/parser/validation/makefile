root := ../../../..

include $(root)/build/config.make

dirs := built-in

ifeq ($(XSDE_IOSTREAM),y)
ifeq ($(XSDE_EXCEPTIONS),y)
dirs += all any attribute choice restriction sequence
endif
endif

.PHONY: _all $(dirs)

_all: $(dirs)

$(dirs):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
%.make:: ;

%:: $(dirs) ;
