root := ../../..

include $(root)/build/config.make

dirs :=

ifeq ($(XSDE_CUSTOM_ALLOCATOR),n)

dirs += binary compositors custom evolution

ifeq ($(XSDE_IOSTREAM),y)
ifeq ($(XSDE_EXCEPTIONS),y)

dirs += hello multiroot streaming

ifeq ($(XSDE_STL),y)
dirs += library wildcard filter
endif

ifeq ($(XSDE_POLYMORPHIC),y)
dirs += polymorphism polyroot
endif

endif
endif

ifeq ($(XSDE_STL),n)
ifeq ($(XSDE_EXCEPTIONS),n)
dirs += minimal
endif
endif

else # XSDE_CUSTOM_ALLOCATOR

ifeq ($(XSDE_STL),n)
ifeq ($(XSDE_EXCEPTIONS),n)
dirs += allocator
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
