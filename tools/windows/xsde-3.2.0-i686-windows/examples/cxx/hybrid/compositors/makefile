root := ../../../..

include $(root)/build/cxx/rules.make

# Build.
#
EXTRA_CPPFLAGS := -I$(root)/libxsde

ifeq ($(XSDE_ENCODING),iso8859-1)
EXTRA_XSDFLAGS += --char-encoding iso8859-1
endif

ifeq ($(XSDE_STL),n)
EXTRA_XSDFLAGS += --no-stl
endif

ifeq ($(XSDE_IOSTREAM),n)
EXTRA_XSDFLAGS += --no-iostream
endif

ifeq ($(XSDE_EXCEPTIONS),n)
EXTRA_XSDFLAGS += --no-exceptions
endif

ifeq ($(XSDE_LONGLONG),n)
EXTRA_XSDFLAGS += --no-long-long
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
EXTRA_XSDFLAGS += --reuse-style-mixin
endif

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

driver: driver.o compositors.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx compositors.hxx
compositors.o: compositors.cxx compositors.hxx

.PRECIOUS: %.hxx %.cxx

%.hxx %.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) $<


# Generate.
#
.PHONY: gen
gen: compositors.hxx


# Test.
#
.PHONY: test
test: driver
	./driver

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f compositors.o driver.o driver

clean: cleanobj
	rm -f compositors.?xx
