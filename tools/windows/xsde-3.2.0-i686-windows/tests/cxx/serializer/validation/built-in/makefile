root := ../../../../..

include $(root)/build/config.make

dirs := date-time decimal integer qname string

.PHONY: all $(dirs)

all: $(dirs)

$(dirs):
	@$(MAKE) -C $@ $(MAKECMDGOALS)

makefile: ;
%.make:: ;

%:: $(dirs) ;
