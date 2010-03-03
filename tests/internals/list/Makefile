MAIN_DIRECTORY=../../..
INTERNALS=$(MAIN_DIRECTORY)/internals.a
COMPILE=gcc-4.4 -I$(MAIN_DIRECTORY) -g -Wall

all: test


%.elf: %.c
	$(COMPILE) $^ $(INTERNALS) -o $@

test: test1.elf test2.elf test3.elf test4.elf test5.elf
	./test1.elf
	./test2.elf
	./test3.elf
	./test4.elf
	./test5.elf

clean:
	rm -rf *.elf
