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
impl := people-pimpl-mixin
else
impl := people-pimpl-tiein
endif

driver: driver.o people-pskel.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx $(impl).hxx people-pskel.hxx gender.hxx
people-pskel.o: people-pskel.cxx people-pskel.hxx gender.hxx

.PRECIOUS: %-pskel.hxx %-pskel.cxx

%-pskel.hxx %-pskel.cxx: %.xsd %.map
	$(root)/bin/xsde cxx-parser $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--type-map $*.map $<


# Generate.
#
.PHONY: gen
gen: people-pskel.hxx


# Test.
#
.PHONY: test
test: driver people.xml
	./driver people.xml


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f people-pskel.o driver.o driver

clean: cleanobj
	rm -f people-pskel.?xx
