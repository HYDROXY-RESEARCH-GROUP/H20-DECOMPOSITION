root := ../../../..

include $(root)/build/config.make

dirs := built-in

ifeq ($(XSDE_IOSTREAM),y)
dirs += any attribute choice element sequence
endif

.PHONY: all $(dirs)

all: $(dirs)

$(dirs):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
%.make:: ;

%:: $(dirs) ;
