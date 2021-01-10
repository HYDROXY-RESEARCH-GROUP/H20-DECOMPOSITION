root := ../../../../..

include $(root)/build/cxx/rules.make

override LIBS += -lACE

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
library-sskel.o library-simpl.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx library.hxx library-pimpl.hxx library-simpl.hxx
library.o: library.cxx library.hxx
library-pskel.o: library-pskel.cxx
library-pimpl.o: library-pimpl.cxx
library-simpl.o: library-simpl.cxx
library-simpl.o: library-simpl.cxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-parser --generate-serializer --generate-aggregate \
--generate-insertion CDR --generate-extraction CDR $<


# Generate.
#
.PHONY: gen
gen: library.hxx


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
library.o driver.o driver

clean: cleanobj
	rm -f library-pimpl.?xx library-pskel.?xx library-simpl.?xx \
library-sskel.?xx library.?xx
