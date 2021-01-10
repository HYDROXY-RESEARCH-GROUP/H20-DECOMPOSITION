root := ../../../..

include $(root)/build/cxx/rules.make

# Build.
#
EXTRA_CPPFLAGS := -I$(root)/libxsde

EXTRA_XSDFLAGS := --no-stl --no-exceptions --custom-allocator

ifeq ($(XSDE_ENCODING),iso8859-1)
EXTRA_XSDFLAGS += --char-encoding iso8859-1
endif

ifeq ($(XSDE_IOSTREAM),n)
EXTRA_XSDFLAGS += --no-iostream
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

driver: driver.o arena.o people.o people-pskel.o people-pimpl.o \
people-sskel.o people-simpl.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx arena.cxx arena.hxx people.hxx people-pimpl.hxx \
people-simpl.hxx
arena.o: arena.cxx arena.hxx
people.o: people.cxx
people-pskel.o: people-pskel.cxx
people-pimpl.o: people-pimpl.cxx
people-simpl.o: people-simpl.cxx
people-simpl.o: people-simpl.cxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-parser --generate-serializer --generate-aggregate $<


# Generate.
#
.PHONY: gen
gen: people.hxx


# Test.
#
.PHONY: test
test: driver people.xml
	./driver people.xml

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f people-pimpl.o people-pskel.o people-simpl.o people-sskel.o \
people.o driver.o arena.o driver

clean: cleanobj
	rm -f people-pimpl.?xx people-pskel.?xx people-simpl.?xx \
people-sskel.?xx people.?xx 
