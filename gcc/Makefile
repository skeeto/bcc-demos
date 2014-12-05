CC      = gcc
OBJCOPY = objcopy
CFLAGS  = -std=gnu99 -Wall -Os -nostdlib -m32 -Wno-unused-function \
  -ffreestanding -fomit-frame-pointer -fwrapv -fno-strict-aliasing \
  -fno-leading-underscore \
  -Wl,--nmagic,-static,--build-id=none,-Tdemo.ld

all : demo.com

demo.com : demo.c \
    vga.h time.h int.h math.h joystick.h vga_font.h port.h tone.h mouse.h

.PHONY : all clean test

clean :
	$(RM) demo.com demo.com.elf

test : demo.com
	dosbox $^

%.com : %.c
	$(CC) -o $@.elf $(CFLAGS) $<
	$(OBJCOPY) -O binary $@.elf $@
