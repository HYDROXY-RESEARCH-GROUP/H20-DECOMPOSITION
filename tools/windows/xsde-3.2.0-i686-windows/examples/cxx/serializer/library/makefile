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

ifeq ($(XSDE_SERIALIZER_VALIDATION),n)
EXTRA_XSDFLAGS += --suppress-validation
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
EXTRA_XSDFLAGS += --reuse-style-mixin
endif

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

ifeq ($(XSDE_REUSE_STYLE),mixin)
impl := library-simpl-mixin
else
impl := library-simpl-tiein
endif

driver: driver.o library-sskel.o $(impl).o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx $(impl).hxx library-sskel.hxx library.hxx
$(impl).o: $(impl).cxx $(impl).hxx library-sskel.hxx library.hxx
library-sskel.o: library-sskel.cxx library-sskel.hxx library.hxx

.PRECIOUS: %-sskel.hxx %-sskel.cxx

%-sskel.hxx %-sskel.cxx: %.xsd %.map
	$(root)/bin/xsde cxx-serializer $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--type-map $*.map $<


# Generate.
#
.PHONY: gen
gen: library-sskel.hxx


# Test.
#
.PHONY: test
test: driver
	./driver


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f $(impl).o library-sskel.o driver.o driver

clean: cleanobj
	rm -f library-sskel.?xx
