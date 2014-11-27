CC        = bcc
CFLAGS   ?= -ansi -W -O -Md
DOS      ?= dosbox
DOSFLAGS ?= -exit

all : test.com life.com rmrogue.com

test.com : test.c vga.h

life.com : life.c vga.h

rmrogue.com : test.c vga.h sound.h time.h

.PHONY : clean run

run : rmrogue.com
	$(DOS) -exit $^

clean :
	$(RM) test.com

%.com : %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)
