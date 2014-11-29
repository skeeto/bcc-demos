CC      = gcc
OBJCOPY = objcopy
CFLAGS  = -std=gnu99 -Wall -Os -Wl,-n,-static,--build-id=none,-Thello.ld -ffreestanding -nostdlib -m32

all : hello.com

hello.com : hello.c

.PHONY : all clean test

clean :
	$(RM) hello.com hello.com.elf

test : hello.com
	dosbox $^

%.com : %.c
	$(CC) -o $@.elf $(CFLAGS) $<
	$(OBJCOPY) -O binary $@.elf $@
