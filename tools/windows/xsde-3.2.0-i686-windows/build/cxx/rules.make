# file      : build/cxx/rules.make
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(root)/build/config.make

# Rules.
#
%.o: %.cxx
	$(CXX) $(CPPFLAGS) $(EXTRA_CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%: %.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
ifneq ($(POSTLD),)
	$(POSTLD) $@ $^ $(LIBS)
endif
