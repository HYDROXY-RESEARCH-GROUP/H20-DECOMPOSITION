root := ../..

include $(root)/build/config.make

dirs := string hybrid parser serializer

ifeq ($(XSDE_POLYMORPHIC),y)
dirs += hashmap
endif

.PHONY: all $(dirs)

all: $(dirs)

$(dirs):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
% :: $(dirs) ;
