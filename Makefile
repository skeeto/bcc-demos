CC        = bcc
CFLAGS   ?= -ansi -W -O -Md
DOS      ?= dosbox
DOSFLAGS ?= -exit

all : test.com life.com

test.com : test.c vga.h

life.com : life.c vga.h

.PHONY : clean run

run : life.com
	$(DOS) -exit $^

clean :
	$(RM) test.com

%.com : %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)
