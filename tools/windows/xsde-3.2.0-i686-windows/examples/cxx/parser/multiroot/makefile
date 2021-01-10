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
impl := protocol-pimpl-mixin
else
impl := protocol-pimpl-tiein
endif


driver: driver.o protocol-pskel.o $(impl).o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx $(impl).hxx protocol-pskel.hxx protocol.hxx
$(impl).o: $(impl).cxx $(impl).hxx protocol-pskel.hxx protocol.hxx
protocol-pskel.o: protocol-pskel.cxx protocol-pskel.hxx protocol.hxx

.PRECIOUS: %-pskel.hxx %-pskel.cxx

%-pskel.hxx %-pskel.cxx: %.xsd %.map
	$(root)/bin/xsde cxx-parser $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--type-map $*.map $<


# Generate.
#
.PHONY: gen
gen: protocol-pskel.hxx


# Test.
#
.PHONY: test
test: driver balance.xml withdraw.xml deposit.xml
	./driver balance.xml
	./driver withdraw.xml
	./driver deposit.xml


# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f $(impl).o protocol-pskel.o driver.o driver

clean: cleanobj
	rm -f protocol-pskel.?xx
