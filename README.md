# Real Mode VGA Demos

These are demos using [Bruce's C Compiler][bcc] (BCC) to develop
old-school MS-DOS COM programs with VGA capabilities. The demos should
run on any DOS system, including emulation/virtualization like
[Dosbox][dosbox] and [Dosemu][dosemu].

BCC is very rudimentary, not even supporting all of ANSI C. It also
doesn't support x86 far pointers, which makes accessing additional
memory segments (such as memory-mapped VGA) difficult. Fortunately it
supports inline assembly, providing an escape hatch (see `vga.h`).

On Debian BCC is available for install as a regular package.

    # apt-get install bcc dosbox
    $ make
    $ dosbox test.com


[bcc]: http://linux.die.net/man/1/bcc
[dosbox]: http://www.dosbox.com/
[dosemu]: http://www.dosemu.org/
