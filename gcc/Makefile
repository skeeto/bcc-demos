CC      = gcc
OBJCOPY = objcopy
CFLAGS  = -std=gnu99 -Wall -Os -nostdlib -m32 -Wno-unused-function \
  -ffreestanding -fomit-frame-pointer -fwrapv -fno-strict-aliasing \
  -Wl,--nmagic,-static,--build-id=none,-Thello.ld

all : hello.com

hello.com : hello.c \
    vga.h time.h int.h math.h joystick.h vga_font.h port.h tone.h mouse.h

.PHONY : all clean test

clean :
	$(RM) hello.com hello.com.elf

test : hello.com
	dosbox $^

%.com : %.c
	$(CC) -o $@.elf $(CFLAGS) $<
	$(OBJCOPY) -O binary $@.elf $@
