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

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

driver: driver.o position.o position-pskel.o position-pimpl.o \
position-sskel.o position-simpl.o object-pimpl.o object-simpl.o \
$(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx position.hxx position-pimpl.hxx position-simpl.hxx
position.o: position.cxx position.hxx
position-pskel.o: position-pskel.cxx
position-pimpl.o: position-pimpl.cxx
position-simpl.o: position-simpl.cxx
position-simpl.o: position-simpl.cxx
object-pimpl.o: object-pimpl.cxx object-pimpl.hxx position.hxx
object-simpl.o: object-simpl.cxx object-simpl.hxx position.hxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-parser --generate-serializer --generate-aggregate \
--custom-parser object=/object-pimpl.hxx \
--custom-serializer object=/object-simpl.hxx $<


# Generate.
#
.PHONY: gen
gen: position.hxx


# Test.
#
.PHONY: test
test: driver position.xml
	./driver position.xml

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f object-pimpl.o object-simpl.o position-pimpl.o position-pskel.o \
position-simpl.o position-sskel.o position.o driver.o driver

clean: cleanobj
	rm -f position-pimpl.?xx position-pskel.?xx position-simpl.?xx \
position-sskel.?xx position.?xx

