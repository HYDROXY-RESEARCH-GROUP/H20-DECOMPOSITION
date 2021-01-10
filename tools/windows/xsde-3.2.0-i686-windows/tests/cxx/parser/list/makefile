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
EXTRA_XSDFLAGS += --suppress-validation
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

driver: driver.o test-pskel.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx test-pskel.hxx 
test-pskel.o: test-pskel.cxx

.PRECIOUS: %-pskel.hxx %-pskel.ixx %-pskel.cxx
%-pskel.hxx %-pskel.ixx %-pskel.cxx: %.xsd
	$(root)/bin/xsde cxx-parser $(XSDFLAGS) $(EXTRA_XSDFLAGS) $<

.PHONY: gen
gen: test-pskel.hxx test-pskel.ixx test-pskel.cxx

.PHONY: test
test: driver
	./driver test-000.xml | diff -u test-000.std -

.PHONY: clean cleanobj
cleanobj:
	rm -f driver driver.o test-pskel.o

clean: cleanobj
	rm -f test-pskel.cxx test-pskel.ixx test-pskel.hxx 

