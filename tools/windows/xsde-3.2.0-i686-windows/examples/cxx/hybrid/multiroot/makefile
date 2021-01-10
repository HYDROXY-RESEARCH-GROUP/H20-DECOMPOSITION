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

ifeq ($(XSDE_REUSE_STYLE),mixin)
EXTRA_XSDFLAGS += --reuse-style-mixin
endif

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

driver: driver.o protocol.o protocol-pskel.o protocol-pimpl.o \
$(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx protocol.hxx protocol-pimpl.hxx
protocol.o: protocol.cxx
protocol-pskel.o: protocol-pskel.cxx
protocol-pimpl.o: protocol-pimpl.cxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx
%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--generate-parser --generate-aggregate --root-element-all $<


# Generate.
#
.PHONY: gen
gen: protocol.hxx


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
	rm -f protocol-pimpl.o protocol-pskel.o protocol.o driver.o driver

clean: cleanobj
	rm -f protocol-pimpl.?xx protocol-pskel.?xx protocol.?xx
