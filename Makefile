CC        = bcc
CFLAGS   ?= -ansi -W -O -Md
DOS      ?= dosbox
DOSFLAGS ?= -exit

test.com : test.c vga.h
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

.PHONY : clean run

run : test.com
	$(DOS) -exit $^

clean :
	$(RM) test.com
