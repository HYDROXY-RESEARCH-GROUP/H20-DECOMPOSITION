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

ifeq ($(XSDE_POLYMORPHIC),y)
EXTRA_XSDFLAGS += --runtime-polymorphic
endif

driver: driver.o text-pskel.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx text-pskel.hxx anchor.hxx
text-pskel.o: text-pskel.cxx text-pskel.hxx anchor.hxx

.PRECIOUS: %-pskel.hxx %-pskel.cxx

%-pskel.hxx %-pskel.cxx: %.xsd %.map
	$(root)/bin/xsde cxx-parser $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--type-map $*.map $<


# Generate.
#
.PHONY: gen
gen: text-pskel.hxx


# Test.
#
.PHONY: test
test: driver text.xml
	./driver text.xml

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f text-pskel.o driver.o driver

clean: cleanobj
	rm -f text-pskel.?xx

