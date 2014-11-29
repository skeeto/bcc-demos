CC       = bcc
LINK     = ld86
CFLAGS  += -ansi -Md -Mf -Mc -0 -O86
LDFLAGS += -y -d -T100

all : bare.com

bare.com : bare.o
bare.o : bare.c

.PHONY : all clean test

clean :
	$(RM) bare.o bare.com

test : bare.com
	dosbox $^

%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $<

%.com : %.o
	$(LINK) -o $@ $(LDFLAGS) $< $(LDLIBS)
