root := ../../../..

include $(root)/build/cxx/rules.make

# Build.
#
EXTRA_CPPFLAGS := -I$(root)/libxsde

ifeq ($(XSDE_ENCODING),iso8859-1)
EXTRA_XSDFLAGS += --char-encoding iso8859-1
endif

ifeq ($(XSDE_LONGLONG),n)
EXTRA_XSDFLAGS += --no-long-long
endif

ifeq ($(XSDE_PARSER_VALIDATION),n)
EXTRA_XSDFLAGS += --suppress-validation
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
EXTRA_XSDFLAGS += --reuse-style-mixin
endif

ifeq ($(XSDE_REUSE_STYLE),none)
EXTRA_XSDFLAGS += --reuse-style-none
endif

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

driver: driver.o hello-pskel.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx hello-pskel.hxx
hello-pskel.o: hello-pskel.cxx hello-pskel.hxx

.PRECIOUS: %-pskel.hxx %-pskel.cxx
%-pskel.hxx %-pskel.cxx: %.xsd
	$(root)/bin/xsde cxx-parser $(XSDFLAGS) $(EXTRA_XSDFLAGS) $<


# Generate.
#
.PHONY: gen
gen: hello-pskel.hxx


# Test.
#
.PHONY: test
test: driver hello.xml
	./driver hello.xml


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f hello-pskel.o driver.o driver

clean: cleanobj
	rm -f hello-pskel.?xx
