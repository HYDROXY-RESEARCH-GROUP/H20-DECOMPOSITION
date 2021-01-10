dirs := libxsde examples

.PHONY: all $(dirs)
all: $(dirs)

tests: libxsde
examples: libxsde

$(dirs):
	$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
% :: $(dirs) ;
