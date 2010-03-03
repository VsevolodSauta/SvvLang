MAIN_DIRECTORY=../../..
INTERNALS=$(MAIN_DIRECTORY)/internals.a
COMPILE=gcc-4.4 -I$(MAIN_DIRECTORY) -g

all: test


%.elf: %.c $(INTERNALS)
	$(COMPILE) $^ -o $@

test: test1.elf test2.elf
	./test1.elf
	./test2.elf

clean:
	rm -rf *.elf
