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

ifeq ($(XSDE_SERIALIZER_VALIDATION),n)
EXTRA_XSDFLAGS += --suppress-serializer-val
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
EXTRA_XSDFLAGS += --reuse-style-mixin
endif

driver: driver.o supermen.o supermen-pskel.o supermen-pimpl.o \
supermen-sskel.o supermen-simpl.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx supermen.hxx supermen-pimpl.hxx supermen-simpl.hxx
supermen.o: supermen.cxx supermen.hxx
supermen-pskel.o: supermen-pskel.cxx
supermen-pimpl.o: supermen-pimpl.cxx
supermen-simpl.o: supermen-simpl.cxx
supermen-simpl.o: supermen-simpl.cxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-parser --generate-serializer --generate-aggregate \
--generate-polymorphic --generate-typeinfo --root-element person $<


# Generate.
#
.PHONY: gen
gen: supermen.hxx


# Test.
#
.PHONY: test
test: driver person.xml batman.xml superman.xml
	./driver person.xml
	./driver batman.xml
	./driver superman.xml

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f supermen-pimpl.o supermen-pskel.o supermen-simpl.o \
supermen-sskel.o supermen.o driver.o driver

clean: cleanobj
	rm -f supermen-pimpl.?xx supermen-pskel.?xx supermen-simpl.?xx \
supermen-sskel.?xx supermen.?xx
