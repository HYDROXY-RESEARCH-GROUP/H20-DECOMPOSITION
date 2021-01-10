root := ../../../../..

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

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

driver: driver.o library.o library-pskel.o library-pimpl.o \
library-sskel.o library-simpl.o exceptions.o orawstream.o \
irawstream.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx library.hxx library-pimpl.hxx library-simpl.hxx
exceptions.o: exceptions.cxx
orawstream.o: orawstream.cxx xml-schema.hxx
irawstream.o: irawstream.cxx xml-schema.hxx
library.o: library.cxx library.hxx
library-pskel.o: library-pskel.cxx library-pskel.hxx
library-pimpl.o: library-pimpl.cxx library-pskel.hxx
library-simpl.o: library-simpl.cxx library-simpl.hxx
library-simpl.o: library-simpl.cxx library-simpl.hxx

library.hxx: xml-schema.hxx
library-pskel.hxx: xml-schema-pskel.hxx
library-pimpl.hxx: xml-schema-pskel.hxx
library-sskel.hxx: xml-schema-sskel.hxx
library-simpl.hxx: xml-schema-sskel.hxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx

xml-schema%hxx xml-schema-pskel%hxx xml-schema-sskel%hxx:
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-parser --generate-serializer --generate-xml-schema xml-schema.xsd

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--options-file options $<


# Generate.
#
.PHONY: gen
gen: xml-schema.hxx library.hxx


# Test.
#
.PHONY: test
test: driver library.xml
	./driver library.xml

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f library-pimpl.o library-pskel.o library-simpl.o library-sskel.o \
library.o irawstream.o orawstream.o exceptions.o driver.o driver

clean: cleanobj
	rm -f xml-schema.hxx xml-schema-pskel.hxx xml-schema-sskel.hxx \
library-pimpl.?xx library-pskel.?xx library-simpl.?xx library-sskel.?xx \
library.?xx
