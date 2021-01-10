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

driver: driver.o test.o $(root)/libxsde/xsde/libxsde.a

driver.o: driver.cxx test.hxx 
test.o: test.cxx

.PRECIOUS: %.hxx %.cxx
%.hxx %.cxx: %.xsd
	$(root)/bin/xsde cxx-hybrid $(XSDFLAGS) $(EXTRA_XSDFLAGS) $<

.PHONY: gen
gen: test.hxx test.cxx

.PHONY: test
test: driver
	./driver

.PHONY: clean cleanobj
cleanobj:
	rm -f driver driver.o test.o

clean: cleanobj
	rm -f test.cxx test.ixx test.hxx 

