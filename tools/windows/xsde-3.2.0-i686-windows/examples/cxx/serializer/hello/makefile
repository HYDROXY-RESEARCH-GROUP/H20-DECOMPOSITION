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

ifeq ($(XSDE_SERIALIZER_VALIDATION),n)
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

driver: driver.o hello-sskel.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx hello-sskel.hxx
hello-sskel.o: hello-sskel.cxx hello-sskel.hxx

.PRECIOUS: %-sskel.hxx %-sskel.cxx
%-sskel.hxx %-sskel.cxx: %.xsd
	$(root)/bin/xsde cxx-serializer $(XSDFLAGS) $(EXTRA_XSDFLAGS) $<


# Generate.
#
.PHONY: gen
gen: hello-sskel.hxx


# Test.
#
.PHONY: test
test: driver
	./driver


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f hello-sskel.o driver.o driver

clean: cleanobj
	rm -f hello-sskel.?xx
