root := ../../../..

include $(root)/build/config.make

dirs :=

ifeq ($(XSDE_IOSTREAM),y)
ifeq ($(XSDE_EXCEPTIONS),y)
ifeq ($(XSDE_STL),y)

ifeq ($(XSDE_POLYMORPHIC),y)
dirs += ignore passthrough
endif

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
