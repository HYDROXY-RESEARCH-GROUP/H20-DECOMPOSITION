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

ifeq ($(XSDE_REUSE_STYLE),mixin)
impl := supermen-simpl-mixin
else
impl := supermen-simpl-tiein
endif

driver: driver.o supermen-sskel.o $(impl).o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx $(impl).hxx supermen-sskel.hxx supermen.hxx
$(impl).o: $(impl).cxx $(impl).hxx supermen-sskel.hxx supermen.hxx
supermen-sskel.o: supermen-sskel.cxx supermen-sskel.hxx supermen.hxx

.PRECIOUS: %-sskel.hxx %-sskel.cxx

%-sskel.hxx %-sskel.cxx: %.xsd %.map
	$(root)/bin/xsde cxx-serializer $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-polymorphic --type-map $*.map $<


# Generate.
#
.PHONY: gen
gen: supermen-sskel.hxx


# Test.
#
.PHONY: test
test: driver
	./driver


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f $(impl).o supermen-sskel.o driver.o driver

clean: cleanobj
	rm -f supermen-sskel.?xx
