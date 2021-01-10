root := ../../../../..

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
EXTRA_XSDFLAGS += --suppress-parser-val
endif

ifeq ($(XSDE_SERIALIZER_VALIDATION),n)
EXTRA_XSDFLAGS += --suppress-serializer-val
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
EXTRA_XSDFLAGS += --reuse-style-mixin
endif

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

driver: driver.o transform.o transform-pskel.o transform-pimpl.o \
$(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx transform.hxx transform-pimpl.hxx
transform.o: transform.cxx transform.hxx
transform-pskel.o: transform-pskel.cxx
transform-pimpl.o: transform-pimpl.cxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-parser --generate-aggregate --root-element transformations \
--generate-polymorphic $<


# Generate.
#
.PHONY: gen
gen: transform.hxx


# Test.
#
.PHONY: test
test: driver transform.xml
	./driver transform.xml

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f transform-pimpl.o transform-pskel.o transform.o driver.o driver

clean: cleanobj
	rm -f transform-pimpl.?xx transform-pskel.?xx transform.?xx 
