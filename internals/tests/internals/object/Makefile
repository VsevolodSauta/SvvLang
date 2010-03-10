MAIN_DIRECTORY=../../..
INTERNALS=$(MAIN_DIRECTORY)/internals.a
COMPILE=gcc -I$(MAIN_DIRECTORY)

all: test


%.elf: %.c $(INTERNALS)
	$(COMPILE) $^ -o $@

test: test1.elf test2.elf
	./test1.elf
	./test2.elf

clean:
	rm -rf *.elf
