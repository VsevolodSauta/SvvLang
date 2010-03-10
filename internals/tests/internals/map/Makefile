MAIN_DIRECTORY=../../..
INTERNALS=$(MAIN_DIRECTORY)/internals.a
COMPILE=gcc -I$(MAIN_DIRECTORY) -g

all: test


%.elf: %.c $(INTERNALS)
	$(COMPILE) $^ -o $@

test: test1.elf
	./test1.elf

clean:
	rm -rf *.elf
