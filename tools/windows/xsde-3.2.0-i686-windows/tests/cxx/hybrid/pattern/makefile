root := ../../../..

include $(root)/build/cxx/rules.make

EXTRA_CPPFLAGS := -I$(root)/libxsde

EXTRA_XSDFLAGS += --char-encoding $(XSDE_ENCODING)

ifeq ($(XSDE_STL),n)
EXTRA_XSDFLAGS += --no-stl
endif

ifeq ($(XSDE_IOSTREAM),n)
EXTRA_XSDFLAGS += --no-iostream
endif

ifeq ($(XSDE_EXCEPTIONS),n)
EXTRA_XSDFLAGS += --no-exceptions
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

ifeq ($(XSDE_CUSTOM_ALLOCATOR),y)
EXTRA_XSDFLAGS += --custom-allocator
endif

driver: driver.o test.o test-pskel.o test-pimpl.o test-sskel.o test-simpl.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx test.hxx test-pskel.hxx test-pimpl.hxx test-sskel.hxx test-simpl.hxx 
test.o: test.cxx
test-pskel.o: test-pskel.cxx
test-pimpl.o: test-pimpl.cxx
test-sskel.o: test-sskel.cxx
test-simpl.o: test-simpl.cxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx %-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx
%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx %-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) --generate-parser --generate-serializer --generate-aggregate $<

.PHONY: gen
gen: test.hxx test.cxx test-pskel.hxx test-pskel.cxx test-pimpl.hxx test-pimpl.cxx test-sskel.hxx test-sskel.cxx test-simpl.hxx test-simpl.cxx

.PHONY: test
test: driver
	./driver test-000.xml | diff -u test-000.std -

.PHONY: clean cleanobj
cleanobj:
	rm -f driver driver.o test.o test-pskel.o test-pimpl.o test-sskel.o test-simpl.o

clean: cleanobj
	rm -f test.cxx test-pskel.cxx test-pimpl.cxx test-sskel.cxx test-simpl.cxx test.ixx test-pskel.ixx test-pimpl.ixx test-sskel.ixx test-simpl.ixx test.hxx test-pskel.hxx test-pimpl.hxx test-sskel.hxx test-simpl.hxx 

