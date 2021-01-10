# file      : build/c/rules.make
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(root)/build/config.make

# Rules.
#
%.o: %.c
	$(CC) $(CPPFLAGS) $(EXTRA_CPPFLAGS) $(CFLAGS) -c $< -o $@
