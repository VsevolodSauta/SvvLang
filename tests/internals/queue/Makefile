MAIN_DIRECTORY=../../..
INTERNALS=$(MAIN_DIRECTORY)/internals.a
COMPILE=gcc -I$(MAIN_DIRECTORY)

all: test


%.elf: %.c
	$(COMPILE) $^ $(INTERNALS) -o $@

test: test1.elf
	./test1.elf

clean:
	rm -rf *.elf
