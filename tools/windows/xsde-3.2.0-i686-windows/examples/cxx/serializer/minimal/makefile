root := ../../../..

include $(root)/build/cxx/rules.make

# Build.
#
EXTRA_CPPFLAGS += -I$(root)/libxsde

EXTRA_XSDFLAGS := --no-stl --no-exceptions

ifeq ($(XSDE_ENCODING),iso8859-1)
EXTRA_XSDFLAGS += --char-encoding iso8859-1
endif

ifeq ($(XSDE_IOSTREAM),n)
EXTRA_XSDFLAGS += --no-iostream
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
impl := people-simpl-mixin
else
impl := people-simpl-tiein
endif

driver: driver.o people-sskel.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx $(impl).hxx people-sskel.hxx people.hxx
people-sskel.o: people-sskel.cxx people-sskel.hxx people.hxx

.PRECIOUS: %-sskel.hxx %-sskel.cxx

%-sskel.hxx %-sskel.cxx: %.xsd %.map
	$(root)/bin/xsde cxx-serializer $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--type-map $*.map $<


# Generate.
#
.PHONY: gen
gen: people-sskel.hxx


# Test.
#
.PHONY: test
test: driver
	./driver


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f people-sskel.o driver.o driver

clean: cleanobj
	rm -f people-sskel.?xx
