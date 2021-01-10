root := ../../../..

include $(root)/build/cxx/rules.make

# Build.
#
EXTRA_CPPFLAGS += -I$(root)/libxsde

ifeq ($(XSDE_ENCODING),iso8859-1)
EXTRA_XSDFLAGS += --char-encoding iso8859-1
endif

ifeq ($(XSDE_LONGLONG),n)
EXTRA_XSDFLAGS += --no-long-long
endif

ifeq ($(XSDE_PARSER_VALIDATION),n)
EXTRA_XSDFLAGS += --suppress-validation
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
EXTRA_XSDFLAGS += --reuse-style-mixin
endif

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
impl := library-pimpl-mixin
else
impl := library-pimpl-tiein
endif

driver: driver.o library-pskel.o $(impl).o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx $(impl).hxx library-pskel.hxx library.hxx
$(impl).o: $(impl).cxx $(impl).hxx library-pskel.hxx library.hxx
library-pskel.o: library-pskel.cxx library-pskel.hxx library.hxx

.PRECIOUS: %-pskel.hxx %-pskel.cxx

%-pskel.hxx %-pskel.cxx: %.xsd %.map
	$(root)/bin/xsde cxx-parser $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--type-map $*.map $<


# Generate.
#
.PHONY: gen
gen: library-pskel.hxx



# Test.
#
.PHONY: test
test: driver library.xml
	./driver library.xml


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f $(impl).o library-pskel.o driver.o driver

clean: cleanobj
	rm -f library-pskel.?xx
