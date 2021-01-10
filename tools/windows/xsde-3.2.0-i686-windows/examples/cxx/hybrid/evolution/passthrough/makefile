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

driver: driver.o unknown-type.o transform.o xml.o transform-pskel.o \
transform-pimpl.o transform-sskel.o transform-simpl.o unknown-type-pimpl.o \
unknown-type-simpl.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx transform.hxx unknown-type.hxx xml.hxx xml.ixx \
transform-pimpl.hxx transform-simpl.hxx
transform.o: transform.cxx transform.hxx unknown-type.hxx
xml.o: xml.cxx xml.hxx xml.ixx transform.hxx
transform-pskel.o: transform-pskel.cxx
transform-pimpl.o: transform-pimpl.cxx
transform-simpl.o: transform-simpl.cxx
transform-simpl.o: transform-simpl.cxx
unknown-type.o: unknown-type.cxx unknown-type.hxx transform.hxx xml.hxx xml.ixx
unknown-type-pimpl.o: unknown-type-pimpl.cxx unknown-type-pimpl.hxx \
transform.hxx xml.hxx xml.ixx
unknown-type-simpl.o: unknown-type-simpl.cxx unknown-type-simpl.hxx \
transform.hxx xml.hxx xml.ixx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--options-file options $<


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
	rm -f unknown-type.o unknown-type-pimpl.o unknown-type-simpl.o \
transform-pimpl.o transform-pskel.o transform-simpl.o transform-sskel.o \
xml.o transform.o driver.o driver

clean: cleanobj
	rm -f transform-pimpl.?xx transform-pskel.?xx transform-simpl.?xx \
transform-sskel.?xx transform.?xx 
