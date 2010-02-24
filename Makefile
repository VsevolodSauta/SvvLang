COMPILE=gcc -c

all: internals externals
	ld *.o -lm -o SvvLanguage
	
internals: internal_object.o internal_nothing.o internal_allocator.o internal_mmu.o internal_string.o internal_list.o internal_set.o internal_map.o 


internal_nothing.o: internal_nothing.c
	$(COMPILE) internal_nothing.c -o internal_nothing.o
	
internal_object.o: internal_object.c
	$(COMPILE) internal_object.c -o internal_object.o
	
internal_list.o: internal_list.c internal_list.h
	$(COMPILE) internal_list.c -o internal_list.o
	
internal_allocator.o: internal_allocator.c internal_allocator.h
	$(COMPILE) internal_allocator.c -o internal_allocator.o
	
internal_set.o: internal_set.c internal_set.h
	$(COMPILE) internal_set.c -o internal_set.o

internal_map.o: internal_map.c internal_map.h
	$(COMPILE) internal_map.c -o internal_map.o

internal_string.o: internal_string.c internal_string.h
	$(COMPILE) internal_string.c -o internal_string.o

internal_mmu.o: internal_mmu.c internal_mmu.h
	$(COMPILE) internal_mmu.c -o internal_mmu.o

externals: external_object.o

external_object.o: external_object.c external_object.h
	$(COMPILE) external_object.c -o external_object.o

clean:
	rm -f *.o
	
PHONY: internals externals clean all