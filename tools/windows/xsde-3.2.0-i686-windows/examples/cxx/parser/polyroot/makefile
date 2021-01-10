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

ifeq ($(XSDE_REUSE_STYLE),mixin)
impl := supermen-pimpl-mixin
else
impl := supermen-pimpl-tiein
endif

driver: driver.o supermen-pskel.o $(impl).o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx $(impl).hxx supermen-pskel.hxx
$(impl).o: $(impl).cxx $(impl).hxx supermen-pskel.hxx
supermen-pskel.o: supermen-pskel.cxx supermen-pskel.hxx

.PRECIOUS: %-pskel.hxx %-pskel.cxx

%-pskel.hxx %-pskel.cxx: %.xsd
	$(root)/bin/xsde cxx-parser $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-polymorphic $<


# Generate.
#
.PHONY: gen
gen: supermen-pskel.hxx


# Test.
#
.PHONY: test
test: driver person.xml batman.xml superman.xml
	./driver person.xml
	./driver batman.xml
	./driver superman.xml


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f $(impl).o supermen-pskel.o driver.o driver

clean: cleanobj
	rm -f supermen-pskel.?xx
