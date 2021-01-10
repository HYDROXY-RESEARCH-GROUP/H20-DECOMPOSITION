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

ifeq ($(XSDE_LONGLONG),n)
EXTRA_XSDFLAGS += --no-long-long
endif

ifeq ($(XSDE_PARSER_VALIDATION),n)
EXTRA_XSDFLAGS += --suppress-parser-val
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
EXTRA_XSDFLAGS += --reuse-style-mixin
endif

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

driver: driver.o hello.o hello-pskel.o hello-pimpl.o \
$(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx hello.hxx hello-pimpl.hxx
hello.o: hello.cxx
hello-pskel.o: hello-pskel.cxx
hello-pimpl.o: hello-pimpl.cxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx
%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-parser --generate-aggregate $<


# Generate.
#
.PHONY: gen
gen: hello.hxx


# Test.
#
.PHONY: test
test: driver hello.xml
	./driver hello.xml

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f hello-pimpl.o hello-pskel.o hello.o driver.o driver

clean: cleanobj
	rm -f hello-pimpl.?xx hello-pskel.?xx hello.?xx
