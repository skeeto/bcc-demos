CC        = bcc
CFLAGS   ?=  -ansi -W -O -Md
DOS      ?= dosbox
DOSFLAGS ?= -exit

test.com : test.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

.PHONY : clean run

run : test.com
	$(DOS) -exit $^

clean :
	$(RM) test.com
