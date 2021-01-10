root := ../../..

include $(root)/build/config.make

dirs := sequences

ifeq ($(XSDE_POLYMORPHIC),y)
dirs += polymorphism/any-type polymorphism/enumeration polymorphism/multischema
endif

ifeq ($(XSDE_STL),y)
ifeq ($(XSDE_STL_ITERATOR),y)
dirs += iterator
endif
endif

ifeq ($(XSDE_IOSTREAM),y)
dirs += built-in default enumeration list test-template union facets pattern

ifeq ($(XSDE_ENCODING),iso8859-1)
dirs += iso8859-1
endif

ifeq ($(XSDE_PARSER_VALIDATION),y)
dirs += choice recursive clone

ifeq ($(XSDE_CDR),y)
dirs += binary/cdr
endif

ifeq ($(XSDE_XDR),y)
dirs += binary/xdr
endif
endif

endif # XSDE_IOSTREAM


.PHONY: all $(dirs)

all: $(dirs)

$(dirs):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
%.make:: ;

%:: $(dirs) ;
