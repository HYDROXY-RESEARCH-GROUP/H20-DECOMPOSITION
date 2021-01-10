root := ../../../../..

include $(root)/build/cxx/rules.make

# Build.
#
EXTRA_CPPFLAGS := -I$(root)/libxsde

ifeq ($(XSDE_ENCODING),iso8859-1)
EXTRA_XSDFLAGS += --char-encoding iso8859-1
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

driver: driver.o email.o body.o email-pskel.o email-pimpl.o \
email-sskel.o email-simpl.o envelope-pimpl.o envelope-simpl.o \
$(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx email.hxx envelope.hxx body.hxx email-pimpl.hxx email-simpl.hxx
email.o: email.cxx email.hxx envelope.hxx
body.o: body.cxx body.hxx email.hxx
email-pskel.o: email-pskel.cxx
email-pimpl.o: email-pimpl.cxx
email-simpl.o: email-simpl.cxx
email-simpl.o: email-simpl.cxx
envelope-pimpl.o: envelope-pimpl.cxx envelope-pimpl.hxx email.hxx body.hxx
envelope-simpl.o: envelope-simpl.cxx envelope-simpl.hxx email.hxx body.hxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx

%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx \
%-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) \
--options-file options $<


# Generate.
#
.PHONY: gen
gen: email.hxx


# Test.
#
.PHONY: test
test: driver email.xml
	./driver email.xml

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f envelope-pimpl.o envelope-simpl.o email-pimpl.o email-pskel.o \
email-simpl.o email-sskel.o body.o email.o driver.o driver

clean: cleanobj
	rm -f email-pimpl.?xx email-pskel.?xx email-simpl.?xx email-sskel.?xx \
email.?xx 
