COMPILE=gcc -c -g -Wall

all: internals.a
#	ld *.o -lm -o SvvLanguage
	
internals.a: internal_object.o internal_nothing.o internal_allocator.o internal_mmu.o internal_list.o internal_stack.o internal_queue.o internal_string.o internal_set.o internal_map.o
	if [ -f $@ ] ; then rm $@ ; fi
	ar r $@ $^

%.o: %.c
	$(COMPILE) $^ -o $@
	

clean:
	rm -f *.o internals.a
	
PHONY: internals externals clean all