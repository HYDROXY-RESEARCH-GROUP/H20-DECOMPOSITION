root := ../../../../..

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

driver: driver.o test.o type.o test-pskel.o type-pskel.o test-pimpl.o type-pimpl.o test-sskel.o type-sskel.o test-simpl.o type-simpl.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx test.hxx type.hxx test-pskel.hxx type-pskel.hxx test-pimpl.hxx type-pimpl.hxx test-sskel.hxx type-sskel.hxx test-simpl.hxx type-simpl.hxx 
test.o: test.cxx
type.o: type.cxx
test-pskel.o: test-pskel.cxx
type-pskel.o: type-pskel.cxx
test-pimpl.o: test-pimpl.cxx
type-pimpl.o: type-pimpl.cxx
test-sskel.o: test-sskel.cxx
type-sskel.o: type-sskel.cxx
test-simpl.o: test-simpl.cxx
type-simpl.o: type-simpl.cxx

.PRECIOUS: %.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx %-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx
%.hxx %.cxx %-pskel.hxx %-pskel.cxx %-pimpl.hxx %-pimpl.cxx %-sskel.hxx %-sskel.cxx %-simpl.hxx %-simpl.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) --generate-parser --generate-serializer --generate-aggregate --generate-polymorphic --generate-typeinfo --polymorphic-type base --polymorphic-schema type.xsd $<

.PHONY: gen
gen: test.hxx type.hxx test.cxx type.cxx test-pskel.hxx type-pskel.hxx test-pskel.cxx type-pskel.cxx test-pimpl.hxx type-pimpl.hxx test-pimpl.cxx type-pimpl.cxx test-sskel.hxx type-sskel.hxx test-sskel.cxx type-sskel.cxx test-simpl.hxx type-simpl.hxx test-simpl.cxx type-simpl.cxx

.PHONY: test
test: driver
	./driver test-000.xml | diff -u test-000.std -

.PHONY: clean cleanobj
cleanobj:
	rm -f driver driver.o test.o type.o test-pskel.o type-pskel.o test-pimpl.o type-pimpl.o test-sskel.o type-sskel.o test-simpl.o type-simpl.o

clean: cleanobj
	rm -f test.cxx type.cxx test-pskel.cxx type-pskel.cxx test-pimpl.cxx type-pimpl.cxx test-sskel.cxx type-sskel.cxx test-simpl.cxx type-simpl.cxx test.ixx type.ixx test-pskel.ixx type-pskel.ixx test-pimpl.ixx type-pimpl.ixx test-sskel.ixx type-sskel.ixx test-simpl.ixx type-simpl.ixx test.hxx type.hxx test-pskel.hxx type-pskel.hxx test-pimpl.hxx type-pimpl.hxx test-sskel.hxx type-sskel.hxx test-simpl.hxx type-simpl.hxx 

